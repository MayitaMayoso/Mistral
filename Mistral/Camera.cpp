#include "Mistral.h"
#include "Camera.h"


#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

Camera::Camera(Mistral* g) {
	game = g;
}

void Camera::zoom(float zoom_factor) {

	glm::vec3 zoom = front * zoom_factor;
	position += zoom;
	lookat += zoom;

	// create orthonormal camera system and view matrix
	UpdateCamera();
}

// Pan function (translate both camera eye and lookat point)
void Camera::pan(float pan_x, float pan_y, float pan_z) {
	glm::vec3 movVec = glm::vec3(pan_x, pan_y, pan_z);
	position += movVec;
	lookat += movVec;

	// create orthonormal camera system and view matrix
	UpdateCamera();
}

// Rotate function
// rotate around a particular center (this does not have to be the lookat point or the origin)
void Camera::rotate(glm::vec3 rotation_center, float angle_X_inc, float angle_Y_inc) {

	// rotate up and right vector based on the increments retrieved from the mouse events
	// rotation 1: based on the mouse horizontal axis
	glm::mat4 rotation_matrixX = glm::mat4(1.0f);
	rotation_matrixX = glm::rotate(rotation_matrixX, glm::radians(angle_X_inc), glm::normalize(up));

	// rotation 2: based on the mouse vertical axis
	glm::mat4 rotation_matrixY = glm::mat4(1.0f);
	rotation_matrixY = glm::rotate(rotation_matrixY, glm::radians(angle_Y_inc), glm::normalize(right));

	// translate back to the origin, rotate and translate back to the pivot location
	glm::mat4 translate_matrix = glm::mat4(1.0f);
	glm::mat4x4 transformation = glm::translate(translate_matrix, rotation_center) * rotation_matrixY * rotation_matrixX * glm::translate(translate_matrix , -rotation_center);

	// apply the transformations
	position = glm::vec3(transformation * glm::vec4(position, 1));
	lookat = glm::vec3(transformation * glm::vec4(lookat, 1));

	// create orthonormal camera system and view matrix
	UpdateCamera();
}

// create orthonormal camera system
void Camera::UpdateCamera() {
	// create new direction vector
	front = glm::normalize(lookat - position);

	// new right vector (orthogonal to direction, up)
	right = glm::normalize(glm::cross(front, up));

	// new up vector (orthogonal to right, direction)
	up = glm::normalize(glm::cross(right, front));
}