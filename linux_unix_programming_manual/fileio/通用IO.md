### 文件I/O: 通用的I/O模型

```
所有执行I/O操作的系统调用都以文件描述符，一个非负整数(通常是小整数)，来指代打开的文件。文件描述符用以表示所有类型的已打开文件，包括管道(pipe)，FIFO，socket，终端设备和普通文件，针对每个进程，文件描述符都自成一套

按照惯例，大多数程序都期望能够使用3中标准的文件描述符，
	(文件描述符)		(用途)		(POSIX名称)		(stdio流)
    		0  		标准输入  		STDIN_FILENO		stdin
            1		标准输出		STDOUT_FILENO		stdout
            2		标准错误		STDERR_FILENO		stderr

在程序运行开始之前，shell代表程序打开这3个文件描述符。程序继承了shell文件描述符的副本-----在shell的日常操作中，这3个文件描述符始终是打开的(在交互式shell中，这3个文件描述符通常指向shell运行所在的终端)如果命令行指定对输入/输出进行重定向操作，那么shell会对文件描述符做适当修改，然后再启动程序
```

### 文件I/O操作的4个主要系统调用(编程语言和软件包会利用I/O函数库对它们进行间接调用)
```

+ fd = open(pathname, flags, mode)函数打开pathname所标识的文件，并返回文件描述符，用以在后续函数调用中指代打开的文件。如果文件不存在，open()函数可以创建，这取决于对位掩码参数flags的设置。
flags: 参数还可指定文件的打开方式:只读，只写，亦或是读写方式。
mode: 参数则指定了由open()调用创建文件的访问权限，如果open()函数并未创建文件，那么忽略或省略mode参数

+ numread = read(fd, buffer, count)调用从fd所指代的打开文件中读取至多count字节的数据，并存储到buffer中。read()调用的返回值为实际读取到的字节数。如果再无字节可读(例如:读到文件结尾符EOF时)，则返回值为0

+ numwritten = write(fd, buffer, count)调用则从buffer中读取多达count字节的数据写入fd所指代的已打开的文件中，write()函数调用的返回值为实际写入文件中的字节数，且有可能小于count

+ status = close(fd)在所有输入/输出完成后，调用close(), 释放文件描述符fd以及与之相关的内核资源
```

##### open()函数调用中的flags参数
```
	标志				用途				统一UNIX规范版本
	O_RDONLY		以只读方式打开				v3
    O_WRONLY		以只写方式打开				v3
    O_RDWR			以读写方式打开				v3

    O_CLOEXEC		设置close-ono-exec标志	  v4
    				(自Linux2.6.23版本开始)
    O_CREAT			若文件不存在则创建之		  v3
    O_DIRECT		无缓冲的输入/输出
    O_DIRECTORY		如果pathname不是目录，则失败 v4
    O_EXCL			结合O_CREAT参数使用，专门用于创建文件v3
    O_LARGEFILE		在32位系统中使用此标志打开大文件
    O_NOATIME		调用read()时,不修改文件最近访问时间
    				(自Linux2.6.8版本开始)
    O_NOCTTY		不要让pathname(所指向的终端设备) v3
    				成为控制终端
    O_NOFOLLOW		对符号链接不予解引用			v4
    O_TRUNC			截断已有文件，使其长度为零	  v3

    O_APPEND		总在文件末尾追加数据			v3
    O_ASYNC			当I/O操作可行时，产生信号
    				(signal)通知进程
    O_DSYNC			提供同步的I/O数据完整性		v3
    				自(Linux2.6.33版本开始)
    O_NONBLOCK		以阻塞方式打开				  v3
    O_SYNC			以同步方式写入文件			 v3
```

##### creat()系统调用
```
在早期UNIX实现中，open()只有两个参数，无法创建新文件，而是使用creat()系统调用来创建并打开一个新文件
#include <fcntl.h>
int creat(const char *pathname, mode_t mode);
				Returns file descriptor, or -1 on error

creat()系统调用根据 pathname 参数创建并打开一个文件,若文件已存在,则打开文件,并清空文件内容,将其长度清 0。creat()返回一文件描述符,供后续系统调用使用。
```

##### 读取文件内容 read()
```
#include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count);
				Returns number of bytes read, 0 on EOF, or -1 on error
```

##### 数据写入文件 write()
```
#include <unsitd.h>

ssize_t write(int fd, void *buffer, size_t count);

				Returns number of bytes written, or -1 on error
```

