#include "../includes/shot.h"

/** PRIVATE METHODS */
void Shot::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

/** PUBLIC METHODS */
Shot::Shot(Position *current, GLfloat directionAngle) {
    this->start = nullptr;
    this->final = current;
    this->directionAngle = directionAngle;
    this->speed = 10;
}

void Shot::move() {
    GLfloat new_x = this->speed * sin(this->directionAngle),
            new_y = this->speed * cos(this->directionAngle);

    this->final->setX( new_x );
    this->final->setY( new_y );
}

void Shot::draw() {

    this->drawCircle(this->final->getRadius(), 1, 1, 1);

}