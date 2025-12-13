#ifndef _POSITION_H_
#define _POSITION_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

class Position {
    GLfloat x, y;
    GLint radius;

private:

public:
    Position(GLfloat x, GLfloat y, GLint radius);
    GLfloat getDistancePoints(Position *b);

    /** getter */
    GLfloat getX() { return this->x; }
    GLfloat getY() { return this->y; }
    GLint getRadius() { return this->radius; }

    /** setters */
    void setX(GLfloat dx) { this->x = dx; }
    void setY(GLfloat dy) { this->y = dy; }
};

#endif