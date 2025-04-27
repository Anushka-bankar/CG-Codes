#include <iostream>
#include <GL/glut.h> 
//So that you don't have to write std::cout every time; you can just write cout
using namespace std;

int ww = 600, wh = 500;

    //bgCol: Background color (white)

    //intCol: Initial polygon color (yellow)

    //fillCol: New color to fill (magenta)
float bgCol[3] = {1.0,1.0,1.0};
float intCol[3] = {1.0,1.0,0.0};
float fillCol[3] = {1.0,0.0,1.0};

void SetPixel(int pointx, int pointy, float f[3]) {
    glBegin(GL_POINTS);
    glColor3fv(f); // sets the color using an array.
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels); 
}

void drawPolygon(int x1, int y1, int x2, int y2) {
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    glFlush();
}

void display() {
    glClearColor(0.0,0.0,1.0,1.0); // blue 
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(200, 200, 300, 300);
    glFlush();
}

void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    getPixel(x, y, color);

    if(color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        SetPixel(x, y, newColor);
        floodFill(x+1, y, oldColor, newColor);
        floodFill(x-1, y, oldColor, newColor);
        floodFill(x, y+1, oldColor, newColor);
        floodFill(x, y-1, oldColor, newColor);
    }
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int xi = x;
        int yi = (wh - y); 
        floodFill(xi, yi, intCol, fillCol); 
    }
}

void myInit() {
    glViewport(0, 0, ww, wh);  //sets the window area for drawing.   
    glMatrixMode(GL_PROJECTION);         
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Flood Fill");
    myInit(); 
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
