#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "position.hpp"
#include "shot.hpp"

class Obstacle {
    Position *center;
    GLfloat R, G, B;

private:
    void drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void drawObstacle();

public:
    Obstacle(Position *center,  GLfloat R, GLfloat G, GLfloat B);

    /**
     * @brief desenha um obstaculo
     */
    void draw();

    /**
     * @brief Verifica se um tiro atingiu um obstaculo
     * @param shot Tiro a analisar colisao
     */
    bool hitControll(Shot *shot);

    /** getters */
    Position* getCenter() { return this->center; }
    GLint getRadius() {  return this->getCenter()->getRadius(); }
    
    /** setters */
};

#endif