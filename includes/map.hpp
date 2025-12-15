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

    /**
     * @brief desenha o mapa com um campo, scoreboard, personagens e obstaculos
     */
    void draw();

    /**
     * @brief adiciona um obstaculo a lista de obstaculos do mapa
     * @param obstacle obstaculo a ser adicionado
     */
    void addObstacle(Obstacle *obstacle);

    /**
     * @brief adiciona uma lista de obstaculos a lista de obstaculos do mapa
     * @param obstacleList lista de obstaculos
     */
    void addObstacleList(list<Obstacle*> *obstacleList);

    /**
     * @brief movimento um personagem do mapa
     * @param p personagem
     * @param player qual player (0=p1, 1=p2)
     * @param acceleration incremento do movimento
     */
    void moveCharacter(Character *p, int player, GLfloat accelaration);
    
    /** getters */
    GLint getRadius() { return this->getCenter()->getRadius(); }
    Position* getCenter() {  return this->center; }
    Character* getPlayerOne() {  return this->p1; }
    Character* getPlayerTwo() { return this->p2; }
    list<Obstacle*>* getObstacles() { return this->obstacles; }
    Character* isGameOver();
    
    /** setters */
    void setCharacters(Character *p1, Character *p2);
};

#endif