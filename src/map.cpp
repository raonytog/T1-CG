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

    GLfloat x = this->getCenter()->getX(), y = this->getCenter()->getY();
    GLint radius = this->getCenter()->getRadius();
    glTranslatef(x, y, 0);
    this->drawCircle(radius, this->R, this->G, this->B);

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
