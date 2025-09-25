#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "StandardIncludes.h"

class Camera
{
public:
	Camera(
		Resolution _resolution,
		glm::vec3 _eye = {1, 0, 0}, glm::vec3 _center = { 0, 0, 0 }, glm::vec3 _up = { 0, 1, 0 },
		float _fov = 45.0f, float _near = 0.1f, float _far = 1000.0f
	);
	~Camera() = default;

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }

private:
	glm::mat4 projection;
	glm::mat4 view;
};

#endif

