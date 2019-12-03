//
//  Shader.hpp
//  OpenGL
//
//  Created by 陈江林 on 2019/11/30.
//  Copyright © 2019 陈江林. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp
/// 表示只编译一次
#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
    
    
public:
    int shaderProgram;
    Shader(void);
    ~Shader(void);
    void useShader();
};

#endif /* Shader_hpp */
