#include "shaders.h"

const char *vsTrianglePosition ="#version 330 core\n"
                            "layout (location = 0) in vec3 aPos;\n"

                            "void main()\n"
                            "{\n"
                            "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                            "}\n";

const char *fsOrange =      "#version 330 core\n"
                            "out vec4 FragColor;\n"
                            "void main()\n"
                            "{\n"
                            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                            "}\n";

const char *vsTrianglePositionColor = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    //"layout (location = 1) in vec3 acolor;"
                                    "layout (location = 1) in vec2 aTexCoord;"
                                    "uniform float offset;\n"
                                    "uniform mat4 model;\n"
                                    "uniform mat4 view;\n"
                                    "uniform mat4 projection;\n"
                                    //"out vec3 ourColor;"
                                    "out vec2 TexCoord;"
                                    "void main()\n"
                                    "{\n"
                                    "gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                                    //"ourColor = acolor;"
                                    "TexCoord = aTexCoord;"
                                    "}\n";

const char *fsColor = "#version 330 core\n"
                                        //"in vec3 ourColor;"
                                        "out vec4 FragColor;\n"
                                        "in vec2 TexCoord;\n"
                                        "uniform sampler2D texture1;\n"
                                        "uniform sampler2D texture2;\n"
                                        "uniform float alpha;\n"
                                        "void main()\n"
                                        "{\n"
                                        "FragColor = mix(texture(texture1, TexCoord) , texture(texture2, TexCoord), alpha);\n"
                                        
                                        "}\n";