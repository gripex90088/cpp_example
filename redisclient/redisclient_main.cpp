#include <iostream>
#include <vector>
#include <string>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/io_service.hpp>
#include <redisclient/redissyncclient.h>

using namespace std;

int redisclient_main()
{
    boost::asio::ip::address address = boost::asio::ip::address::from_string("127.0.0.1");
    const unsigned short port = 6379;
    boost::asio::ip::tcp::endpoint endpoint(address, port);

    boost::asio::io_service ioService;
    redisclient::RedisSyncClient redis(ioService);
    boost::system::error_code ec;

    redis.connect(endpoint, ec);

    if (ec) {
        cerr << "Can't connect to redis: " << ec.message() << endl;
        return EXIT_FAILURE;
    }

    redisclient::RedisValue result;

    result = redis.command("SET", {"key", "set_value"});

    if (result.isError()) {
        cerr << "SET error: " << result.toString() << "\n";
        return EXIT_FAILURE;
    }

    result = redis.command("GET", {"key"});
    if ( result.isOk()) {
        cerr << "GET: " << result.toString() << "\n";
    } else {
        cerr << "GET error: " << result.toString() << "\n";
        return EXIT_FAILURE;
    }

    result = redis.command("GET", {"key"});
    if ( result.isOk()) {
        cerr << "GET: " << result.toString() << "\n";
    } else {
        cerr << "GET error: " << result.toString() << "\n";
        return EXIT_FAILURE;
    }
    
    result = redis.command("DEL", {"key"});
    if (result.isError()) {
        cerr << "DEL error: " << result.toString() << "\n";
        return EXIT_FAILURE;
    } else {
        cerr << "DEL success" << endl;
    }

    result = redis.command("GET", {"key"});
    if (result.isOk()) {
        cerr << "GET: " << result.toString() << "\n";
    } else {
        cerr << "GET error: " << result.toString() << "\n";
        return EXIT_FAILURE;
    }
    


    
    return 0;
}
