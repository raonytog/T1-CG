#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "position.h"
#include "shot.h"

class Character {
    Position *center;
    GLfloat R,G,B;
    GLint radius;

private:
    void drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawArm(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawLeg(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawCharacter();

public:
    Character(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    void walk(GLfloat dx, GLfloat dy);

    /** getters */
    Position* getCenter();
    GLint getRadius();

};

#endif