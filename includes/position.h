#ifndef _POSITION_H_
#define _POSITION_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

class Position {
    GLfloat x, y;

private:

public:
    Position(GLfloat x, GLfloat y);
    GLfloat getX();
    GLfloat getY();
    void setX(GLfloat dx);
    void setY(GLfloat dy);
    GLfloat getDistancePoints(Position *a, Position *b);
};

#endif