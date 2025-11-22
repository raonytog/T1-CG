#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "position.h"
#include "shot.h"

class Character {
    int forwardLeg;
    int delayToChangeLeg;
    Position *center;
    GLfloat R,G,B,
            directionAngle,
            armAngle;



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
    void rotateArm(GLfloat inc);
    void changeForwardLeg();
    void updateStepAnimation();

    /** getters */
    Position* getCenter();
    GLint getRadius();
    GLfloat getDirectionAngle();
    GLfloat getArmAngle();
    int getForwardLeg();


    /** setters */
    void setDirection(GLfloat direction);


};

#endif