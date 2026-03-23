#include "offlinemessagemodel.hpp"
#include "db.hpp"

// 存储用户的离线消息
void OfflineMessageModel::insert(int userid, string msg)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into OfflineMessage values('%d', '%s')", userid, msg.c_str());
    MySql mysql;
    if(mysql.connect()){
        mysql.update(sql);
    }
}


// 删除用户的离线消息
void OfflineMessageModel::remove(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "delete from OfflineMessage where userid = %d", userid);
    MySql mysql;
    if(mysql.connect()){
        mysql.update(sql);
    }
}

// 查询用户的离线消息
vector<string> OfflineMessageModel::query(int userid)
{
    vector<string> vec;
    char sql[1024] = {0};
    sprintf(sql, "select message from OfflineMessage where userid = %d", userid);
    MySql mysql;
    if(mysql.connect()){
        auto res = mysql.query(sql);
        MYSQL_ROW temp;
        while((temp = mysql_fetch_row(res)) != nullptr){
            vec.push_back(temp[0]);
        }
        mysql_free_result(res);
        return vec;
    }
    return vec;
}