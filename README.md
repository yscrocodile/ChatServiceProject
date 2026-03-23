基于muduo库的集群聊天服务器项目，支持多终端设备同时访问、分布式多服务器响应。可以部署在Nginx tcp负载均衡环境下。c++语言开发，用到MySQL、Redis等技术栈。

📘 项目 README（chatRobotProject） 项目简介 一个基于 C++ 的简易聊天系统，包括:

服务端：ChatServer 客户端：ChatClient 基于 JSON 协议（nlohmann::json） 支持用户注册/登录、一对一聊天、群聊、加好友、创建/加入群 使用 socket + 线程（客户读写分离 + 信号量同步） 📁 目录结构 CMakeLists.txt：根 CMake 配置 src client/main.cpp：客户端主程序 server/main.cpp, chatServer.cpp, chatservice.cpp：服务端逻辑 db/, model/, redis/：持久层/业务层/Redis 协议 include：头文件 json.hpp：nlohmann::json bin：可执行文件输出 ⚙️ 功能功能点（客户端视角） 启动即与服务端建立 TCP 连接 登录 / 注册 登录后自动: 显示用户信息、好友列表、群组列表 接收并展示离线消息（C2C + 群） 命令格式： help chat:: addfriend: creategroup:: addgroup: groupchat:: loginout 🔧 编译运行

生成构建
cd chatRobotProjectmkdir -p build && cd buildcmake ..make 2. 启动服务端 假设端口 6000，在本机执行：

./bin/ChatServer 6000 3. 启动客户端 连接本机服务端：

./bin/ChatClient 127.0.0.1 6000 Windows 环境下请使用类 UNIX 兼容的编译工具（CMake + MinGW 或 WSL），并确保 socket 头 <sys/socket.h> 可用。 你当前的代码是 POSIX API，原生 Windows 需调整为 WinSock。

🧩 数据协议（JSON） 客户端/服务端（msgid，中心字段对应服务器命令）：

REG_MSG / REG_MSG_ACK LOGIN_MSG / LOGIN_MSG_ACK ONE_CHAT_MSG GROUP_CHAT_MSG ADD_FRIEND_MSG CREATE_GROUP_MSG ADD_GROUP_MSG LOGINOUT_MSG 🧪 使用流程（典型） 启动 ChatServer 启动 ChatClient 输入： 1 -> 用户 ID / 密码 -> 登陆 登陆成功后自动刷新自身、好友、群列表 命令 help 查看客户端指令 互发消息（chat / groupchat） 💡 代码重点说明 main.cpp：

readTaskHandler()：子线程循环 recv()，处理消息并 sem_post(&rwsem)（同步注册/登录） mainMenu()：字符串命令解析映射 commandHandlerMap getCurrentTime()：聊天时间戳 include 里封装实体类：

User, Group, GroupUser 🛠️ 扩展建议 增加命令行参数校验与错误处理（当前 send 失败仅输出，不重试） 加入 select / poll + 非阻塞套接字优化 插件化命令、按键历史命令 在服务端加认证 JWT / 逻辑更完整、持久化脱离当前简单 DB 支持文件传输、通知、在线状态实时广播
