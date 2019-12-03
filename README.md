# OpenGL-ES
OpenGL

GLFW生成窗口，支持Opengl上下文

GLAD支持不同的软硬件环境

2.glm对于矩阵的缩放、旋转、位移等
头文件

    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
使用了三个函数

    glm:scale
    glm:rotate
    glm:translate

3.void glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)

    通过一致变量（uniform修饰的变量）引用将一致变量值传入渲染管线。

    location : uniform的位置。
    count : 需要加载数据的数组元素的数量或者需要修改的矩阵的数量。
    transpose : 指明矩阵是列优先(column major)矩阵（GL_FALSE）还是行优先(row major)矩阵（GL_TRUE）。
    value : 指向由count个元素的数组的指针。

