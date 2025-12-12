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
    void drawShot(GLfloat x, GLfloat y);
public:
    Shot(Position *final, GLfloat directionAngle);
    void move();
    bool isStillValid();
    void draw();

    GLfloat getDirectionAngle() { return this->directionAngle; }
    GLfloat getSpeed() { return this->speed; }
    Position* getStart() { return this->start; }
    Position* getFinal() { return this->final; }
};

#endif