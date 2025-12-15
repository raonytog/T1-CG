#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <iostream>
#include <string>
using namespace std;

#include "../includes/tinyxml2.hpp"
using namespace tinyxml2;

#include "../includes/map.hpp"
#include "../includes/character.hpp"
#include "../includes/shot.hpp"

#define INC_KEY 1

Map *mapa = nullptr;
Character *p1 = nullptr,
          *p2 = nullptr;
list<Obstacle*> *obstaculos = new list<Obstacle*>();
Shot* shots[2];

const GLint WINDOWS_SIZE = 500;
const char *path = nullptr;

int keyStatus[256];
int mouseShootStatus = 0;
int lastX = -1;

bool someoneWon();
void restart();
void mouseMotion(int x, int y);
void mouseClick(int button, int state, int x, int y);
void renderScene();
void keyup(unsigned char key, int x, int y);
void keyPress(unsigned char key, int x, int y);
void ResetKeyStatus();
void idle(void);
void fixChractersDirection();
void parse(const char *svgPath);
void init(const char *svgPath);

int main(int argc, char *argv[]) {
    path = argv[1];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    /** config windows */
    glutInitWindowSize(WINDOWS_SIZE, WINDOWS_SIZE);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("T1 CG, Ray");

    /** callbacks */
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMotion);

    init(argv[1]);

    glutMainLoop();
 
    return 0;
}

bool someoneWon() {
    return (p1->getLife() == 0 or p2->getLife() == 0);
}

void restart() {
    if (mapa == nullptr) return;

    list<Obstacle*>* obsList = mapa->getObstacles();
    for (Obstacle* obs : *obsList) { delete obs; }
    obsList->clear();           delete obsList;

    for(int i=0; i<2; i++) { delete shots[i]; }

    delete p1->getCenter();     delete p1;
    delete p2->getCenter();     delete p2;
    delete mapa->getCenter();   delete mapa;
    

    if (obstaculos) { obstaculos->clear(); }
    
    mapa = nullptr;
    p1 = p2 = nullptr;
    shots[0] = shots[1] = nullptr;
    
    parse(path);
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON && shots[0] == nullptr && someoneWon() == false) {
            shots[0] = p1->shotProjectile();
            mouseShootStatus = 1;
        }

    } else mouseShootStatus = 0;
}


void mouseMotion(int x, int y) {
    if (lastX < 0) lastX = x;
    int dx = x - lastX;

    GLfloat angle = p1->getDirectionAngle();
    
    // CORREÇÃO DA INVERSÃO: Inverte o movimento do mouse (dx) se o personagem estiver 
    // virado para a metade esquerda da tela (entre 90.0f e 270.0f).
    if (angle > 90.0f && angle < 270.0f) { 
        dx = -dx;
    } 
    // A condição 'else if (angle >= 360)' foi removida, 
    // pois o ângulo deve ser normalizado para [0, 360) em 'rotateHead'.
    
    if (someoneWon() == false) {
        // CORREÇÃO DA APLICAÇÃO:
        // Mouse Direita (dx > 0) -> Gira Horário/Direita -> p1->rotateArm(-INC_KEY)
        if (dx > 0)      p1->rotateArm(-INC_KEY);

        // Mouse Esquerda (dx < 0) -> Gira Anti-Horário/Esquerda -> p1->rotateArm(+INC_KEY)
        else if (dx < 0) p1->rotateArm(+INC_KEY);
    }

    lastX = x;
    glutPostRedisplay();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    mapa->draw();
    GLint mapRadius = mapa->getRadius();
    for (int i = 0; i < 2; i++) {
        if (shots[i] == nullptr) continue;

        
        if (shots[i]->getFinal()->getDistancePoints(mapa->getCenter()) <= mapRadius) shots[i]->draw();
        else shots[i] = nullptr;
    }

    glutSwapBuffers();
}

void keyup(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y) {
    switch (key) {
        /** player 1 */
        case 'w':
        case 'W':
            keyStatus[(int)('w')] = 1;
            break;

        case 'a':
        case 'A':
            keyStatus[(int)('a')] = 1;
            break;

        case 's':
        case 'S':
            keyStatus[(int)('s')] = 1;
            break;

        case 'd':
        case 'D':
            keyStatus[(int)('d')] = 1;
            break;

        /** player 2 */
        case 'o':
        case 'O':
            keyStatus[(int)('o')] = 1;
            break;

        case 'k':
        case 'K':
            keyStatus[(int)('k')] = 1;
            break;

        case 'l':
        case 'L':
            keyStatus[(int)('l')] = 1;
            break;

        case 231: /** ç */
        case 199: /** Ç */
            keyStatus[231] = 1;
            break;

        case '4': /** move braco esquerda */
            keyStatus[(int)('4')] = 1;
            break;

        case '5': /** atira */
            keyStatus[(int)('5')] = 1;
            break;
        
        case '6': /** move braco direita */
            keyStatus[(int)('6')] = 1;
            break;


        
        /** debug */
        case 'R':
        case 'r': /** reseta o jogo */
            keyStatus[(int)('r')] = 1;
            break;

        case '1': /** tira uma vida de p1 */
            keyStatus[(int)('1')] = 1;
            break;

        case '2': /** tira uma vida de p2 */
            keyStatus[(int)('2')] = 1;
            break;
    }
}

void ResetKeyStatus() {
    for(int i = 0; i < 256; i++) {
        keyStatus[i] = 0; 
    }
}

