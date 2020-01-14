#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define N 4096

/**
 * error code,
 * error msg
 * error describe
 */
void send_err();

/*
 * write back header
 */
void send_header(char * type);

/**
 * int status: error code
 * char *title: error title
 * char * text: error description
 */
void send_err(int status, char *title, char *text)
{

    send_header("text/html");
    printf("<html><head><title>%d %s</title></head>", status, title);
    printf("<body bgcolor=\"green\"> <h5>%d %s</h5>", status, title);
    printf("%s\n", text);
    printf("<hr/></body>\n</html>\n");
    fflush(stdout);
    exit(1);

}

void send_header(char * type)
{
    
    // HTTP/1.1 200 OK   // response line,  including message protocol and version, status code and status description
    // Content-Type: texe/plain; charset=utf-8
    // Content-Length: 100   if the writing be accurate, otherwise it will not be written
    // Connection: close
    // \r\n
    
    printf("%s %d %s \r\n", "HTTP/1.1", 200, "OK");
    printf("Content-Type:%s\r\n", type);
    printf("Connection:close\r\n");
    printf("\r\n");

}

int main(int argc, char *argv[])
{
    char line[N];
    char method[N], path[N], protocol[N];

    FILE *ff;
    ff =fopen("i.txt", "w");
    if (ff == NULL) {
        printf("open file error");
        fclose(ff);
        exit(1);
    } else {

        fwrite("aaaaa", 12, 12, ff);
        fclose(ff);
    }


    char *file;
    struct stat sbuf;
    FILE *fp;
    char ich;

    char *dot, *type;
    if (argc != 2) 
        send_err(500, "500", "500");
 
    // change process working direcotry
    if (chdir(argv[1]) == -1) 
        send_err(500, "Internal Server Error", "Content error");

    if (fgets(line, N, stdin) == NULL) {
        send_err(500, "aa", "aa");
    }
    
    if (sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol) != 3) {
        send_err(500, "aa", "aa");
    }

    while(fgets(line, N, stdin) != NULL) {
        // http protocol end with '\r\n'
        if (strcmp(line, "\r\n")) {
            break;
        }
    }

    if (strcmp(method, "GET") != 0) {
        send_err(500, "100", "500");
    }

    if (path[0] != '/') {
        send_err(500, "200", "200");
    }

    file = path + 1;
   
    // get file status
    if (stat(file, &sbuf) < 0 ) {
        send_err(404, "Not Found", "500");
    }

    fp = fopen(file, "r");
    if (fp == NULL) {
        send_err(500, "500", "500");
    }
    
    // write back data by byte
    dot = strrchr(file, '.');
    if (dot == NULL) {
        type = "text/plain; charset=utf-8";
    } else if (strcmp(dot, ".c") == 0) {
        type = "text/plain;charset=utf-8";
    } else if (strcmp(dot, ".txt") == 0) {
        type = "text/plain;charset=utf-8";
    } else if (strcmp(dot, ".html") == 0) {
        type = "text/html;charset=ios-8859-1";
    } else {
        type = "text/plain;charset=ios-8859-1";
    }

    send_header(type);
    while ( (ich = getc(fp)) != EOF) {
        putchar(ich);
    }

    fflush(stdout);
    fclose(fp);
    
    return 0;
}


