//
//  Shader.cpp
//  OpenGL
//
//  Created by 陈江林 on 2019/11/30.
//  Copyright © 2019 陈江林. All rights reserved.
//

#include "Shader.hpp"
using namespace std;
Shader:: Shader(void)
{
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTextCoord;\n"
    "out vec2 TextCoord;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "TextCoord = aTextCoord;\n"
    "}\0";
    
    
    //片段着色器 in 和 out的传值
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TextCoord;\n"
    "uniform sampler2D ourTexture1;\n"
    "uniform sampler2D ourTexture2;\n"
    "void main()\n"
    "{\n"
    "FragColor = mix(texture(ourTexture1, TextCoord), texture(ourTexture2, TextCoord), 0.8);\n"
    "}\n\0";
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
    shaderProgram = glCreateProgram();
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
    
    //    vertexMyColorLocation = glGetUniformLocation(shaderProgram, "myColor");
    
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}

Shader::~Shader(void)
{
    
}

void Shader::useShader()
{
    glUseProgram(shaderProgram);
}
