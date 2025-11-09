#include "../includes/character.h"
#include <iostream>

/** PRIVATE METHODS */
void Character::drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

void Character::drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glPointSize(1.0);
    glColor3f(R-.2, G-.2, B-.2);
    
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
        float x = radius*2 * cos(i);
        float y = radius/2 * sin(i);
        glVertex3f(x, y, 0);
    }
    glEnd();
}

void Character::drawArm(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void Character::drawLeg(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void Character::drawCharacter() { 
    glPushMatrix();

    // pernas

    // braco

    // torso
    glTranslatef(this->getCenter()->getX(), this->getCenter()->getY(), 0);
    this->drawTorso(this->getRadius(), this->R, this->G, this->B);

    // cabeca
    this->drawHead(this->getRadius(), this->R, this->G, this->B);

    glPopMatrix();
}


/** PUBLIC METHODS */
Character::Character(Position *center, GLint radius, GLfloat R, GLfloat G, GLfloat B) { 
    this->center = center;
    this->radius = radius;
    this->R = R;
    this->G = G;
    this->B = B;
}

void Character::draw() {
    this->drawCharacter();
}

void Character::walk(GLfloat dx, GLfloat dy) {

}

Position* Character::getCenter() {
    return this->center;
}

GLint Character::getRadius() {
    return this->radius;
}