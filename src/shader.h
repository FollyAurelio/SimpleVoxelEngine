#ifndef SHADER_H
#define SHADER_H

#include "gfx.h"
#include "rs.h"

class Shader
{
public:
	unsigned int handle;
	Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
	void use();
	void destroy();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMatrix4(const std::string &name, glm::mat4 m) const;
	void setVector3(const std::string &name, glm::vec3 v) const;
	void setVector4(const std::string &name, glm::vec4 v) const;
};

#endif
