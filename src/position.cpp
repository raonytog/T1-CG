#include "../includes/position.h"

/** PRIVATE METHODS */

/** PUBLIC METHODS */
Position::Position(GLfloat x, GLfloat y, GLint radius) {
    this->x = x;
    this->y = y;
	this->radius = radius;
}

GLfloat Position::getX() {
	return this->x;
}

GLfloat Position::getY() {
	return this->y;
}

GLint Position::getRadius() {
	return this->radius;
}

void Position::setX(GLfloat dx) {
	this->x = dx;
}

void Position::setY(GLfloat dy) {
	this->y = dy;
}

GLfloat Position::getDistancePoints(Position *a, Position *b) {
	GLfloat dx = a->getX() - b->getX();
	GLfloat dy = a->getY() - b->getY();
	return sqrt(dx*dx + dy*dy);
}