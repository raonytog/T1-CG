#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "shot.h"

class Character {
    GLfloat x, y;
    GLfloat R,G,B;

private:
    void drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawArm(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawLeg(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawCharacter();

public:
    Character(GLfloat x, GLfloat y, GLint radius, GLfloat R, GLfloat G, GLfloat B) { this->x = x; this->y = y; }
    void draw() { this->drawCharacter(); }
    void walk(GLfloat dx, GLfloat dy);
    GLfloat getX() { return this->x; }
    GLfloat getY() { return this->y; }
};

#endif