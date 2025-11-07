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

void ResetKeyStatus() {
    for(int i = 0; i < 256; i++) keyStatus[i] = 0; 
}

void init(void) { }

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    /** config windows */
    glutInitWindowSize(WINDOWS_SIZE, WINDOWS_SIZE);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Tranformations 2D");
 
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