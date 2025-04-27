//2D 
// Scaling      Rotation      Reflection
#include <iostream>
#include <GL/glut.h>
#include <cmath>

float angle = 0.0; //Rotation angle (how much shape is rotated)
float scaleX = 1.0, scaleY = 1.0; //Scaling factors (zoom in, zoom out)
bool reflectY = false; //Reflection flag (around Y-axis)

void drawPolygon() {
    glBegin(GL_POLYGON);
    float vertices[6][2] = { //Polygon vertices
        {0.2,0.2}, {0.7,0.2}, {0.9,0.5},
        {0.6,0.8}, {0.4,0.8}, {0.1,0.5}
    };

    for(int i = 0; i < 6; i++) {
        //Apply Scaling
        float x = vertices[i][0] * scaleX;
        float y = vertices[i][1] * scaleY;

        if(reflectY) {
            x = -x; //Reflection
        }

        //Apply Rotation
        float newX = x * cos(angle) - y * sin(angle);
        float newY = x * sin(angle) + y * cos(angle);
        glVertex2f(newX, newY);
    }
    glEnd();
}

void drawAxes() {
    //Draw horizontal (X-axis) and vertical (Y-axis) lines.
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glColor3f(1.0, 0.0, 0.0); //Red color
    drawPolygon();
    glFlush(); //Render the polygon
}

void keyboard(unsigned char key, int x, int y) {
    // r: Rotate the polygon
    // s: Scale up (zoom in)
    // d: Scale down (zoom out)
    // f: Toggle reflection on/off
    switch(key) {
        case 'r' : angle += 0.1; break;
        case 's' : scaleX += 0.1; scaleY += 0.1; break;
        case 'd' : scaleX -= 0.1; scaleY -= 0.1; break;
        case 'f' : reflectY = !reflectY; break;
    }
    glutPostRedisplay(); //Refresh the window after key press
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); //White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); //Set coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Transformation");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
