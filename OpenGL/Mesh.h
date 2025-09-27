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
	void Render(glm::mat4 _wvp, std::string name = "Test");
	void RotateWorld(float _angle, glm::vec3 axis);
	void TranslateWorld(glm::vec3 _offset);

private:
	Shader* shader = nullptr;
	std::vector<GLfloat> vertexData;
	std::vector<GLfloat> colorData;
	std::vector<GLubyte> indexData;
	glm::mat4 world = glm::mat4(1);
};

#endif

