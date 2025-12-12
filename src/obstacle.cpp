#include "../includes/obstacle.h"

/** PRIVATE METHODS */
void Obstacle::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    if (radius <= 0) return;
    
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
    
    GLfloat x = this->getCenter()->getX(), y = this->getCenter()->getY();
    GLint radius = this->getRadius();
    glTranslatef(x, y, 0);
    this->drawCircle(radius, this->R, this->G, this->B);
    
    glPopMatrix();
}

/** PUBLIC METHODS */
Obstacle::Obstacle(Position *center, GLfloat R, GLfloat G, GLfloat B) {
    this->center = center;

    this->R = R;
    this->G = G;
    this->B = B;
}

void Obstacle::draw() {
    this->drawObstacle();
}

