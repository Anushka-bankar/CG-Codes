#include <GL/glut.h>
#include <cmath>

int level = 4; // how many times the curve is divided

void drawKochCurve(float x1, float y1, float x2, float y2, int iter) {
    if (iter == 0) {
        glVertex2f(x1, y1); //means you're defining a vertex (a point).
        glVertex2f(x2, y2);
    } else {
        float dx = (x2 - x1) / 3.0;
        float dy = (y2 - y1) / 3.0;

        float x3 = x1 + dx;
        float y3 = y1 + dy;
        float x5 = x1 + 2 * dx;
        float y5 = y1 + 2 * dy;
        float x4 = 0.5 * (x1 + x2) - sqrt(3.0) * (y1 - y2) / 6.0;
        float y4 = 0.5 * (y1 + y2) - sqrt(3.0) * (x2 - x1) / 6.0;

        drawKochCurve(x1, y1, x3, y3, iter - 1);
        drawKochCurve(x3, y3, x4, y4, iter - 1);
        drawKochCurve(x4, y4, x5, y5, iter - 1);
        drawKochCurve(x5, y5, x2, y2, iter - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
 
    // Coordinates of an equilateral triangle
    float x1 = 150, y1 = 300;
    float x2 = 450, y2 = 300;
    float x3 = 300, y3 = 300 + (sqrt(3.0) * 150);

    drawKochCurve(x1, y1, x2, y2, level);
    drawKochCurve(x2, y2, x3, y3, level);
    drawKochCurve(x3, y3, x1, y1, level);

    glEnd();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background 	Sets the background color of the window.
    glColor3f(0.0, 0.0, 0.0);         // Black lines
    glMatrixMode(GL_PROJECTION);      // Set projection mode
    glLoadIdentity();                 // Reset the projection matrix
    gluOrtho2D(0, 600, 0, 600);        // Set 2D orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Snowflake");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
