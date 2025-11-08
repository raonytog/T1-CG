#ifndef _MAPA_H_
#define _MAPA_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "character.h"
#include "pos.h"
class Map {
    GLint radius;
    Pos *posicao;
    GLfloat R, G, B;
    Character *p1, *p2;



private:
void drawCircle();
void drawMap();

public:
    Map(GLfloat x, GLfloat y, GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void addObstaculos();
    void setP1(Character p1);
    void setP2(Character p2);

};

#endif