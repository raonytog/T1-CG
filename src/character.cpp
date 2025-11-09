#include "../includes/character.h"

/** PRIVATE METHODS */
void drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void drawArm(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void drawLeg(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void Character::drawCharacter() { 
    
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

GLfloat Character::getX() {
    return this->center->getX();
}

GLfloat Character::getY() {
    return this->center->getY();
}