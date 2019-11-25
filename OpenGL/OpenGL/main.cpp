//
//  main.cpp
//  OpenGL
//
//  Created by 陈江林 on 2019/11/25.
//  Copyright © 2019 陈江林. All rights reserved.
//

#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

int main(){
    //初始化窗口
    glfwInit();
    /// 设置版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    /// 设置工作模式 设置成核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /// 兼容mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    /// 设置窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        cout << 'create window fail' << endl;
        glfwTerminate();
        return -1;
    }
    /// 渲染引擎
    while (!glfwWindowShouldClose(window)) {
        glClearColor(<#GLclampf red#>, <#GLclampf green#>, <#GLclampf blue#>, <#GLclampf alpha#>)
        /// 接受任何事件
        glfwPollEvents();
    }
    ///退出
    glfwTerminate();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}

