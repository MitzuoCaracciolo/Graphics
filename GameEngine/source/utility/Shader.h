#pragma once
#include<GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
class Shader
{
public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
};

