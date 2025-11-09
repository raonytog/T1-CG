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
    glTranslatef(this->center->getX(), this->center->getY(), 0);
    this->drawCircle(this->radius, this->R, this->G, this->B);
}

void Map::drawObstacles() {
    for (Obstacle *ob : *this->obstaculos) {
        ob->draw();
    }
}

void Map::drawCharacters() {
    this->p1->draw();
    this->p2->draw();
}

void Map::drawMap() {
    glPushMatrix();

    this->drawBase();
    // this->drawObstacles();
    
    glPopMatrix();
}

void Map::draw() { this->drawMap(); }

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
        this->obstaculos->push_back(obs);
    }
}

void Map::setP1(Character *p1) {
    if (p1 == nullptr) return;
    this->p1 = p1;
}

void Map::setP2(Character *p2) {
    if (p2 == nullptr) return;
    this->p2 = p2;
}