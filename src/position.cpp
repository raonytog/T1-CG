#include "../includes/position.h"

/** PRIVATE METHODS */

/** PUBLIC METHODS */
Position::Position(GLfloat x, GLfloat y, GLint radius) {
    this->x = x;
    this->y = y;
	this->radius = radius;
}

GLfloat Position::getDistancePoints(Position *b) {
	GLfloat dx = this->getX() - b->getX();
	GLfloat dy = this->getY() - b->getY();
	return sqrt(dx*dx + dy*dy);
}