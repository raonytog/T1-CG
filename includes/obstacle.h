#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <GL/gl.h>
#include <GL/glu.h>

/** arquivos autorais */
#include "position.h"

class Obstacle {
    GLint radius;
    Position *center;
    GLfloat R, G, B;

private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawObstacle();

public:
    Obstacle(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    

};

#endif