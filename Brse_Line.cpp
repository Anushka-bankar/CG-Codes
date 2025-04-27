#include <iostream>
#include <gl/glut.h>
#include <cmath>
using namespace std;

int x_start, y_start, x_end , y_end;
bool firstClick = true;
int lineType;

// To Convert mouse Screen coordinates to Cartesian Coordinates
int convertX(int x) {
    return x-400; //centre to origin
}

int convertY(int y) {
    return 300-y; //Invert the Y-axix
}

void drawAxes() { //Draw X and Y axes in green color to show a refrence in a window
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(-400,0);
    glVertex2i(400,0);
    glVertex2i(0,-300);
    glVertex2i(0,300);
    glEnd();
}

//Generalized Bresenham's Algorithm (handles all slopes)
void Bresenham(int x_start, int y_start, int x_end, int y_end,int type) {
    int dx = abs(x_end-x_start);  //tells us how much we have to move in X-direction
    int dy = abs(y_end - y_start); //tells us how much we have to move in Y-direction

    //If the end point is to the right of the start point, we increase x (+1), otherwise we decrease x (-1).
    int sx = (x_end > x_start)?1:-1; //step direction
    //If the end point is above the start point, we increase y (+1), otherwise we decrease y (-1).
    int sy = (y_end > y_start)?1:-1;
    bool isSteep = dy > dx; //slope > 1

    if(isSteep) std::swap(dx,dy); //to handel slop greater than 1 by steeping over y instead of x -> To draw smooth

    //err is the initial error term.
    //It helps us decide when to move in Y direction while we are moving in X (or vice-versa if steep).
    int err = 2*dy - dx;
    int x = x_start,y=y_start;
    int cnt = 0;
    glBegin(GL_POINTS);

    for(int i = 0; i<=dx; i++) {
        //Draw based on line type
        bool draw = false;
        switch(type) {
            case 1: draw = true;
            break;  //Simple
            case 2: draw = (cnt%2 == 0);
            break;   //Dotted
            case 3: draw = (cnt%10 <5);          //draw 5 points and skip next 5 points
            break;   //Dashed
            case 4: draw = true;
            glPointSize(3.0);
            break; //Solid
        } 
    
        if(draw) glVertex2i(x,y);
        if(err>0) {
            if(isSteep) {
                x += sx; //if steep move x
            }
            else {
                y += sy; //otherwise y
            }
            err -= 2*dx; //correct the error by substracting 2
        }
        if(isSteep) {
            y += sy;
        }else {
            x += sx;
        }
        err += 2 * dy; //correct the error by adding 2
        cnt++;
    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int mx, int my) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(firstClick) {
            x_start = convertX(mx);
            y_start = convertY(my);
            firstClick = false;
        }else {
            x_end = convertX(mx);
            y_end = convertY(my);
            glColor3f(1.0,1.0,1.0);
            Bresenham(x_start,y_start,x_end,y_end,lineType);
            firstClick = true;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glFlush();
}

void init() {
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);
    gluOrtho2D(-400,400,-300,300);
    glPointSize(1.0);
}

int main(int argc, char**argv) {
    cout<<"Enter line type\n";
    cout<<"1.Simple\n";
    cout<<"2.Dotted\n";
    cout<<"3.Dashed\n";
    cout<<"4.Solid\n";
    cout<<"Your Choice: ";
    cin >> lineType;


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //Clears the screen (background refresh)
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bresenham Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0; 
}
