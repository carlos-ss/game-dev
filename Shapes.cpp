#include <glew/glew.h>
#include <GLFW/glfw3.h>


#include <iostream>

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.25f, -0.25f, 0.0f);
	glVertex3f(0.25f, -0.25f, 0.0f);
	glVertex3f(0.0f, 0.25f, 0.0f);
	glEnd();

}

void drawParallelogramWithTriangles() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.75f, 0.75f, 0.75f);

	// left triangle
	glVertex3f(-0.4f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(-0.0f, 0.0f, 0.0f);

	glColor3f(0.30f, 0.30f, 0.30f);
	// right triangle
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.4f, 0.0f);

	glEnd();

}

void drawTrapezoid() {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	//center
	glVertex3f(0.0f, 0.0f, 0.0f);

	// bottom left
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.25f, -0.5f, 0.0f);

	// bottom right
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.25f, -0.5f, 0.0f);

	//bottom center
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, -0.5f, 0.0f);
	glVertex3f(0.25f, -0.5f, 0.0f);
	glEnd();
}

void drawPentagon() {
	const float scale = 32.0f; // Brightness 
	glBegin(GL_TRIANGLE_FAN);
	
	// top left
	glColor3f(1.0f * scale / 255.0f, 2.0f * scale / 255.0f, 0.1f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	// top right
	glColor3f(5.0f * scale / 255.0f, 10.0f * scale / 255.0f, 1.0f );
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);

	//center
	glVertex3f(0.0f, 0.0f, 0.0f);

	// bottom left
	glColor3f(25.0f * scale / 255.0f, 1.0f * scale / 255.0f, 13.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.25f, -0.5f, 0.0f);

	// bottom right
	
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.25f, -0.5f, 0.0f);

	//bottom center
	//glColor3f(8.0 / 255.0, 5.0 / 255.0, 0.0);
	glVertex3f(-0.25f, -0.5f, 0.0f);
	glVertex3f(0.25f, -0.5f, 0.0f);
	//end
	glEnd();
}

void drawSquare() {

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);

	// top left 
	glVertex3f(-0.95f, 0.95f, 0.0f);

	// top right 
	glVertex3f(0.95f, 0.95f, 0.0f);

	// bottom right
	glVertex3f(0.95f, -0.95f, 0.0f);


	glVertex3f(-0.95f, -0.95f, 0.0f);

	glEnd();

}

void drawOctagon() {
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	// start
	glVertex3f(-0.25f, 0.5f, 0.0f);
	glVertex3f(0.25f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, -0.25f, 0.0f);
	glVertex3f(0.25f, -0.5f, 0.0f);
	glVertex3f(-0.25f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.25f, 0.0f);
	glVertex3f(-0.5f, 0.25f, 0.0f);
	//end
	glEnd();
}

void drawHand() {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 1.0f);
	// start

	// thumb
	glVertex3f(-1.0f, -0.1f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.6f, -0.2f, 0.0f);


	// index finger
	glVertex3f(-0.6f, 0.8f, 0.0f);
	glVertex3f(-0.4f, 0.8f, 0.0f);
	glVertex3f(-0.4f, 0.2f, 0.0f);
	glVertex3f(-0.3f, 0.1f, 0.0f);
	
	// middle finger
	glVertex3f(-0.2f, 0.2f, 0.0f);
	glVertex3f(-0.2f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);


	// ring finger
	glVertex3f(0.2f, 0.3f, 0.0f);
	glVertex3f(0.2f, 0.9f, 0.0f);
	glVertex3f(0.4f, 0.9f, 0.0f);
	glVertex3f(0.4f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.1f, 0.0f);


	// pinky finger
	glVertex3f(0.6f, 0.2f, 0.0f);
	glVertex3f(0.6f, 0.6f, 0.0f);
	glVertex3f(0.8f, 0.6f, 0.0f);
	glVertex3f(0.8f, 0.1f, 0.0f);
	// palm /arm
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.3f, -0.6f, 0.0f);
	glVertex3f(0.2f, -1.0f, 0.0f);
	glVertex3f(-0.3f, -1.0f, 0.0f);
	glVertex3f(-0.4f, -0.7f, 0.0f);
	glVertex3f(-0.6f, -0.7f, 0.0f);

	glEnd();
}


int notShapesmain() {
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "Modern OpenGL Triangle", NULL, NULL);

	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	// While window is open 
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();  // Reset transformation matrix

		//static float angle = 0.0f;
		//angle += 1.0f;  // Increase rotation angle
		//glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate around Z-axis

		//drawTriangle();
		//drawParallelogramWithTriangles();
		//drawTrapezoid();
		//drawPentagon();

		//drawSquare();
		drawOctagon();
		//drawHand();
		

		glfwSwapBuffers(window);

		glfwPollEvents();


	}
	// Once window is no longer open - END
	glfwTerminate();

	return 0;
}


