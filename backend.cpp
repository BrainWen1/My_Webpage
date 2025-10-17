// 引入cpp-httplib库（单头文件，直接包含即可）
#include "httplib.h"
// 引入JSON库（处理数据格式，也是单头文件）
#include "json.hpp"
#include <string>

// 用别名简化代码
using namespace httplib;
using json = nlohmann::json;

int main() {
    // 1. 创建HTTP服务器对象，监听8080端口
    Server svr;
    const int PORT = 8080;

    // 设置“静态文件根目录”（frontend.html所在的文件夹）
    svr.set_mount_point("/", "D:/PersonalWeb");  // 替换为你frontend.html的实际路径

    // 2. 定义接口：处理GET请求 /getUser（前端会请求这个地址拿数据）
    svr.Get("/getUser", [](const Request& req, Response& res) {
        // 设置响应头：允许跨域（本地开发也兼容，避免浏览器拦截）
        res.set_header("Access-Control-Allow-Origin", "*");

        // 3.构造个人信息数据（不用数据库，直接硬编码，实际项目会从数据库查）
        json user_data;
        user_data["nickname"] = "文斌";       // 昵称
        user_data["major"] = "计算机科学与技术";     // 专业
        user_data["intro"] = "大二在校生, 正在学习C++后端开发, 目标是大二暑期找到一份实习工作"; // 简介
        user_data["hobbies"] = {"编程", "蓝桥杯竞赛", "Web开发", "看技术视频"}; // 爱好（数组）
        user_data["skill"] = {"C++", "算法数据结构", "HTTP协议", "Linux基础", "Git"};    // 技能（数组）

        // 4. 关键修正：用 set_content 同时设置“JSON内容”和“内容类型”
        res.set_content(user_data.dump(4), "application/json"); 
        // 第一个参数：JSON字符串（user_data.dump(4) 会格式化JSON，更易读）
        // 第二个参数：内容类型（告诉前端“这是JSON数据”）
    });

    // 5. 启动服务器，打印提示信息
    std::cout << "Backend and Frontend is running! Visit: http://localhost:" << PORT << "/frontend.html" << std::endl;
    svr.listen("0.0.0.0", PORT); // 0.0.0.0表示允许本机所有IP访问

    return 0;
}