void idle(void) {
    /** arruma a diferenca de tempo de resposta entre maquinas diferentes */
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime, timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime;
    previousTime = currentTime;

    if (someoneWon() == false) {
        if (keyStatus[(int)('a')]) { p1->rotateHead(+INC_KEY); }
        if (keyStatus[(int)('d')]) { p1->rotateHead(-INC_KEY); }
        if (keyStatus[(int)('w')]) { mapa->moveCharacter(p1, PLAYER1, +INC_KEY, timeDiference); }
        if (keyStatus[(int)('s')]) { mapa->moveCharacter(p1, PLAYER1, -INC_KEY, timeDiference); }
        /** roda braco com mouse */
        /** atira com mouse */
        /** roda braco com mouse */
        
        if (keyStatus[(int)('k')]) { p2->rotateHead(+INC_KEY); }
        if (keyStatus[231])        { p2->rotateHead(-INC_KEY); }
        if (keyStatus[(int)('o')]) { mapa->moveCharacter(p2, PLAYER2, +INC_KEY, timeDiference); }
        if (keyStatus[(int)('l')]) { mapa->moveCharacter(p2, PLAYER2, -INC_KEY, timeDiference); }
        if (keyStatus[(int)('4')]) { p2->rotateArm(+INC_KEY); }
        if (keyStatus[(int)('5')] and shots[1] == nullptr) { shots[1] = p2->shotProjectile(); } /** atira */
        if (keyStatus[(int)('6')]) { p2->rotateArm(-INC_KEY); }
    }

    /** debug */
    if (keyStatus[(int)('r')]) { keyStatus[(int)('r')] = 0; restart(); }
    if (keyStatus[(int)('1')]) { keyStatus[(int)('1')] = 0; p1->decreaseLife(); }
    if (keyStatus[(int)('2')]) { keyStatus[(int)('2')] = 0; p2->decreaseLife(); }

    /** tiros */
    for (int i = 0; i < 2; i++) { 
        if (shots[i] == nullptr) continue; 
        
        // alterar o move para receber o timeDiff para essas funcoes e mover do seguinte jeito: dist = vel * t
        shots[i]->move( timeDiference );
        if (p1->hitControll(shots[i])) { delete shots[i]; shots[i] = nullptr; continue; }
        if (p2->hitControll(shots[i])) { delete shots[i]; shots[i] = nullptr; continue; }

        for (Obstacle *o : *obstaculos) {
            if (o->hitControll(shots[i])) { delete shots[i]; shots[i] = nullptr; break; }
        }
    }

    glutPostRedisplay();
}

/**
 * @brief Inicializa os personagens olhando um para o outro
 */
void fixChractersDirection() {
    GLfloat x1 = p1->getCenter()->getX(), y1 = p1->getCenter()->getY(),
            x2 = p2->getCenter()->getX(), y2 = p2->getCenter()->getY();

    GLfloat dx = x2-x1,
            dy = y2-y1;

    GLfloat angleInDegrees = atan2(dy,dx) * 180/M_PI;
    if (angleInDegrees < 0) angleInDegrees += 360;

    p1->setDirection(angleInDegrees);

    angleInDegrees += 180;
    if (angleInDegrees > 360) angleInDegrees -= 360;
    p2->setDirection(angleInDegrees);
}

/**
 * @brief Popula o sistema com o mapa, obstaculos e personagens do jogo
 * @param *svgPath é o ponteiro para o caminho do arquvio SVG, contendo as posicoes inicias de cada objeto
 */
void parse(const char *svgPath) {
    XMLDocument doc;    XMLError eResult = doc.LoadFile(svgPath);

    if (eResult != XML_SUCCESS) { std::cerr << "Error to load svg file: " << doc.ErrorStr() << std::endl; return; }

    XMLElement* root = doc.FirstChildElement("svg");
    if (root == nullptr) { std::cerr << "<svg> tag not found." << std::endl; return; }

    XMLElement* elemento = root->FirstChildElement("circle");
    while (elemento != nullptr) {
        GLfloat centerX, centerY, radius;
        centerX = centerY = radius = 0;

        elemento->QueryFloatAttribute("cx", &centerX);
        elemento->QueryFloatAttribute("cy", &centerY);
        elemento->QueryFloatAttribute("r", &radius);
        string id = elemento->Attribute("id");
        string fill = elemento->Attribute("fill");

        Position *pos = new Position(centerX, -centerY, radius);

        if      (fill == "black") { obstaculos->push_back( new Obstacle(pos, 0,0,0) ); } /* obstaculo*/
        else if (fill == "blue")  { mapa = new Map(pos, 0,0,1); }     /** mapa */
        else if (fill == "green") { p1 = new Character(pos, -1, 0,1,0); } /** p1 */ 
        else if (fill == "red")   { p2 = new Character(pos, -1, 1,0,0); }  /** *p2 */

        elemento = elemento->NextSiblingElement("circle");
    }

    mapa->addObstacleList(obstaculos);
    mapa->setCharacters(p1, p2);

    fixChractersDirection();
}

void init(const char *svgPath) {
    ResetKeyStatus();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    parse(svgPath);

    if (mapa == nullptr) {
        cout << "ERRO: A arena não criada." << endl;
        return;
    }

    shots[0] = shots[1] = nullptr;

    GLfloat cx = mapa->getCenter()->getX(),
            cy = mapa->getCenter()->getY(),
            r = mapa->getRadius();
 
    glMatrixMode(GL_PROJECTION);
    glOrtho(cx-r, cx+r,
            cy-r, cy+r,
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}