/*
 * Connection.h
 *
 *  Created on: Jul 19, 2019
 *      Author: xuxing
 */

#ifndef BASE_TCPCONNECTION_H_
#define BASE_TCPCONNECTION_H_
#include "noncopyable.h"
#include "StringPiece.h"
#include "Types.h"


namespace my_muduo {

namespace net {

class Channel;
class EventLoop;
class Socket;

class TcpConnection : noncopyable {
					//public std::enable_shared_from_this<TcpConnection>{
};

}  // namespace net

}  // namespace my_muduo



#endif /* BASE_TCPCONNECTION_H_ */
