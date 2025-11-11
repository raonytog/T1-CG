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
    GLfloat x = this->getCenter()->getX(), y = this->getCenter()->getY();
    GLint radius = this->getRadius();
    GLfloat angle = this->getDirection();

    // pernas
    
    // braco
    
    // torso
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    this->drawTorso(radius, this->R, this->G, this->B);

    // cabeca
    this->drawHead(radius, this->R, this->G, this->B);

    glPopMatrix();
}


/** PUBLIC METHODS */
Character::Character(Position *center, GLfloat R, GLfloat G, GLfloat B) { 
    this->center = center;
    
    this->R = R;
    this->G = G;
    this->B = B;
    
    this->direction = 0;
}

void Character::draw() {
    this->drawCharacter();
}

void Character::moveForward(GLfloat aceleration) {
    GLfloat rad = this->direction * M_PI / 180.0;

    GLfloat dx = aceleration * cos(rad);
    GLfloat dy = aceleration * sin(rad);

    center->setX(center->getX() + dx);
    center->setY(center->getY() + dy);
}

void Character::rotateHead(GLfloat inc) {
    this->direction += inc;
}

Position* Character::getCenter() {
    return this->center;
}

GLint Character::getRadius() {
    return this->getCenter()->getRadius();
}

GLfloat Character::getDirection() {
    return this->direction;
}