#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "position.h"

class Obstacle {
    Position *center;
    GLfloat R, G, B;

private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawObstacle();

public:
    Obstacle(Position *center,  GLfloat R, GLfloat G, GLfloat B);
    void draw();

    /** getters */
    Position* getCenter();
    GLint getRadius();
    
    /** setters */
};

#endif