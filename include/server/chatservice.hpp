#ifndef CHATSERVICE_H
#define CHARSERVICE_H

#include "public.hpp"
#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"
using json = nlohmann::json;
using namespace std;
using namespace muduo;
using namespace muduo::net;
//定义事件处理函数的类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js , Timestamp)>;
class ChatService{
public:
    //获取单例对象的接口函数
    static ChatService* instance();
    //处理登陆业务
    void login(const TcpConnectionPtr &conn, json &js , Timestamp);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js , Timestamp);
    //获取消息对应的处理器
    MsgHandler getHandler(int msg);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr& conn, json& js, Timestamp time);
    //处理服务器ctrl+c结束的函数
    void reset();
    //添加好友业务
    void addFriend(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
     // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);
private:
    ChatService();
    //储存消息id和其他对应的业务的方法
    unordered_map<int, MsgHandler> msgHandlerMap;
    //定义互斥锁
    mutex _connMutex;
    //储存在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    //数据操作类
    UserModel usermodel;
    OfflineMessageModel offlinemessagemodel;
    FriendModel friendmodel;
    GroupModel _groupModel;
    Redis _redis;
};


#endif