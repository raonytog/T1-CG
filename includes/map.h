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
    Position *center;
    GLfloat R, G, B;
    Character *p1, *p2;
    list<Obstacle*> *obstacles;
    
private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawBase();
    void drawObstacles();
    void drawCharacters();
    void drawMap();

public:
    Map(Position *center, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    void addObstacle(Obstacle *obstacle);
    void addObstacleList(list<Obstacle*> *obstacleList);

    /** getters */
    GLint getRadius();
    Position* getCenter();
    Character* getPlayerOne();
    Character* getPlayerTwo();
    list<Obstacle*>* getObstacles();

    /** setters */
    void setCharacters(Character *p1, Character *p2);


};

#endif