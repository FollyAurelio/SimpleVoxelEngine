#ifndef PROGRAM_H
#define PROGRAM_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "gfx.h"

typedef struct gl_program
{
    unsigned int ID;

}gl_program;

gl_program CreateGLProgram(const char *VertexPath, const char *FragmentPath);
void UseGLProgram(gl_program Program);
void CheckShaderCompilationError(unsigned int Shader_ID);
void CheckProgramLinkError(unsigned int Program_ID);

#endif