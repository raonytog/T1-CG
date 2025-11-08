#ifndef _POS_H_
#define _POS_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

class Pos {
    GLfloat x, y;

private:


public:
    Pos(GLfloat X, GLfloat Y);
    GLfloat getX() { return this->x; }
    GLfloat getY() { return this->y; }
    GLfloat getDistancePoins(Pos *a, Pos *b) { 
        return sqrt( pow((a->getX() - b->getX()),2) + pow((a->getY(), b->getY()),2)); 
    }
};

#endif