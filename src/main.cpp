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

Map *mapa = nullptr;
Character *p1 = nullptr,
          *p2 = nullptr;

const GLint WINDOWS_SIZE = 500;
int keyStatus[256];

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    mapa->draw();

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyup(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus() {
    for(int i = 0; i < 256; i++) keyStatus[i] = 0; 
}

void parse(const char *svgPath) {
    XMLDocument doc;    XMLError eResult = doc.LoadFile(svgPath);

    if (eResult != XML_SUCCESS) { std::cerr << "Error to load svg file: " << doc.ErrorStr() << std::endl; return; }

    XMLElement* root = doc.FirstChildElement("svg");
    if (root == nullptr) { std::cerr << "<svg> tag not found." << std::endl; return; }

    XMLElement* elemento = root->FirstChildElement("circle");
    while (elemento != nullptr) {
        GLfloat cx, cy, r;
        cx = cy = r = 0;

        elemento->QueryFloatAttribute("cx", &cx);
        elemento->QueryFloatAttribute("cy", &cy);
        elemento->QueryFloatAttribute("r", &r);
        string id = elemento->Attribute("id");
        string fill = elemento->Attribute("fill");

        Position *pos = new Position(cx, cy);

        if (fill == "black") { /* obstaculo*/
            

        } else if (fill == "blue") { /** mapa */
            mapa = new Map(pos, r, 0, 0, 1);

        } else if (fill == "green" ) { /** p1 */
            // p1 = new Character();

        } else if (fill == "red") { /** *p2 */
            // p2 = new Character();
        } 

        elemento = elemento->NextSiblingElement("circle");
    }
}

void init(const char *svgPath) {
    ResetKeyStatus();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 
    glMatrixMode(GL_PROJECTION);
    glOrtho(-(WINDOWS_SIZE/2), (WINDOWS_SIZE/2),
            -(WINDOWS_SIZE/2), (WINDOWS_SIZE/2),
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    parse(svgPath);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    /** config windows */
    glutInitWindowSize(WINDOWS_SIZE, WINDOWS_SIZE);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Tranformations 2D");

    /** callbacks */
    glutDisplayFunc(renderScene);

    init(argv[1]);

    glutMainLoop();
 
    return 0;
}