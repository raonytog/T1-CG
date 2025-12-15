#include "../includes/shot.hpp"

#define SPEED 2

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

void Shot::drawShot(GLfloat x, GLfloat y) {
     glPushMatrix();

    glTranslatef(x, y, 0);
    this->drawCircle(this->final->getRadius(), 1.0f, 1.0f, 1.0f);

    glPopMatrix();
}

/** PUBLIC METHODS */
Shot::Shot(Position *current, GLfloat directionAngle) {

    this->start = new Position(current->getX(), current->getY(), current->getRadius());
    this->final = current;
    this->directionAngle = directionAngle;
    this->speed = SPEED;
}

void Shot::move(GLdouble correcao) {
    GLfloat directionAngle = this->getDirectionAngle(),
            speed = this->getSpeed(),
            rad = directionAngle*M_PI/180,
            new_x = correcao * speed * cos(rad),
            new_y = correcao * speed * sin(rad),
            x = this->final->getX(), 
            y = this->final->getY();

    this->final->setX( (x+new_x) );
    this->final->setY( (y+new_y) );
}

void Shot::draw() {
    GLfloat x = this->getFinal()->getX(),
            y = this->getFinal()->getY();
    this->drawShot(x, y);
}