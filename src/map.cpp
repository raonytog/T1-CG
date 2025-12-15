#include <iostream>
#include <string>

#include "../includes/map.hpp"
#include "../includes/position.hpp"

/** PRIVATE METHODS */
void Map::drawCircle(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

void Map::drawBase() {
    glPushMatrix();

    GLfloat x = this->getCenter()->getX(),
            y = this->getCenter()->getY(),
            R = this->R, G = this->G, B = this->B;
    GLint radius = this->getRadius();
    glTranslatef(x, y, 0);
    this->drawCircle(radius, R, G, B);

    glPopMatrix();
}

void Map::drawObstacles() {
    for (Obstacle *obstaculo : *this->obstacles) { obstaculo->draw(); }
}

void Map::drawCharacters() {
    this->p1->draw();
    this->p2->draw();
}

void Map::drawHeart(GLfloat x, GLfloat y, GLfloat scale, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (float t = 0.0f; t <= 2 * M_PI; t += 0.01f) {
        float x_t = 16 * powf(sinf(t), 3);
        float y_t = 13 * cosf(t) - 5 * cosf(2*t) - 2 * cosf(3*t) - cosf(4*t);

        float px = x - x_t * scale;
        float py = y + y_t * scale;

        glVertex2f(px, py);
    }

    float x_t_start = 16*powf(sinf(0.0), 3);
    float y_t_start = 13*cosf(0.0) - 5 * cosf(0.0f * 2) - 2 * cosf(0.0f * 3) - cosf(0.0f * 4);
    glVertex2f(x + x_t_start * scale, y - y_t_start * scale);

    glEnd();
}

static void drawText(float x, float y, const char* text, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R,G,B);
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        ++text;
    }
}

static void drawFade() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0, 0, 0, 0.5f); // preto, 50%
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(2000, 0);
        glVertex2f(2000, 2000);
        glVertex2f(0, 2000);
    glEnd();

    glDisable(GL_BLEND);
}

void Map::drawScoreboard() {
    glPushMatrix();

    GLfloat cx = this->getCenter()->getX(),
            cy = this->getCenter()->getY(),
            r = this->getCenter()->getRadius(),
            x = cx-r+sqrt(r),
            y = cy+r-sqrt(r);
            
    /** player 1 */
    drawText(x, y-sqrt(r), "Player 1", 1,0,0);
    for (int i = 0; i < this->getPlayerOne()->getLife(); i++, x+=2*sqrt(r)) {
        this->drawHeart(x, y-2.25*sqrt(r), 1, 1,0,0);
    }

    /** player 2 */
    x = cx+r-sqrt(r);
    drawText(x-4.4*sqrt(r), y-sqrt(r), "Player 2", 1,0,0);
    for (int i = 0; i < this->getPlayerTwo()->getLife(); i++, x-=2*sqrt(r)) {
        this->drawHeart(x, y-2.25*sqrt(r), 1, 1,0,0);
    }

    glPopMatrix();
}

void Map::drawMap() {
    this->drawBase();
    this->drawObstacles();
    this->drawCharacters();
}

void Map::draw() {
    this->drawMap();
    this->drawScoreboard();

    Character* winner = isGameOver();

    if (winner == nullptr) return;

    Position *pos = this->getCenter();
    string output = "";
    if (winner == this->getPlayerOne()) output += "P1 wins";
    else                                output += "P2 wins";
    int adjust = 0.5 * output.length() * glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, 'a');

    drawFade();
    drawText(pos->getX()-adjust, pos->getY(), (char*)output.c_str(), 1,0,0);
}

/** PUBLIC METHODS */
Map::Map(Position *center, GLfloat R, GLfloat G, GLfloat B) {
    this->center = center;

    this->R = R;
    this->G = G;
    this->B = B;

    this->p1 = nullptr; 
    this->p2 = nullptr;
    this->obstacles = new list<Obstacle*>();
}

void Map::addObstacle(Obstacle *obstacle) {
    if (obstacle == nullptr) return;
    this->obstacles->push_back(obstacle);
}

void Map::addObstacleList(list<Obstacle*> *obstacleList) {
    if (obstacleList == nullptr) return;
    for (Obstacle* obs : *obstacleList) {
        this->addObstacle(obs);
    }
}

void Map::moveCharacter(Character *p, int player, GLfloat accelaration, GLdouble correcao) {
    if (p == nullptr) return;

    GLint charRadius = p->getRadius();
    
    GLfloat rad = p->getDirectionAngle() * M_PI / 180.0,
            currentX = p->getCenter()->getX(),
            currentY = p->getCenter()->getY(),
            dx = correcao * accelaration * cos(rad),
            dy = correcao * accelaration * sin(rad);

    Position* newPos = new Position(currentX + dx, currentY + dy, charRadius);

    Character* oponente = nullptr;
    if (player == PLAYER1) oponente = this->getPlayerTwo();
    else                   oponente = this->getPlayerOne();

    /** verifica colisao com outro player */
    GLint sumRadius = charRadius * 2;
    if (newPos->getDistancePoints(oponente->getCenter()) <= sumRadius) return;

    /** verifica colisao com os obstaculos */
    for (Obstacle *obstaculo : *this->getObstacles()) {
        sumRadius = obstaculo->getRadius() + charRadius;
        if (newPos->getDistancePoints(obstaculo->getCenter()) <= sumRadius) return;
    }

    /** verifica colisao com a area fora do mapa */
    if (newPos->getDistancePoints(this->getCenter()) + charRadius >= this->getRadius()) return;
    
    /** se chegou aqui, nao houve colisao, .: move */
    p->moveForward(accelaration*accelaration);
    p->updateStepAnimation();
    delete newPos;
}

Character* Map::isGameOver() {
    Character* winner = nullptr;
    Character* p1 = this->getPlayerOne();
    Character* p2 = this->getPlayerTwo();
    
    if (p1->isAlive() == false)         winner = p2;
    else if (p2->isAlive() == false)    winner = p1;
    else                                winner = nullptr;

    return winner;
}

void Map::setCharacters(Character *p1, Character *p2) {
    if (p1 == nullptr or p2 == nullptr) return;
    this->p1 = p1;       this->p2 = p2;
}

