#include <iostream>

#include "../includes/map.h"
#include "../includes/position.h"

/** PRIVATE METHODS */
void Map::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glPointSize(1.0);
    glColor3f(R, G, B);
    
    glBegin(GL_POLYGON);
        for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
            float x = radius * cos(i);
            float y = radius * sin(i);
                glVertex3f(x, y, 0);
            }
    glEnd();
}

void Map::drawBase() {
    glPushMatrix();

    GLfloat x = this->getCenter()->getX(),
            y = this->getCenter()->getY(),
            R = this->R, G = this->G, B = this->B;
    GLint radius = this->getRadius();
    glTranslatef(x, y, 0);
    this->drawCircle(radius, R, G, B);

    glPopMatrix();
}

void Map::drawObstacles() {
    for (Obstacle *obstaculo : *this->obstacles) {
        obstaculo->draw();
    }
}

void Map::drawCharacters() {
    this->p1->draw();
    this->p2->draw();
}

void Map::drawMap() {
    glPushMatrix();

    this->drawBase();
    this->drawObstacles();
    this->drawCharacters();
    
    glPopMatrix();
}

void Map::draw() {
    this->drawMap();
}

/** PUBLIC METHODS */
Map::Map(Position *center, GLfloat R, GLfloat G, GLfloat B) {
    this->center = center;

    this->R = R;
    this->G = G;
    this->B = B;

    this->p1 = nullptr; 
    this->p2 = nullptr;
    this->obstacles = new list<Obstacle*>();
}

void Map::addObstacle(Obstacle *obstacle) {
    if (obstacle == nullptr) return;
    this->obstacles->push_back(obstacle);
}

void Map::addObstacleList(list<Obstacle*> *obstacleList) {
    if (obstacleList == nullptr) return;
    for (Obstacle* obs : *obstacleList) {
        this->addObstacle(obs);
    }
}

void Map::moveCharacter(Character *p, int player, GLfloat accelaration) {
    GLfloat rad = p->getDirection() * M_PI / 180.0;

    GLint charRadius = p->getRadius();
    GLfloat currentX = p->getCenter()->getX();
    GLfloat currentY = p->getCenter()->getY();

    GLfloat dx = accelaration * cos(rad);
    GLfloat dy = accelaration * sin(rad);

    Position *newPos = new Position(currentX+dx, currentY+dy, charRadius);

    /** verifica colisao com player */
    bool colidiu = false;
    if (newPos->getDistancePoints(this->getPlayerTwo()->getCenter()) <= charRadius)
        colidiu = true;
    

    /** verifica colisao com obstaculos */
    if (colidiu == false) {
        for (Obstacle *obstaculo : *this->getObstacles()) {
            if (newPos->getDistancePoints(obstaculo->getCenter()) <= obstaculo->getRadius()) {
                colidiu = true;
                break;
            }
        }
    }

    /** verifica se o jogador saiu do mapa */
    if (colidiu == false) {
        if (newPos->getDistancePoints(this->getCenter()) > this->getRadius()) colidiu = true;
    }

    if (colidiu) return;
    else p->moveForward(accelaration);
}

void Map::rotateCharacter(Character *p) {

}

GLint Map::getRadius() {
    return this->getCenter()->getRadius();
}

Position* Map::getCenter() {
    return this->center;
}

void Map::setCharacters(Character *p1, Character *p2) {
    if (p1 == nullptr or p2 == nullptr) return;
    this->p1 = p1;
    this->p2 = p2;
}

Character* Map::getPlayerOne() {
    return this->p1;
}

Character* Map::getPlayerTwo() {
    return this->p2;
}

list<Obstacle*>* Map::getObstacles() {
    return this->obstacles;
}

