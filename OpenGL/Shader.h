#pragma once

#ifndef _SHADER_H_
#define _SHADER_H_

#include "StandardIncludes.h"

class Shader
{
	GLuint programID = 0;
	GLuint attrVertices = 0;
	GLuint attrWVP = 0;
	GLuint attrColors = 0;

	GLint result = GL_FALSE;
	int infoLogLength = 0;
public:
	Shader() = default;
	~Shader();

	GLuint GetProgramID() { return programID; }
	GLuint GetAttrVertices() { return attrVertices; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint GetAttrWVP() { return attrWVP; }
	GLuint GetAttrColors() { return attrColors; }

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int infoLength, GLuint id);
};

#endif

