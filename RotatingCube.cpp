#include <GLFW/glfw3.h>
#include <freeglut/glut.h>
#include <iostream>

// Dimensiones de la ventana
const int WIDTH = 640;
const int HEIGHT = 480;

GLFWwindow* window;
float angle = 0.0f; // Variable para el ángulo de rotación

// Función para dibujar el cubo
void drawCube() {
    glBegin(GL_QUADS);

    // Cara frontal (roja)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Cara trasera (verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Cara superior (azul)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Cara inferior (amarilla)
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Cara izquierda (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Cara derecha (cian)
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glEnd();
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // Crear la ventana
    window = glfwCreateWindow(WIDTH, HEIGHT, "Transformaciones combinadas", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        return -1;
    }

    // Establecer el contexto actual
    glfwMakeContextCurrent(window);

    // Habilitar prueba de profundidad
    glEnable(GL_DEPTH_TEST);

    // Configurar la proyección
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        // Limpiar buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configurar matriz de modelo-vista
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Aplicar transformaciones combinadas
        glTranslatef(0.0f, 0.0f, -5.0f);  // Traslación
        glRotatef(angle, 1.0f, 1.0f, 1.0f); // Rotación
        glScalef(0.5f, 0.5f, 0.5f);       // Escalado

        // Dibujar el cubo
        drawCube();

        // Intercambiar buffers y procesar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Incrementar el ángulo de rotación
        angle += 1.0f;
        if (angle > 360) angle -= 360;
    }

    // Terminar GLFW
    glfwTerminate();
    return 0;
}