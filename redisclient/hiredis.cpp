#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <hiredis/hiredis.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

int main()
{

    cout << "Start" << endl;

    unsigned int j, isunix = 0;
    redisContext *c;
    redisReply *reply;
    const char hostname[] = "127.0.0.1";
    int port = 6377;
  
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    if (isunix) {
        c = redisConnectUnixWithTimeout(hostname, timeout);
    } else {
        c = redisConnectWithTimeout(hostname, port, timeout);
    }
    
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    
    /* PING server */
    reply = (redisReply *)redisCommand(c, "PING");
    //printf("PING: %s\n", reply->str);
    if (!strcasecmp(reply->str, "PONG")) {
        cout << "PONG success" << endl;
    } else {
        cout << "PONG error: " << reply->str << endl;
        return EXIT_FAILURE;
    }
    freeReplyObject(reply);

    /* set a key */
    reply = (redisReply *)redisCommand(c, "SET %s %s", "foo", "Hello World");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply *)redisCommand(c, "GET %s", "foo");
    printf("GET: %s\n",reply->str);
    freeReplyObject(reply);


    reply = (redisReply *)redisCommand(c, "SET %s %lld", "counter", 1);
    cout << "set result " << reply->str << endl;
    freeReplyObject(reply);

    for (j = 0; j < 10000; j++) {
        reply = (redisReply *)redisCommand(c, "INCR counter");
    }
    freeReplyObject(reply);

   // reply = (redisReply *)redisCommand(c, "GET counter");
   // printf("GET counter, value is %lld\n", reply->str);
   // freeReplyObject(reply);

   // reply = (redisReply *)rediscommand(c, "SET number_test %d", "1");
    reply = (redisReply *)redisCommand(c, "GET counter");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    /* Try a GET and two INCR */
    return 0;
}

