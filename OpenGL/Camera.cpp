#include "Camera.h"

Camera::Camera(
	Resolution _resolution,
	glm::vec3 _eye, glm::vec3 _center, glm::vec3 _up,
	float _fov, float _near, float _far
)
{
	projection = glm::perspective(
		glm::radians(_fov),
		(float)_resolution.width / (float)_resolution.height,
		_near,
		_far
	);

	view = glm::lookAt(_eye,_center,_up);
}
