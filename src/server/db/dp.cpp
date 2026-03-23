#include "db.hpp"
#include <muduo/base/Logging.h>

//数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

//初始化数据库连接
MySql::MySql(){
    _conn = mysql_init(nullptr);
}
//释放数据库连接资源
MySql::~MySql(){
    if(_conn != nullptr){
        mysql_close(_conn);
    }
}
//连接数据库
bool MySql::connect(){
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
    password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if( p!= nullptr){
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "connenct mysql success!";
    }else{
        LOG_INFO << "connect mysql fail!";
    }
    return p;
}
//更新操作
bool MySql::update(string sql){
    if(mysql_query(_conn, sql.c_str())){
        LOG_INFO << __FILE__<< ":" << __LINE__ << ":"<< sql << "更新失效!";
        return false;
    }
    return true;
}
//查询操作
MYSQL_RES* MySql::query(string sql){
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失效!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL* MySql::getConnection(){
    return _conn;
}