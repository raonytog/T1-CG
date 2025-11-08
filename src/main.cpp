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
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    /** aqui eu tenho que fazer os objetos */

    glutSwapBuffers(); // Desenha the new frame of the game.
}

void keyup(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus() {
    for(int i = 0; i < 256; i++) keyStatus[i] = 0; 
}

void parse() {
    XMLDocument doc;    XMLError eResult = doc.LoadFile("arena.svg");

    if (eResult != XML_SUCCESS) { std::cerr << "Error to load svg file: " << doc.ErrorStr() << std::endl; return; }

    XMLElement* root = doc.FirstChildElement("svg");
    if (root == nullptr) { std::cerr << "<svg> tag not found." << std::endl; return; }

    XMLElement* circulo = root->FirstChildElement("circle");
    while (circulo != nullptr) {
        GLfloat cx = 0;
        GLfloat cy = 0;
        GLfloat r = 0;

        circulo->QueryFloatAttribute("cx", &cx);
        circulo->QueryFloatAttribute("cy", &cy);
        circulo->QueryFloatAttribute("r", &r);
        string id = circulo->Attribute("id");
        string fill = circulo->Attribute("fill");

        if (fill == "black") { /* obstaculo*/
            

        } else if (fill == "azul") { /** mapa */
            mapa = new Map(cx, cy, r, 0, 0, 1);

        } else if (fill == "green" ) { /** p1 */
            // p1 = new Character();

        } else if (fill == "red") { /** *p2 */
            // p2 = new Character();
        } 
 

        circulo = circulo->NextSiblingElement("circle");
    }
}

void init(void) {
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION);
    glOrtho(-(WINDOWS_SIZE/2), (WINDOWS_SIZE/2),
            -(WINDOWS_SIZE/2), (WINDOWS_SIZE/2),
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    parse();
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

    init();

    glutMainLoop();
 
    return 0;
}