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

static void drawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    glBegin(GL_POLYGON);
        glColor3f(R, G, B);
        glVertex3f(-width/2, height, 0); // D
        glVertex3f(-width/2, 0, 0); // A
        glVertex3f(width/2, 0, 0); // B
        glVertex3f(width/2, height, 0); // C
    glEnd();
}

void Character::drawArm(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    drawRect(width,height, this->R, this->G, this->B);
}

void Character::drawLeg(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    drawRect(width, height, 0,0,0);
}


void Character::drawCharacter() { 
    glPushMatrix();
    GLfloat x = this->getCenter()->getX(), y = this->getCenter()->getY();
    GLfloat angle = this->getDirection();
    GLfloat R = this->R, G = this->G, B = this->B;
    GLint radius = this->getRadius();

    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);

    // pernas
    
    
    // braco
    glPushMatrix();
        glTranslatef(radius*2, 0, 0);
        this->drawArm(radius/4, radius, R, G, B);
    glPopMatrix();
    

    // torso
    this->drawTorso(radius, R, G, B);

    // cabeca
    this->drawHead(radius, R, G, B);

    glPopMatrix();
}


/** PUBLIC METHODS */
Character::Character(Position *center, GLfloat direction, GLfloat R, GLfloat G, GLfloat B) { 
    this->center = center;
    
    this->R = R;
    this->G = G;
    this->B = B;
    
    this->direction = direction;
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