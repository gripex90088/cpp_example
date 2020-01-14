#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

// bindata待编码数据buffer base64编码后数据buffer binlength 待编码数据大小
char *base64_encode(const char *bindata, char *base64, int binlength);
// base64编码字符串 bindata解码后buffer
int base64_decode(const char *base64, char *bindata);

int main()
{
    FILE *fp = NULL;
    unsigned int imageSize; // 图片字节数
    char *imageBin;
    char *imageBase64;
    char *imageOutput;
    size_t result;
    char *ret;
    unsigned int base64StrLength;

    fp = fopen("a.png", "rb"); // 待编码图片
    if (NULL == fp) {
        cout << "file open failed\n";
        return -1;
    }

    // 获取图片大小
    fseek(fp, 0L, SEEK_END);
    imageSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // 分配内存存储整个图片
    imageBin = (char *)malloc(sizeof(char)*imageSize);
    if (NULL == imageBin) {
        cout << "malloc failed\n";
        return -1;
    }

    // 读取图片
    result = fread(imageBin, 1, imageSize, fp);
    if (result != imageSize) {
        cout << "file read failed\n";
        return -1;
    }
    fclose(fp);

    // 分配编码后图片所在buffer
    imageBase64 = (char *)malloc(sizeof(char)*imageSize * 2);
    if (NULL == imageBase64) {
        cout << "\n";
        return -1;
    }

    base64_encode(imageBin, imageBase64, imageSize);
}

const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char *base64_encode(const char *bindata, char *base64, int binlength)
{
    int i, j;
    unsigned char current;

    for (i = 0; j < binlength; i += 3) {
        current = (bindata[i] >> 2);
    }
    return 0;
}
