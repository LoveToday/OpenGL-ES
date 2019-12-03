//
//  main.cpp
//  OpenGL
//
//  Created by 陈江林 on 2019/11/25.
//  Copyright © 2019 陈江林. All rights reserved.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Shader.hpp"
using namespace std;


float vertices[] = {
    -0.5f, -0.5f, 0, 0.3f, 0.4f, 1.0f, //左下0
    0.5f, -0.5f, 0, 0.3f, 0.4f, 1.0f,  //右下1
    -0.5f, 0.5f, 0, 1.0f, 0.4f, 0.0f,  //左上2
    0.5f, 0.5f, 0, 0.3f, 0.4f, 1.0f    //右上3
};

int vertextIndex[] = {
    0, 1, 2,
    1, 2, 3
};

int vertexMyColorLocation;

bool init();

unsigned int VAOSet();

/// in 和 out是解决的GPU内部的问题
/// unifrom 是解决的CPU到GPU的问题




GLFWwindow *window;

int main(){
    
    bool result = init();
    
   
    
    if (!result) {
        return -1;
    }
    
    Shader shader = Shader();
    
    unsigned int VAO = VAOSet();
    
    glPolygonMode(GL_FRONT_AND_BACK, /*GL_FILL*/ GL_LINE);
    /// 渲染引擎
    while (!glfwWindowShouldClose(window)) {
        
        
        float timeValue = glfwGetTime();
        float greenValue = abs(sin(timeValue));
        glUniform4f(vertexMyColorLocation, 0.1f, greenValue, 0.1f, 1.0f);
        
        
        //设置颜色
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // 颜色设置整个区域
        glClear(GL_COLOR_BUFFER_BIT);
        
//        glUseProgram(shaderProgram);
        shader.useShader();
        
        glBindVertexArray(VAO);
        
        /// 绘制三角形  从0开始 取三个点
//        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        /// 缓冲交换等 交换缓存
        glfwSwapBuffers(window);
        /// 接受任何事件
        glfwPollEvents();
    }
    ///退出
    glfwTerminate();
    
    
    
    return 0;
}

bool init()
{
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
    window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    
    if (window == NULL) {
        cout << "create window fail" << endl;
        glfwTerminate();
        return false;
    }
    /// window 与上下文结合起来
    glfwMakeContextCurrent(window);
    /// gl 函数指针给到
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }
    return true;
}

unsigned int VAOSet(){
    unsigned int VBO, VAO, EBO; // ID
    /// 生成一个VAO
    glGenVertexArrays(1, &VAO);
    /// 生成两个VBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    /// opengl 程序绑定起来
    glBindVertexArray(VAO);
    
    // 绑定vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /// 绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
   
    
    
    /// 写值分配显存空间 创建显存  GL_STATIC_DRAW数据几乎没有改变
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertextIndex), vertextIndex, GL_STATIC_DRAW);
    
    /// 告诉 GPU内存的情况 值 的结构
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    /// 启用
    glEnableVertexAttribArray(0);
    
    
    
    /// 告诉 GPU内存的情况 值 的结构
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    /// 启用
    glEnableVertexAttribArray(1);
    
    
    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
    
//    glBindBuffer(GL_ARRAY_BUFFER, 1);
//    glBindVertexArray(1);
    
    return VAO;
}
