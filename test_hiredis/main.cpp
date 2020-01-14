#include <iostream>
#include <boost/asio/defer.hpp>
#include <hiredis/hiredis.h>
#include <unistd.h>

using namespace std;

int main()
{
    redisContext *c = redisConnect("127.0.0.1", 6379);

    if (c->err) {
        redisFree(c);
        cout << "Connect to redis filed\n";
        return 1;
    }

    cout << "connect to redis success" << endl;
    
    redisReply *reply;
    reply = (redisReply *)redisCommand(c, "SET %s %s", "name", "Hello World!!!!!!");

    redisReply *r = (redisReply *)redisCommand(c, "get name");

    cout << r->str << endl;
    (redisReply *)redisCommand(c, "del name");

    r = (redisReply *)redisCommand(c, "get name");
    if (r->str) {
        cout << r->str << endl;
    } else {
        cout << "name not found" << endl;
    }

    return 0;
}
