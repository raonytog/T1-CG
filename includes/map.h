#ifndef _MAPA_H_
#define _MAPA_H_

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
#include <list>

/** arquivos autorais */
#include "character.h"
#include "position.h"
#include "obstacle.h"
class Map {
    GLint radius;
    Position *center;
    GLfloat R, G, B;
    Character *p1, *p2;
    list<Obstacle*> *obstaculos;
    
private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawBase();
    void drawObstacles();
    void drawCharacters();
    void drawMap();

public:
    Map(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    void addObstacle(Obstacle *obstacle);
    void addObstacleList(list<Obstacle*> *obstacleList);
    /** getters */
    GLint getRadius();
    Position* getCenter();

    /** setters */
    void setCharacters(Character *p1, Character *p2);


};

#endif