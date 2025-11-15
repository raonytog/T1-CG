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
    bool checkColision(Position *a, Position *b);

    /** getter */
    GLfloat getX();
    GLfloat getY();
    GLint getRadius();

    /** setters */
    void setX(GLfloat dx);
    void setY(GLfloat dy);
};

#endif