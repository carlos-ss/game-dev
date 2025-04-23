#include <freeglut/glut.h>
#include <iostream>

int menuId;
void menuHandler(int option) {
    switch (option) {
    case 1:
        std::cout << "Starting game..." << std::endl;
        break;
    case 2:
        std::cout << "Showing options..." << std::endl;
        break;
    case 3:
        std::cout << "Showing credits..." << std::endl;
        break;
    case 4:
        std::cout << "Exiting game..." << std::endl;
        exit(0);
        break;
    default:
        std::cout << "Invalid option!" << std::endl;
    }
}
void menuDisplay() {
    menuId = glutCreateMenu(menuHandler);
    glutAddMenuEntry("Start Game", 1);
    glutAddMenuEntry("Options", 2);
    glutAddMenuEntry("Credits", 3);
    glutAddMenuEntry("Exit", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int width, int height) {
    std::cout << "new width: " << width << std::endl;
    std::cout << "new height: " << height << std::endl;
    glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    else if (key == 'm' || key == 'M') {
        // menu at current mouse position
        glutSetMenu(menuId);
        glutPostRedisplay();
        glutPopWindow();
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // menu appears due to glutAttachMenu
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnd();
    glFlush();
}

int menusmain(int argc, char** argv) {
    glutInit(&argc, argv);

    glutCreateWindow("Game");
    glutInitWindowSize(1200, 400);
    menuDisplay();

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}