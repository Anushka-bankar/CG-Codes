#include <GL/glut.h> 

int centerX = 300, centerY = 300;  // Circle center
int radius = 100;                   // Circle radius 

// Bresenham's Circle Drawing Algorithm
void drawCircle(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(centerX + x, centerY + y); // 1st quadrant
    glVertex2i(centerX - x, centerY + y); // 2nd quadrant
    glVertex2i(centerX + x, centerY - y); // 4th quadrant
    glVertex2i(centerX - x, centerY - y); // 3rd quadrant
    glVertex2i(centerX + y, centerY + x); // 1st quadrant
    glVertex2i(centerX - y, centerY + x); // 2nd quadrant
    glVertex2i(centerX + y, centerY - x); // 4th quadrant
    glVertex2i(centerX - y, centerY - x); // 3rd quadrant
    glEnd();
} 

// Bresenham's Circle Algorithm
void bresenhamCircle() {
    int x = 0, y = radius;
    int p = 3 - 2 * radius; 

    while (x <= y) {
        drawCircle(x, y);  // Plot points
        if (p < 0) p += 4 * x + 6;
        else { p += 4 * (x - y) + 10; y--; }
        x++;
    }
} 

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw axes (X and Y)
    glColor3f(0.0, 0.0, 0.0); // Set color to black for axes
    glBegin(GL_LINES);
    glVertex2i(0, centerY); glVertex2i(600, centerY); // X-axis
    glVertex2i(centerX, 0); glVertex2i(centerX, 600); // Y-axis
    glEnd(); 

    // Set color to red for the circle
    glColor3f(1.0, 0.0, 0.0);  // Set color to red 

    // Draw the circle
    bresenhamCircle(); 

    glFlush();
} 

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background to white
    glOrtho(0.0, 600.0, 0.0, 600.0, -1.0, 1.0); // Set up orthogonal projection
} 

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham Circle with Axes"); 

    init();
    glutDisplayFunc(display);
    glutMainLoop(); 

    return 0;
}
