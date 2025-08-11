#include <stdio.h>
#include <math.h>
#include "gfx.h"
#include "program.h"
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cglm/struct.h>

vec3s cameraPos = {0.0f, 0.0f, 3.0f};
vec3s cameraFront = {0.0f, 0.0f, -1.0f};
vec3s cameraUp = {0.0f, 1.0f, 0.0f};
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window,float *alpha){
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        *alpha += 0.001f;
        }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        *alpha -= 0.001f;
        }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        cameraPos = glms_vec3_add(cameraPos, glms_vec3_scale(cameraFront, cameraSpeed));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos = glms_vec3_sub(cameraPos, glms_vec3_scale(cameraFront, cameraSpeed));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraPos = glms_vec3_sub(cameraPos, glms_vec3_scale(glms_normalize(glms_cross(cameraFront, cameraUp)), cameraSpeed));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraPos = glms_vec3_add(cameraPos, glms_vec3_scale(glms_normalize(glms_cross(cameraFront, cameraUp)), cameraSpeed));
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
                        
    float vertices1[] = {
                        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

                        

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
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),(void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float),(void*)(3*sizeof(float)));
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

    vec3s cubePositions[][3] = {{0.0f, 0.0f, 0.0f},
                            { 2.0f, 5.0f, -15.0f},
                            {-1.5f, -2.2f, -2.5f},
                            {-3.8f, -2.0f, -12.3f},
                            { 2.4f, -0.4f, -3.5f},
                            {-1.7f, 3.0f, -7.5f},
                            { 1.3f, -2.0f, -2.5f},
                            { 1.5f, 2.0f, -2.5f},
                            { 1.5f, 0.2f, -1.5f},
                            {-1.3f, 1.0f, -1.5f}};

    
    
    mat4s model = glms_mat4_identity();
    mat4s view; 
    mat4s perspective = glms_mat4_identity();
    perspective = glms_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    float alpha = 0.2f;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window, &alpha);
        glfwSwapBuffers(window);
        glfwPollEvents();        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
        UseGLProgram(InputShaderProgram);
        glUniform1f(glGetUniformLocation(InputShaderProgram.ID, "offset"), 0.25f);
        glUniform1f(glGetUniformLocation(InputShaderProgram.ID, "alpha"), alpha);

        glBindVertexArray(VAO1);
        view = glms_lookat(cameraPos, glms_vec3_add(cameraPos, cameraFront), cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(InputShaderProgram.ID, "view"), 1, GL_FALSE, view.raw[0]);
        glUniformMatrix4fv(glGetUniformLocation(InputShaderProgram.ID, "projection"), 1, GL_FALSE, perspective.raw[0]);

        
        
        for(int i = 0; i < 10 ; i++){
            model = glms_mat4_identity();
            model = glms_translate(model, *cubePositions[i]);
            model = glms_rotate(model, (float)glfwGetTime() * glm_rad((float)(20.f * i)), (vec3s){1.0f,0.3f,0.5f});

            glUniformMatrix4fv(glGetUniformLocation(InputShaderProgram.ID, "model"), 1, GL_FALSE, model.raw[0]);
        

        
            glDrawArrays(GL_TRIANGLES, 0, 36);}
        
        
        
       
              
        
        
        //glUseProgram(RedShaderProgram);
        //glBindVertexArray(VAO1);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }   
    glfwTerminate();
    return 0;
}   