#include "../includes/character.h"
#include <iostream>

/** qual perna ta na frente */
#define LEFT 0
#define RIGHT 1 

/** qtd de frames para desenhar a troca de pernas */
#define DELAY 20

void Character::drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

    glColor3f(0,0,0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
        float x = radius * cos(i);
        float y = radius * sin(i);
        glVertex3f(x, y, 0);
    }
    glEnd();
}

void Character::drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    if (radius <= 0) return;

    glPointSize(1.0);
    glColor3f(R,G,B);
    
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
        float x = radius*2 * cos(i);
        float y = radius/2 * sin(i);
        glVertex3f(x, y, 0);
    }
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
        float x = radius*2 * cos(i);
        float y = radius/2 * sin(i);
        glVertex3f(x, y, 0);
    }
    glEnd();
}

static void drawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    if (width < 0 or height < 0) return;

    glPointSize(1.0);
    glColor3f(R,G,B);
    
    glBegin(GL_POLYGON);
        glColor3f(R, G, B);
        glVertex3f(-width/2, height, 0); // D
        glVertex3f(-width/2, 0, 0); // A
        glVertex3f(width/2, 0, 0); // B
        glVertex3f(width/2, height, 0); // C
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-width/2, height, 0);
        glVertex3f(-width/2, 0, 0);
        glVertex3f(width/2, 0, 0);
        glVertex3f(width/2, height, 0);
    glEnd();
}

void Character::drawArm(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    if (width < 0 or height < 0) return;
    drawRect(width,height, this->R, this->G, this->B);
}

void Character::drawLeg(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    if (width < 0 or height < 0) return;
    drawRect(width, height, 0,0,0);
}

void Character::drawCharacter() { 
    glPushMatrix();
        GLfloat x = this->getCenter()->getX(), y = this->getCenter()->getY();
        GLfloat R = this->R, G = this->G, B = this->B;
        GLfloat lookAngle = this->getDirectionAngle(), armAngle = this->getArmAngle();
        GLint radius = this->getRadius();
        
        glTranslatef(x, y, 0);
        glRotatef(lookAngle-90, 0 ,0, 1);
        
        /** perna direita */
        glPushMatrix();
            if (this->getForwardLeg() == RIGHT) { glTranslatef(radius*0.75, radius*0.25, 0); }
            else { glTranslatef(radius*0.75, -radius*1.25, 0); }
            this->drawLeg(radius/4, radius, R,G,B);
        glPopMatrix();

        /** perna esquerda */
        glPushMatrix();
            if (this->getForwardLeg() == RIGHT) { glTranslatef(-radius*0.75, -radius*1.25, 0); }
            else { glTranslatef(-radius*0.75, radius*0.25, 0); }
            this->drawLeg(radius/4, radius, R,G,B);
        glPopMatrix();
        
        /** braco */
        glPushMatrix();
            glTranslatef(-radius*2, 0, 0);
            glRotatef(armAngle, 0, 0, 1);
            this->drawArm(radius/4, radius, R, G, B);
        glPopMatrix();
        
        /** torso */
        this->drawTorso(radius, R, G, B);

        /** cabeca */
        this->drawHead(radius, R, G, B);
    
    glPopMatrix();
}

/** PUBLIC METHODS */
Character::Character(Position *center, GLfloat direction, GLfloat R, GLfloat G, GLfloat B) { 
    this->center = center;
    
    this->R = R;
    this->G = G;
    this->B = B;

    this->life = 3;
    this->directionAngle = direction;
    this->armAngle = 0;
    this->forwardLeg = RIGHT;
    this->delayToChangeLeg = 0;

    this->shot = nullptr;
}

void Character::draw() {
    if (this->life > 0) this->drawCharacter();
    else return;
}

void Character::moveForward(GLfloat aceleration) {
    GLfloat rad = this->directionAngle * M_PI / 180.0;

    GLfloat dx = aceleration * cos(rad);
    GLfloat dy = aceleration * sin(rad);

    center->setX(center->getX() + dx);
    center->setY(center->getY() + dy);
}

void Character::rotateHead(GLfloat inc) {
    this->directionAngle += inc;

    if (this->directionAngle > 360) this->directionAngle = 0; 
}

void Character::changeForwardLeg() {
    if (this->getForwardLeg() == LEFT)  this->forwardLeg = RIGHT;
    else                                this->forwardLeg = LEFT;
}

void Character::updateStepAnimation() {
    this->delayToChangeLeg++;
    if (this->delayToChangeLeg < DELAY) return;

    this->changeForwardLeg();
    this->delayToChangeLeg = 0;
}

void Character::decreaseLife() {
    this->life--;

    if (this->life >= 0) return;
    else this->life = 0;
}

bool Character::isAlive() {
    return this->life > 0;
}

static void rotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut) {
    GLfloat rad = angle * M_PI / 180.0;
    xOut = x*cos(rad) - y*sin(rad);
    yOut = x*sin(rad) + y*cos(rad);
}


static void translatePoint(GLfloat x, GLfloat y, GLfloat dx, GLfloat dy, GLfloat &xOut, GLfloat &yOut) {
    xOut = x+dx;
    yOut = y+dy;
}

Shot* Character::shotProjectile() {
    GLfloat cx = this->getCenter()->getX(), 
            cy = this->getCenter()->getY(), 
            lookAngle = this->getDirectionAngle();
            armAngle = this->getArmAngle();

    GLint radius = this->getRadius();

    GLfloat px = 0, 
            py =  (GLfloat)radius;

    /** relativo ao braco */
    rotatePoint(px, py, armAngle, px, py);
    translatePoint(px, py, -2*radius, 0, px, py);

    /** relativo ao corpo do personagem */
    rotatePoint(px, py, directionAngle-90, px, py);
    translatePoint(px, py, cx, cy, px, py);

    GLfloat totalAngleDegree = directionAngle + armAngle;

    Position *pos = new Position(px, py, 5); 
    Shot *s = new Shot(pos, armAngle);
    return s;
}

void Character::rotateArm(GLfloat inc) {
    GLfloat newAngle = this->armAngle+inc;
    if      (newAngle < -45) this->armAngle = -45;
    else if (newAngle > +45) this->armAngle = +45;
    else                     this->armAngle = newAngle;
}

Position* Character::getCenter() {
    return this->center;
}

GLint Character::getRadius() {
    return this->getCenter()->getRadius();
}

GLfloat Character::getDirectionAngle() {
    return this->directionAngle;
}

GLfloat Character::getArmAngle() {
    return this->armAngle;
}

int Character::getForwardLeg() {
    return this->forwardLeg;
}

int Character::getLife() {
    return this->life;
}

void Character::setDirection(GLfloat direction) {
    this->directionAngle = direction;
}