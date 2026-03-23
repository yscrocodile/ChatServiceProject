#include "usermodel.hpp"
#include "db.hpp"

//User表的增加方法
bool UserModel::insert(User& user){
    //组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert User(name, password, state) values('%s', '%s', '%s')",
     user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());
    MySql mysql;
    if(mysql.connect()){
        if(mysql.update(sql)){
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

//根据用户id查询
User UserModel::query(int id){
    //组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from User where id = %d", id);
    MySql mysql;
    if(mysql.connect()){
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr){
            MYSQL_ROW row = mysql_fetch_row(res);
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setPwd(row[2]);
            user.setState(row[3]);
            mysql_free_result(res);
            return user;
        }else{

        }
    }
    return false;
}
//更新用户状态
bool UserModel::updateState(User& user){
    //组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update User set state = '%s' where id = %d", user.getState().c_str(),user.getId());
    MySql mysql;
    if(mysql.connect()){
        if(mysql.update(sql)){
            return true;  
        }
    }
    return false;
}

// 重置用户的状态信息
void UserModel::resetState()
{
    //组装sql语句
    char sql[1024] = {"update User set state = 'offline' where state = 'online'"};
    MySql mysql;
    if(mysql.connect()){
       mysql.update(sql);
    }
}