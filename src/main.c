#include <stdio.h>
#include <math.h>
#include "gfx.h"
#include "program.h"
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cglm/struct.h>


void framebuffer_size_callback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window,float *alpha){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        *alpha += 0.001f;
        }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        *alpha -= 0.001f;
        }
        }
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    if (window == NULL){
        printf ("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD\n");
        return -1;

    }
    glViewport(0, 0, 800, 600);
    float vertices[] = {-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
                        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
                         -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
                         0.5f, 0.5f, 0.0f , 1.0f, 1.0f, 0.0f,       1.0f, 1.0f};
                        
    float vertices1[] = {0.75f, 0.75f, 0.0f,  
                        1.0f, 0.75f, 0.0f, 
                         0.75f, 1.0f, 0.0f,   
                         1.0f, 1.0f, 0.0f,  };

    unsigned int indices[] = {0, 1, 2, 1, 2, 3};
    unsigned int indicesTriangle[] = {0, 1, 2};
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
     
    unsigned int EBO;
    glGenBuffers(1, &EBO);
   
    gl_program shaderProgram = CreateGLProgram(vsTrianglePosition, fsOrange);
    gl_program InputShaderProgram = CreateGLProgram(vsTrianglePositionColor, fsColor);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    unsigned VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width2, height2, nrChannels2;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data2 = stbi_load("images/awesomeface.png", &width2, &height2, &nrChannels2, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);

    UseGLProgram(InputShaderProgram);
    glUniform1i(glGetUniformLocation(InputShaderProgram.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(InputShaderProgram.ID, "texture2"), 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    
    vec3s scale = {0.0f, 0.0f, 1.0f};
    vec3s transalation = {0.5f, -0.5f, 0.0f};
    mat4s trans = glms_mat4_identity();
    float alpha = 0.2f;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window)){
        processInput(window, &alpha);
        glfwSwapBuffers(window);
        glfwPollEvents();        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        UseGLProgram(InputShaderProgram);
        glUniform1f(glGetUniformLocation(InputShaderProgram.ID, "offset"), 0.25f);
        glUniform1f(glGetUniformLocation(InputShaderProgram.ID, "alpha"), alpha);

        glBindVertexArray(VAO);
        trans = glms_mat4_identity();
        glUniformMatrix4fv(glGetUniformLocation(InputShaderProgram.ID, "transform"), 1, GL_FALSE, trans.raw[0]);

        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        trans = glms_translate(trans, transalation);
        scale.x = (float)fabs(sin(glfwGetTime()));scale.y = (float)fabs(sin(glfwGetTime()));
        trans = glms_scale(trans, scale);
       
        glUniformMatrix4fv(glGetUniformLocation(InputShaderProgram.ID, "transform"), 1, GL_FALSE, trans.raw[0]);        
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glUseProgram(RedShaderProgram);
        //glBindVertexArray(VAO1);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }   
    glfwTerminate();
    return 0;
}   