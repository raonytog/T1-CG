#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "position.hpp"
#include "shot.hpp"

class Character {
    int forwardLeg,
        delayToChangeLeg,
        life;
    Position *center;
    GLfloat R,G,B,
            directionAngle,
            armAngle;
    Shot *shot;

private:
    void drawHead(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawTorso(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawArm(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void drawLeg(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void drawCharacter();

public:
    Character(Position *center, GLfloat direction, GLfloat R, GLfloat G, GLfloat B);

    /**
     * @brief desenha o personagem
     */
    void draw();

    /** 
     * @brief Trata movimento do personagem
     * @param aceleration o tanto que é incrementado no movimento
     * @param correcao correcao para as chamadas em SO diferentes
     */
    void moveForward(GLfloat aceleration);

    /**
     * @brief rotaciona a cabeca do personagem dado um incremento (+ = direita, - = esquerda)
     * @param inc incremento
     */
    void rotateHead(GLfloat inc);

    /**
     * @brief rotaciona o braco do personagem dado um incremento (+ = direita, - = esquerda)
     * @param inc incremento
     */
    void rotateArm(GLfloat inc);

    /**
     * @brief muda qual a perna que esta na frente
     */
    void changeForwardLeg();

    /**
     * @brief controla o estado da perna de acordo com o tempo decorrido
     */
    void updateStepAnimation();

    /**
     * @brief diminui a vida do personagem em um
     */
    void decreaseLife();

    /**
     * @brief Atira um projétil partindo da ponta do braco do personagem
     */
    Shot* shotProjectile();

    /**
     * @brief verifica se um tiro atingiu o personagem
     * @param shot tiro
     */
    bool hitControll(Shot *shot);

    
    /** getters */
    Position* getCenter() { return this->center; }
    GLint getRadius() {  return this->getCenter()->getRadius(); }
    GLfloat getDirectionAngle() { return this->directionAngle; }
    GLfloat getArmAngle() {  return this->armAngle; }
    int getForwardLeg() { return this->forwardLeg; }
    int getLife() { return this->life; }
    bool isAlive() {  return this->life > 0; }

    /** setters */
    void setDirection(GLfloat direction) { this->directionAngle = direction; }


};

#endif