#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "position.hpp"
#include "shot.hpp"

class Character {
    int forwardLeg,
        delayToChangeLeg,
        life;
    Position *center;
    GLfloat R,G,B,
            directionAngle,
            armAngle;
    Shot *shot;

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
    void decreaseLife();
    bool isAlive() {  return this->life > 0; }
    Shot* shotProjectile();
    bool hitControll(Shot *shot);

    /** getters */
    Position* getCenter() { return this->center; }
    GLint getRadius() {  return this->getCenter()->getRadius(); }
    GLfloat getDirectionAngle() { return this->directionAngle; }
    GLfloat getArmAngle() {  return this->armAngle; }
    int getForwardLeg() { return this->forwardLeg; }
    int getLife() { return this->life; }


    /** setters */
    void setDirection(GLfloat direction) { this->directionAngle = direction; }


};

#endif