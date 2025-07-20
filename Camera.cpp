#include "Camera.h"

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch)
	: front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(2.0f), sensitivity(0.08f) {
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;

	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

vec3 Camera::getPosition() {
	return this->position;
}

vec3 Camera::getFront() {
	return this->front;
}

void Camera::updateCameraVectors() {

	vec3 temp_front;
	temp_front.x = cos(radians(yaw)) * cos(radians(pitch));
	temp_front.y = sin(radians(pitch));
	temp_front.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(temp_front);

	right = normalize(cross(front, worldUp));
	up = normalize(cross(right, front));

	updateViewMatrix();
	notifyViewMatrixObservers();
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.9f) pitch = 89.9f;
	if (pitch < -89.9f) pitch = -89.9f;

	updateCameraVectors();
}

void Camera::updateViewMatrix()
{
	viewMatrix = lookAt(position, position + front, up);
	notifyViewMatrixObservers();
}

void Camera::notifyViewMatrixObservers() {
	mat4 viewMatrix = getViewMatrix();
    Subject::notifyViewMatrixObservers(viewMatrix);
}

void Camera::processKeyboard(Movement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == Movement::FORWARD) {
		position += front * velocity;
	}
	if (direction == Movement::BACKWARD) {
		position -= front * velocity;
	}
	if (direction == Movement::LEFT) {
		position -= right * velocity;
	}
	if (direction == Movement::RIGHT) {
		position += right * velocity;
	}
	updateCameraVectors();
	notifyViewMatrixObservers();
}