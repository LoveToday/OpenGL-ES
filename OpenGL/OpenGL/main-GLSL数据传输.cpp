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
using namespace std;

float vertices[] = {
    -0.5f, -0.5f, 0, //左下0
    0.5f, -0.5f, 0,  //右下1
    -0.5f, 0.5f, 0,  //左上2
    0.5f, 0.5f, 0    //右上3
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

//顶点着色器
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"out vec4 myColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"myColor = vec4(0.5f, 0.9f, 0.4f, 1.0f);\n"
//"}\0";

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//片段着色器 in 和 out的传值
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 myColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = myColor;\n"
//"}\n\0";

//片段着色器 in 和 out的传值
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 myColor;\n"
"void main()\n"
"{\n"
"   FragColor = myColor;\n"
"}\n\0";

GLFWwindow *window;

int main(){
    
    bool result = init();
    
   
    
    if (!result) {
        return -1;
    }
    
    int success;
    char infoLog[512];
    
    /// 创建着色器对象
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    /// 源码与着色器对象绑定
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    /// 编译
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout<<"ERROR: VertexShader Compile Fail"<<infoLog<<endl;
    }
    
    /// 创建着色器对象
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    /// 源码与着色器对象绑定
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    /// 编译
    glCompileShader(fragmentShader);
    
    //检查片段着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout<<"ERROR: FragmentShader Compile Fail"<<infoLog<<endl;
    }
    
    
    //// 创建着色器程序
    int shaderProgram = glCreateProgram();
    /// 着色器放到程序里面
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);
    
    //检查着色器链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout<<"ERROR: Shader Link Fail"<<infoLog<<endl;
    }
    
    vertexMyColorLocation = glGetUniformLocation(shaderProgram, "myColor");
    
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    unsigned int VAO = VAOSet();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL /*GL_LINE*/);
    /// 渲染引擎
    while (!glfwWindowShouldClose(window)) {
        
        
        float timeValue = glfwGetTime();
        float greenValue = abs(sin(timeValue));
        glUniform4f(vertexMyColorLocation, 0.1f, greenValue, 0.1f, 1.0f);
        
        
        //设置颜色
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // 颜色设置整个区域
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
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
    /// 生成一个VBO
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    /// 启用
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
    return VAO;
}
