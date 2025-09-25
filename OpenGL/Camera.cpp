#include "Camera.h"

Camera::Camera(
	Resolution _resolution,
	glm::vec3 _eye, glm::vec3 _center, glm::vec3 _up,
	float _fov, float _near, float _far
): fov(_fov), near_plane(_near), far_plane(_far)
{
	SetProjection(_resolution);
	LookAt(_eye,_center,_up);
}

void Camera::LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
{
	view = glm::lookAt(_position, _lookAt, _up);
}

void Camera::SetProjection(Resolution _res)
{
	projection = glm::perspective(
		glm::radians(fov),
		(float)_res.width / (float)_res.height,
		near_plane,
		far_plane
	);
}
