#include "../includes/position.hpp"

/** PRIVATE METHODS */

/** PUBLIC METHODS */
Position::Position(GLfloat x, GLfloat y, GLint radius) {
    this->x = x;
    this->y = y;
	this->radius = radius;
}

GLfloat Position::getDistancePoints(Position *pos) {
	GLfloat dx = this->getX() - pos->getX();
	GLfloat dy = this->getY() - pos->getY();
	return sqrt(dx*dx + dy*dy);
}