#include <iostream>
#include <cstring>
#include <vector>
#include <alibabacloud/oss/OssClient.h>
#include "mongoose/mongoose.h"
#include "logger/logger.h"

using namespace std;
using namespace AlibabaCloud::OSS;

string response_gen(string);

typedef struct AAA{
    int a;
} Aaa;

int putAliOss()
{
    string AccesskeyId = "LTAIzlOqVRk7g2IB";
    string AccessSecret = "FaQNdIaStZU1LzBN3IMsCiywODG6Mm";
    string Endpoint = "oss-cn-shanghai.aliyuncs.com";
    string BucketName = "classrvideo";
    string ObjectName = "test/test_111.mp4";// + fileName;//path + "/" + fileName;
    string UploadFileName = "test_111.mp4"; // fileName;//fileName;
    string CheckPintFilePath = "/home/debian/Cprojects/mongoose_http_message/build/"; //g_conf->check_point_file_path; //g_conf->check_point_file_path;
    
    // init
    InitializeSdk();
    ClientConfiguration conf;
    OssClient client(Endpoint, AccesskeyId, AccessSecret, conf);

    UploadObjectRequest request(BucketName, ObjectName, UploadFileName, CheckPintFilePath);
    auto outcome = client.ResumableUploadObject(request);
    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "ResumableUploadObject fail" <<
                  ",code:" << outcome.error().Code() <<
                  ",message:" << outcome.error().Message() <<
                  ",requestId:" << outcome.error().RequestId() << std::endl;
      LOG(INFO) << "hahahahahahhahahaha" << endl;
        ShutdownSdk();
      return -1;
    }

    cout << "upload success" << endl;
    return 0;
}

string response_gen(string content)
{
    string response_header = "HTTP/1.0 200 OK\r\n";
    string response_type = "Content-Type: application/json\r\n";
    string response_len = "Content-Length: ";

    string blank_line = "\r\n\r\n";

    char response_content[1024] = { 0 };
    sprintf(response_content, "%s", content.c_str());
    string response_rest = response_header + response_type + response_len + to_string(strlen(response_content)) + blank_line + response_content;
    cout<<response_rest << endl;
    return response_rest;
}

static void ev_hendler(struct mg_connection *c, int ev, void *p)
{
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *)p;
        cout << (hm->body).p << endl;
        response_gen("{\"name\":\"LiuDehua\"}");
        
        LOG(INFO) << "sadfasdfasdfasdf" << endl;
        putAliOss();
//        mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
        mg_printf(c, "%s", response_gen("{\"name\":\"LiuDehua\"}").c_str());

//        mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
//        mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    while (true) {
        struct mg_mgr mgr;
        struct mg_connection *c;

        mg_mgr_init(&mgr, nullptr);
        c = mg_bind(&mgr, "8087", ev_hendler);
        mg_set_protocol_http_websocket(c);

        for (;;)
            mg_mgr_poll(&mgr, 100);
    }

    return 0;
}
