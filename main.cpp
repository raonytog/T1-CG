#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

const GLint WINDOWS_SIZE = 500;
int keyStatus[256];

void ResetKeyStatus() {
    for(int i = 0; i < 256; i++) keyStatus[i] = 0; 
}

void init(void) { }

int main(int argc, char *argv[]) {
    // Initialize openGL with Double buffer and RGB color without transparency.
    // Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(WINDOWS_SIZE, WINDOWS_SIZE);
    glutInitWindowPosition(800, 150);
    glutCreateWindow("Tranformations 2D");
 
    // Define callbacks.
    init();

    glutMainLoop();
 
    return 0;
}