#ifndef _SHOT_H_
#define _SHOT_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "position.h"

class Shot {
    Position *final, *start;
    GLfloat directionAngle, speed;

private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);

public:
    Shot(Position *final, GLfloat directionAngle);
    void move();
    void draw(GLfloat x, GLfloat y);
    bool isStillValid();

    GLfloat getDirectionAngle();
    GLfloat getSpeed();
    Position* getStart();
    Position* getFinal();
};

#endif