#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Shader.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh();

	void Create(Shader* _shader);
	void Render(glm::mat4 _wvp);
	void RotateWorld(float _angle, glm::vec3 axis);

private:
	Shader* shader = nullptr;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLubyte> indexData;
	glm::mat4 world = glm::mat4(1);
};

#endif

