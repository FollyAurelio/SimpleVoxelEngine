#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
}

void CheckShaderCompilationError(unsigned int Shader){
    int success;
    char InfoLog[512];
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, InfoLog);
        printf("ERROR shader compilation failed\n%s",InfoLog);
    }
}

void CheckProgramLinkError(unsigned int Program){
    int success;
    char InfoLog[512];
    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(Program, 512, NULL, InfoLog);
        printf("ERROR program link failed\n%s",InfoLog);

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
    float vertices[] = {-0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                         -0.5f, 0.5f, 0.0f,
                         0.5f, 0.5f, 0.0f};
                        
    float vertices1[] = {0.75f, 0.75f, 0.0f,
                        1.0f, 0.75f, 0.0f,
                         0.75f, 1.0f, 0.0f,
                         1.0f, 1.0f, 0.0f};

    unsigned int indices[] = {0, 1, 2, 1, 2, 3};
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
     
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    
    const char *VertexShaderSource = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                    "}\n";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderCompilationError(vertexShader);

    const char *FragementShaderSource = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                        "}\n";

    const char *RedFragmentShaderSource = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                        "}\n";
    unsigned int FragmentShader;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragementShaderSource, NULL);
    glCompileShader(FragmentShader);
    CheckShaderCompilationError(FragmentShader);


    unsigned int RedFragmentShader;
    RedFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(RedFragmentShader, 1, &RedFragmentShaderSource, NULL);
    glCompileShader(RedFragmentShader);
    CheckShaderCompilationError(RedFragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);
    CheckProgramLinkError(shaderProgram);

    unsigned int RedShaderProgram;
    RedShaderProgram = glCreateProgram();
    glAttachShader(RedShaderProgram, vertexShader); 
    glAttachShader(RedShaderProgram, RedFragmentShader);
    glLinkProgram(RedShaderProgram);
    CheckProgramLinkError(RedShaderProgram);    

    glDeleteShader(vertexShader);
    glDeleteShader(FragmentShader);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);


    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window)){
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUseProgram(RedShaderProgram);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }   
    glfwTerminate();
    return 0;
}   