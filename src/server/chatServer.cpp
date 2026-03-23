#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"
#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

// 初始化
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg):
                       _server(loop, listenAddr, nameArg), _loop(loop)
{
    //注册回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setConnectionCallback(std::bind(&ChatServer::onConnect, this, _1));

    //线程数量
    _server.setThreadNum(12);
}
// 启动
void ChatServer::start()
{
    _server.start();
}

// 处理连接回调函数
void ChatServer::onConnect(const TcpConnectionPtr &conn)
{
    //客户端断开连接
    if(!conn->connected()){
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
// 处理读写事件回调函数
void ChatServer::onMessage(const TcpConnectionPtr & conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据反序列化
    json js = json::parse(buf);
    //解耦业务模块和网络模块代码
    //通过json["msgId"]获取=》业务handler=》conn js tim
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    msgHandler(conn, js, time);
}