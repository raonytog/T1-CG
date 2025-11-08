#ifndef _MAPA_H_
#define _MAPA_H_

#include <GL/gl.h>
#include <GL/glu.h>

class Map {
    GLint radius;
    GLfloat x, y;
    GLfloat R, G, B;
    /** personagens */
    /** osbtaculos  */

private:
void drawCircle();
void drawMap();

public:
    Map(GLfloat x, GLfloat y, GLint radius, GLfloat R, GLfloat G, GLfloat B);
};

#endif