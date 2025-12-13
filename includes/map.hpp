#ifndef _MAPA_H_
#define _MAPA_H_

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
#include <list>

#define PLAYER1 0
#define PLAYER2 1

/** arquivos autorais */
#include "character.hpp"
#include "position.hpp"
#include "obstacle.hpp"
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
    void drawHeart(GLfloat x, GLfloat y, GLfloat scale, GLfloat R, GLfloat G, GLfloat B);
    void drawScoreboard();
    void drawMap();

public:
    Map(Position *center, GLfloat R, GLfloat G, GLfloat B);
    void draw();
    void addObstacle(Obstacle *obstacle);
    void addObstacleList(list<Obstacle*> *obstacleList);
    void moveCharacter(Character *p, int player, GLfloat accelaration);
    Character* isGameOver();

    /** getters */
    GLint getRadius() { return this->getCenter()->getRadius(); }
    Position* getCenter() {  return this->center; }
    Character* getPlayerOne() {  return this->p1; }
    Character* getPlayerTwo() { return this->p2; }
    list<Obstacle*>* getObstacles() { return this->obstacles; }
    

    /** setters */
    void setCharacters(Character *p1, Character *p2);
};

#endif