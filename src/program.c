#include "program.h"

/*static const char* _fileRead(const char *Path){
    char Source[512];
    FILE *pFile = fopen(Path, "rt");
    if (pFile == NULL) {
        fprintf(stderr, "error loading shader at %s\n", Path);
        exit(1);
    }
    char temp[50];
    while (fgets(temp, 50, pFile) != NULL)
    {
        strcat(Source,temp);
    }
    fclose(pFile);
    char *returned = Source;
    return returned;
}*/

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

gl_program CreateGLProgram(const char *VertexSource, const char *FragmentSource){
    
    unsigned int VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, (const GLchar *const *)&VertexSource, NULL);
    glCompileShader(VertexShader);
    CheckShaderCompilationError(VertexShader);

    unsigned int FragmentShader;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, (const GLchar *const *)&FragmentSource, NULL);
    glCompileShader(FragmentShader);
    CheckShaderCompilationError(FragmentShader);

    gl_program self;
    self.ID = glCreateProgram();
    glAttachShader(self.ID, VertexShader);
    glAttachShader(self.ID, FragmentShader);
    glLinkProgram(self.ID);
    CheckProgramLinkError(self.ID);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    return self;

}

void UseGLProgram(gl_program Program){
    glUseProgram(Program.ID);
    }