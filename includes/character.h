#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "position.h"
#include "shot.h"

class Character {
    Position *center;
    GLfloat R,G,B;
    GLfloat directionAngle;
    GLfloat armAngle;
    int forwardLeg;


private:
    void drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawArm(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void drawLeg(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void drawCharacter();

public:
    Character(Position *center, GLfloat direction, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    void moveForward(GLfloat aceleration);
    void rotateHead(GLfloat inc);

    /** getters */
    Position* getCenter();
    GLint getRadius();
    GLfloat getDirection();

    /** setters */
    void setDirection(GLfloat direction);

};

#endif