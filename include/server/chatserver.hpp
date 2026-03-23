#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include "public.hpp"

using namespace muduo::net;
using namespace muduo;

class ChatServer{
public:
    //初始化
    ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);
    //启动
    void start();
private:
    //处理连接回调函数
    void onConnect(const TcpConnectionPtr&);
    //处理读写事件回调函数
    void onMessage(const TcpConnectionPtr &,
                   Buffer *,
                   Timestamp);
    //组合的muduo库
    TcpServer _server;
    //循环对象指针
    EventLoop *_loop;

};

#endif
