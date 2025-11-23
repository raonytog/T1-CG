#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <iostream>
#include <string>
using namespace std;

#include "../includes/tinyxml2.h"
using namespace tinyxml2;

#include "../includes/map.h"
#include "../includes/character.h"
#include "../includes/shot.h"

#define INC_KEY 1

Map *mapa = nullptr;
Character *p1 = nullptr,
          *p2 = nullptr;
list<Obstacle*> *obstaculos = new list<Obstacle*>();

const GLint WINDOWS_SIZE = 500;
const char *path = nullptr;

int keyStatus[256];
int mouseShootStatus = 0;

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

void restart() {
    if (mapa == nullptr) return;

    list<Obstacle*>* obsList = mapa->getObstacles();
    for (Obstacle* obs : *obsList) { delete obs; }
    obsList->clear();           delete obsList;

    delete p1->getCenter();     delete p1;
    delete p2->getCenter();     delete p2;
    delete mapa->getCenter();   delete mapa;

    if (obstaculos) { obstaculos->clear(); }
    
    mapa = nullptr;
    p1 = p2 = nullptr;
    
    parse(path);
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) mouseShootStatus = 1;
    else mouseShootStatus = 0;
}

void mouseMotion(int x, int y) {
    if (x < WINDOWS_SIZE/2) { p1->rotateArm(+INC_KEY); }
    else if (x > WINDOWS_SIZE/2) { p1->rotateArm(-INC_KEY); }
    glutPostRedisplay();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    mapa->draw();
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

        /**  mover horiozontal esquerda < */
        case GLUT_LEFT_BUTTON: /** atira */
        /** mover horizontal direita > */

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
    if (keyStatus[(int)('a')]) { p1->rotateHead(-INC_KEY); }
    if (keyStatus[(int)('d')]) { p1->rotateHead(+INC_KEY); }
    if (keyStatus[(int)('w')]) { mapa->moveCharacter(p1, PLAYER1, +INC_KEY); }
    if (keyStatus[(int)('s')]) { mapa->moveCharacter(p1, PLAYER1, -INC_KEY); }
    /** roda braco com mouse */
    /** atira com mouse */
    /** roda braco com mouse */
    
    if (keyStatus[(int)('k')]) { p2->rotateHead(-INC_KEY); }
    if (keyStatus[231])        { p2->rotateHead(+INC_KEY); }
    if (keyStatus[(int)('o')]) { mapa->moveCharacter(p2, PLAYER2, +INC_KEY); }
    if (keyStatus[(int)('l')]) { mapa->moveCharacter(p2, PLAYER2, -INC_KEY); }
    if (keyStatus[(int)('4')]) { p2->rotateArm(-INC_KEY); }
    // if (keyStatus[(int)('5')]) { mapa->moveCharacter(p2, PLAYER2, -INC_KEY); } /** atira */
    if (keyStatus[(int)('6')]) { p2->rotateArm(+INC_KEY); }

    /** debug */
    if (keyStatus[(int)('r')]) { keyStatus[(int)('r')] = 0; restart(); }
    if (keyStatus[(int)('1')]) { keyStatus[(int)('1')] = 0; p1->decreaseLife(); }
    if (keyStatus[(int)('2')]) { keyStatus[(int)('2')] = 0; p2->decreaseLife(); }

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

    GLfloat angleInDegrees = atan2(dy,dx)*180/M_PI;

    p1->setDirection(angleInDegrees);
    p2->setDirection(angleInDegrees+180);
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

        Position *pos = new Position(centerX, centerY, radius);

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

    GLfloat cx = mapa->getCenter()->getX(),
            cy = mapa->getCenter()->getY(),
            r = mapa->getRadius();
 
    glMatrixMode(GL_PROJECTION);
    glOrtho(cx-r, cx+r,
            cy+r, cy-r,
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}