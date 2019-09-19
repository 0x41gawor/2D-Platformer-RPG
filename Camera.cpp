#include "Camera.h"

Camera::Camera() :posX{ SCREEN_WIDTH / 2.f },posY{SCREEN_HEIGHT / 2},lastMouseX{0},currentMouseX{0},dx{0}
{
	view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Camera::update(sf::RenderWindow& window)
{
	lastMouseX = currentMouseX;
	currentMouseX = static_cast<float>(sf::Mouse::getPosition(window).x);

	dx = sf::Mouse::isButtonPressed(sf::Mouse::Right) ? lastMouseX - currentMouseX : 0.f;

	posX += dx;

	if (posX < SCREEN_WIDTH / 2.f)
		posX = SCREEN_WIDTH / 2.f;
	else if (posX > SCREEN_WIDTH * 2.5f)
		posX = SCREEN_WIDTH * 2.5f;

	view.setCenter(posX, posY);

	window.setView(view);
}

float Camera::get_posX()
{
	return posX;
}

void Camera::set_posX(float x)
{
	posX = x;

	if (posX < SCREEN_WIDTH / 2.f)
		posX = SCREEN_WIDTH / 2.f;
	else if (posX > SCREEN_WIDTH * 2.5f)
		posX = SCREEN_WIDTH * 2.5f;
}

Camera::~Camera()
{
	;;
}
