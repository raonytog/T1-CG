#include "../includes/obstacle.h"

/** PRIVATE METHODS */
void Obstacle::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

void Obstacle::drawObstacle() {
    glPushMatrix();
    
    glTranslatef(this->center->getX(), this->center->getY(), 0);
    this->drawCircle(this->radius, this->R, this->G, this->B);
    
    glPopMatrix();
}

/** PUBLIC METHODS */
Obstacle::Obstacle(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    this->center = center;
    this->radius = radius;

    this->R = R;
    this->G = G;
    this->B = B;
}

void Obstacle::draw() {
    this->drawObstacle();
}