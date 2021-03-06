#include "Camera.h"

namespace AC {
	Camera::Camera(float left, float right, float bottom, float top)
	{
		rotation = 0.0f;
		position = vec2(0, 0);

		projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		view = mat4(1.0f);

		viewProjection = projection * view;
	}

	Camera::Camera()
	{
		rotation = 0.0f;
		position = vec2(0, 0);

		projection = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f, -1.0f, 1.0f);
		view = mat4(1.0f);

		viewProjection = projection * view;
	}

	void Camera::Update()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), vec3(position, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

		view = glm::inverse(transform);

		viewProjection = projection * view;
	}

	void Camera::SetPosition(vec2 value)
	{
		position = value;
		Update();
	}

	void Camera::SetRotation(float value)
	{
		rotation = value;
		Update();
	}

	void Camera::Translate(vec2 value)
	{
		position += value;
		Update();
	}

	void Camera::Rotate(float value)
	{
		rotation += value;
		Update();
	}

	mat4& Camera::GetProjectionView()
	{
		return viewProjection;
	}
}