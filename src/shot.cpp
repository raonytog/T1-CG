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
            new_y = this->speed * cos(this->directionAngle),
            x = this->final->getX(), 
            y = this->final->getY();

    this->final->setX(x+new_x);
    this->final->setY(y+new_y);
}

void Shot::draw(GLfloat x, GLfloat y) {
     glPushMatrix();

    glTranslatef(x, y, 0);
    this->drawCircle(this->final->getRadius(), 1.0f, 1.0f, 1.0f);

    glPopMatrix();
}

bool Shot::isStillValid() {
    GLfloat start_x = this->getStart()->getX(), start_y = this->getStart()->getY(),
            final_x = this->getFinal()->getX(), final_y = this->getFinal()->getY();
    return sqrt( pow((final_x - start_x), 2) + pow((final_y - start_y), 2));
}

GLfloat Shot::getDirectionAngle() {
    return this->directionAngle;
}

GLfloat Shot::getSpeed() {
    return this->speed;
}

Position* Shot::getStart() {
    return this->start;
}

Position* Shot::getFinal() {
    return this->final;
}