#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include "../includes/tinyxml2.h" // Não se esqueça de incluir
using namespace tinyxml2;


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

int parse() {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile("arena.svg");

    if (eResult != XML_SUCCESS) { std::cerr << "Error to load svg file: " << doc.ErrorStr() << std::endl; return 1; }

    XMLElement* root = doc.FirstChildElement("svg");
    if (root == nullptr) { std::cerr << "<svg> tag not found." << std::endl; return 1; }

    XMLElement* circulo = root->FirstChildElement("circle");
    while (circulo != nullptr) {
        float cx = 0;
        float cy = 0;
        float r = 0;

        circulo->QueryFloatAttribute("cx", &cx);
        circulo->QueryFloatAttribute("cy", &cy);
        circulo->QueryFloatAttribute("r", &r);
        const char* id = circulo->Attribute("id");
        const char* fill = circulo->Attribute("fill");

        std::cout << "Circulo encontrado:" << std::endl;
        std::cout << "  ID: " << id << std::endl;
        std::cout << "  Cor: " << fill << std::endl;
        std::cout << "  Centro (cx, cy): (" << cx << ", " << cy << ")" << std::endl;
        std::cout << "  Raio (r): " << r << std::endl;
        std::cout << "---" << std::endl;

        circulo = circulo->NextSiblingElement("circle");
    }

    return 0;
}