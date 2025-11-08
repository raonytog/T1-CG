#include "../includes/map.h"
#include "../includes/pos.h"

Map::Map(Pos *center, GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    this->posicao = center;
    this->radius = radius;
    this->R = R;
    this->G = G;
    this->B = B;
    this->p1 = nullptr; 
    this->p2 = nullptr;
}

void Map::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glPointSize(1.0);
    glColor3f(R, G, B);
    
    glBegin(GL_POINTS);
        for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
            float x = radius * cos(i);
            float y = radius * sin(i);
                glVertex3f(x, y, 0);
            }
    glEnd();
}

void Map::drawMap() {
    glPushMatrix();
    
    glTranslatef(this->posicao->getX(), this->posicao->getY(), 0);
    this->drawCircle(this->radius, this->R, this->G, this->B);

    glPopMatrix();
}

void Map::addObstaculos() {

}

void Map::setP1(Character p1) {

}

void Map::setP2(Character p2) {

}