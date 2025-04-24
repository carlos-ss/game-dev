#include <freeglut/freeglut.h>
#include <iostream>

void cube() {
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
    glutSolidCube(2.0f);
    glPopMatrix();
}

void sphere() {
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();
}

void cone() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
    glutSolidCone(1.0f, 2.0f, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cone();
    cube();
    sphere();

    glutSwapBuffers();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // window
    glutInitWindowSize(640, 480);
    glutCreateWindow("Illumination");


    glEnable(GL_DEPTH_TEST);

    // perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 640.0 / 480.0, 0.1, 100.0);

    // camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { -5.0f, 5.0f, 5.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);



    GLfloat light_position2[] = { 0.0f, 5.0f, 0.0f, 1.0f };
    GLfloat light_color2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color2);
    glEnable(GL_LIGHT1);


    glutDisplayFunc(display);


    glutMainLoop();

    return 0;
}