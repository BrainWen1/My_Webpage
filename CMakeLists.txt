# 1. 指定CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称
project(PersonalWeb)

# 3. 设置C++标准（需C++11及以上，这里用C++17）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 包含头文件目录（httplib.h、json.hpp在当前目录）
include_directories(".")

# 5. 编译可执行文件（后端程序）
add_executable(run backend.cpp)

# 链接线程/套接字库：Windows用ws2_32，Linux/Mac用pthread
if(WIN32)
    target_link_libraries(run ws2_32)  # Windows需要链接ws2_32库
else()
    target_link_libraries(run pthread) # Linux/Mac需要链接pthread库
endif()

# 6. 链接线程库（cpp-httplib依赖pthread）
target_link_libraries(run pthread)

# 关键：每次编译时，自动复制 frontend.html 到 build 目录（替换成你的 HTML 路径）
set(FRONTEND_FILE "${CMAKE_SOURCE_DIR}/frontend.html")  # 假设 HTML 在项目根目录
add_custom_command(
    TARGET run POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${FRONTEND_FILE}
    $<TARGET_FILE_DIR:run>  # 复制到后端可执行文件所在目录（build 目录）
)