##### 关闭文件 close()
```
#include <unistd.h>

int close(int fd);
				Returns 0 on success, or -1 on error

close()能够捕获的错误有，企图关闭一个未打开的文件描述符，或者两次关闭同一文件描述符，也能捕获特定文件系统在关闭操作中诊断出的错误条件
针对特定文件系统的错误，NSF(网络文件系统)就是一例。如果NFS出现提交失败，这意味着数据没有抵达远程磁盘，随之将这一错误作为close()调用失败的原因传递给应用系统
```

##### 改变文件偏移量 lseek()
```
对于每个打开的文件，系统内核会记录其文件偏移量，有时也将偏移量称为读写偏移量或指针。文件偏移量是指执行下一个read()或wirte()操作的文件起始位置，会以相对于文件头部起始点的文件当前位置来表示。文件第一个字节的偏移量为0

#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
				Returns new file offset if successful,or -1 on error

offset参数指定了一个以字节为单位的数值，(SUSv3规定off_t数据类型为有符号整型数)whence参数则表明应参照哪个基点来解释offset参数，

SEEK_SET
	将文件偏移量设置为从文件头部起始点开始offset个字节
SEEK_CUR
	相对于当前文件偏移量，将文件偏移量调整offset个字节
SEEK_END
	将文件偏移量设置为起始于文件尾部的offset个字节。也就是说，offset参数应该从文件最后一个字节之后的下一个字节算起

在早期的UNIX实现中，whence参数用整数0，1,2来表示，而非SEEK*常量，BSD的早期版本使用另一套命名:L_SET, L_INCR和L_XTND来表示whence参数。

如果whence参数值为SEEK_CUR或SEEK_END，offset参数可以为正数也可以为负数:如果whence参数为SEEK_SET,offset参数值必须为非负数。
lseek()调用成功会返回新的文件偏移量。
获取文件偏移量当前的未知

curr = lseek(fd, 0, SEEK_CUR);

有些UNIX系统(Linux不在此列)实现类非标准的tell(fd)函数，其调用目的与lseek相同

lseek()调用只是调整内核中与文件描述符相关的文件偏移量记录，并没有引起对任何物理设备的访问

lseek()并不适用于所有类型的文件，不允许将lseek()应用于管道，FIFO，socket或者终端，一旦如此，调用将会失败，并将errno置为ESPIPE，另一方面，只要合情合理，也可以将lseek()应用于设备。例如，在磁盘或磁带上查找一处具体位置

offset参数和调用返回值的类型起初都是long型。早期的UNIX系统还提供seek()系统调用，当时这两个值为int型
```

##### 文件空洞
```
如果程序的文件偏移量已然跨越了文件结尾，然后再执行I/O操作，read()调用将返回0,表示文件结尾。有点令人惊讶的是，write()函数可以在文件结尾后的任意位置写入数据

从文件结尾后到新写入数据间的这段空间被称为文件空洞。从编程角度看，文件空洞中是存在字节的，读取空洞将返回以0(空字节)填充的缓冲区
然而，文件空洞不占用任何磁盘空间。直到后续某个时点，在文件空洞中写入数据，文件系统才会为之分配磁盘块。文件空洞的主要优势在于，与为实际需要的空字节分配磁盘块相比，稀疏填充的文件会占用较少的磁盘空间。核心转储文件(core dump)是包含空洞文件的常见例子

对于文件空洞不占用磁盘空间的说法，在大多数文件系统中，文件空间的分配是以块为单位。块的大小取决于文件系统，通常是1024字节，2048字节，4096字节。如果空洞的边界落在块内，而非恰好落在块边界上，则会分配一个完整的块来存储数据，块中与空洞相关的部分以空字节填充

SUSv3的posix_fallocate(fd, offset, len)规定，针对文件描述符fd所指代的文件，能确保按照由offset参数和len参数所确定的字节范围为其在磁盘上分配存储空间。这样，应用程序对文件的后续write()调用不会因磁盘空间耗尽而失败(否则，当文件中一个空洞被填满后，或者因其他应用程序消耗了磁盘空间时，都可能因磁盘空间耗尽而引发此类错误)。在过去,glibc库在实现posix_fallocate()函数时，通过向指定范围内的每个块写入一个值为0的字节以达到预期结果，自内核版本2.6.23开始，Linux系统提供了fallocate()系统调用，能更为高效地确保所需存储空间的分配。当fallocate()调用可用时，glibc库会利用其来实现posix_fallocate()函数的功能。
```



##### 通用I/O模型以外的操作: ioctl()

```
#include <sys/ioctl.h>

int ioctl(int fd, init request, ... /* argp */);
								Value returned on success depends on request, or -1 on error
```


