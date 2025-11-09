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

    glTranslatef(this->center->getX(), this->center->getY(), 0);
    this->drawCircle(this->radius, this->R, this->G, this->B);

    glPopMatrix();
}

void Map::drawObstacles() {
    for (Obstacle *obstaculo : *this->obstaculos) {
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
Map::Map(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    this->center = center;
    this->radius = radius;

    this->R = R;
    this->G = G;
    this->B = B;

    this->p1 = nullptr; 
    this->p2 = nullptr;
    this->obstaculos = new list<Obstacle*>();
}

void Map::addObstacle(Obstacle *obstacle) {
    if (obstacle == nullptr) return;
    this->obstaculos->push_back(obstacle);
}

void Map::addObstacleList(list<Obstacle*> *obstacleList) {
    if (obstacleList == nullptr) return;
    for (Obstacle* obs : *obstacleList) {
        this->addObstacle(obs);
    }
}

GLint Map::getRadius() {
    return this->radius;
}

Position* Map::getCenter() {
    return this->center;
}

void Map::setCharacters(Character *p1, Character *p2) {
    if (p1 == nullptr or p2 == nullptr) return;
    this->p1 = p1;
    this->p2 = p2;
}
