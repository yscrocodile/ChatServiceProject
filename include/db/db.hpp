#ifndef DB_H
#define DB_H
#include <string>
#include <mysql/mysql.h>
using namespace std;

class MySql{
public:
    //初始化连接
    MySql();
    //释放数据库连接资源
    ~MySql();
    //连接数据库
    bool connect();
    //更新操作
    bool update(string sql);
    //查询操作
    MYSQL_RES* query(string sql);
    //获取连接
    MYSQL* getConnection();
private:
    MYSQL *_conn;
};

#endif