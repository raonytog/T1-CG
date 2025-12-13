#include "../includes/character.hpp"
#include <iostream>

/** qual perna ta na frente */
#define LEFT 0
#define RIGHT 1 

/** qtd de frames para desenhar a troca de pernas */
#define DELAY 40

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
        float x = radius/2 * cos(i);
        float y = radius*2 * sin(i);
        glVertex3f(x, y, 0);
    }
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
        float x = radius/2 * cos(i);
        float y = radius*2 * sin(i);
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
    drawRect(width, height, this->R, this->G, this->B);
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
        glRotatef(lookAngle, 0 ,0, 1);
        
        /** perna direita */
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            if (this->getForwardLeg() == RIGHT) { glTranslatef(radius*0.75, -radius*1.25, 0); } 
            else { glTranslatef(radius*0.75, radius*0.25, 0); }
            // if (this->getForwardLeg() == RIGHT) { glTranslatef(radius*0.75, radius*0.25, 0);
            // else { glTranslatef(radius*0.75, -radius*1.25, 0); }
            this->drawLeg(radius/4, radius, R,G,B);
        glPopMatrix();

        /** perna esquerda */
        glPushMatrix();
            glRotatef(90, 0, 0, 1);
            if (this->getForwardLeg() == RIGHT) { glTranslatef(-radius*0.75, radius*0.25, 0); }
            else { glTranslatef(-radius*0.75, -radius*1.25, 0); }
            // if (this->getForwardLeg() == RIGHT) { glTranslatef(-radius*0.75, -radius*1.25, 0); }
            // else { glTranslatef(-radius*0.75, radius*0.25, 0); }
            this->drawLeg(radius/4, radius, R,G,B);
        glPopMatrix();
        
        /** braco */
        glPushMatrix();
            glTranslatef(0, 2*radius, 0);
            glRotatef(armAngle-90, 0, 0, 1);
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
            directionAngle = this->getDirectionAngle();
            armAngle = this->getArmAngle();

    GLint radius = this->getRadius(); 2*radius;

    GLfloat x = 0, 
            y =  (GLfloat)radius;

    /** relativo ao braco */
    rotatePoint(x, y, armAngle-90, x, y);
    translatePoint(x, y, 0,  2*radius, x, y);

    /** relativo ao corpo do personagem */
    rotatePoint(x, y, directionAngle, x, y);
    translatePoint(x, y, cx, cy, x, y);

    Position *pos = new Position(x, y, 5); 
    Shot *s = new Shot(pos, directionAngle+armAngle);
    return s;
}

bool Character::hitControll(Shot *shot) {
    Position *shot_pos = shot->getFinal(),
             *char_pos = this->getCenter();

    if (shot_pos->getDistancePoints(char_pos) <= this->getRadius()) {
        this->decreaseLife();
        return true;
    }

    return false;
}

void Character::rotateArm(GLfloat inc) {
    GLfloat newAngle = this->armAngle+inc;
    if      (newAngle < -45) this->armAngle = -45;
    else if (newAngle > +45) this->armAngle = +45;
    else                     this->armAngle = newAngle;
}