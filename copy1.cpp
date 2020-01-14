#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define LEN 40


class Aa {

public:
	int ccc(int a, int b) {
		printf("aaa\n");
		return 1;
	}

	int ccc(char a) {
		printf("bbbbbb\n");
		return 2;
	}

	char ccc(int a, char b) {
		printf("ccc\n");
		return 'a';
	}
};

int main(int argc, char * argv[])
{
	FILE *in, *out;
	int ch;
	char name[LEN];
	int count = 0;

	// 检查命令行参数
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// 设置输入
	if ((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "I couldn't open the file \"%s\"%n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// 设置输入
	strncpy(name, argv[1], LEN - 5); // 拷贝文件名
	name[LEN - 5] = '\0';
	strcat(name, ".red");
	if ((out = fopen(name, "w")) == NULL) {
		fprintf(stderr, "Can't create output file.\n");
		exit(3);
	}

	// 拷贝数据
	while((ch = getc(in)) != EOF) {
		if (count++ % 3 == 0) {
			putc(ch, out); // 打印3个字符中的第1个字符
		}
	}

	// 收尾工作
	if (fclose(in) != 0 || fclose(out) != 0)
		fprintf(stderr, "Error in closing files\n");

	return 0;
}
