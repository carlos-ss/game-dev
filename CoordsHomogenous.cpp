#include <GLFW/glfw3.h>
#include <freeglut/glut.h>

#include <iostream>

void chkey_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class Coords {
	private:
		float position_x = 0.0f;
		float position_y = 0.0f;
		float position_z = 0.0f;
		float position_w = 0.0f;
		float width = 0.0f;
		float height = 0.0f;
		float color_r = 0.0f;
		float color_g = 0.0f;
		float color_b = 0.0f;
		float angle = 0.0f;

	public: 
		Coords() {}

	void set_position(float x, float y) {

		// make coords homogenous
		position_x = x;
		position_y = y;
		position_z = 0.0f;
		position_w = 1.0f;
	}

	void get_position(float* x, float* y) {
		*x = position_x/position_w;
		*y = position_y/position_w;
	}

	void set_size(float w, float h) {
		width = w;
		height = h;
	}
	
	void set_color(float r, float g, float b) {
		color_r = r;
		color_g = g;
		color_b = b;
	}

	void draw() {
		glPushMatrix();
		glTranslatef(position_x, position_y, position_z);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glScalef(width, height, 1.0f);
	
		// set color
		glColor3f(color_r, color_g, color_b);

		// draw square
		glBegin(GL_QUADS);
			glVertex2f(-width / 2, -height / 2);
			glVertex2f(width / 2, -height / 2);
			glVertex2f(width / 2, height / 2);
			glVertex2f(-width / 2, height / 2);
		glEnd();
		glPopMatrix();

	}
	void move(float dx, float dy) {

		float x, y, z, w;
		x = position_x;
		y = position_y;
		z = position_z;
		w = position_w;

		// Coord transformation movement
		x += w * dx;
		y += w * dy;

		// Transtlate from homogenous to cartesian
		position_x = x;
		position_y = y;

		// moves to infinity very quickly
		/*position_x += x / w;
		position_y += y / w;*/


	}

	void scale(float sx, float sy) {
		width *= sx;
		height *= sy;
	}

	void rotate(float angle) {
		this->angle += angle;
	}
};


int homogenousmain() {
	// GLFW init
	if (!glfwInit()) return -1;	

	// window init
	GLFWwindow* window = glfwCreateWindow(640, 480, "Transformations", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, chkey_callback);
	glfwMakeContextCurrent(window);

	Coords obj1, obj2;

	// init obj1 
	obj1.set_position(-0.5f, 0.0f);
	obj1.set_size(0.5f, 0.5f);
	obj1.set_color(1.0f, 0.0f, 0.0f);

	// init obj2
	obj2.set_position(0.5f, 0.0f);
	obj2.set_size(0.5f, 0.5f);
	obj2.set_color(0.0f, 1.0f, 0.0f);

	// render loop
	while (!glfwWindowShouldClose(window)) {

		//window size
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		// color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		// render
		obj1.draw();
		obj2.draw();

		obj1.move(0.001f, 0.001f );
		obj2.move(-0.001f, -0.001f);

		//obj1.scale(1.001f, 1.001f);
		//obj2.scale(0.999f, 0.999f);

		//obj1.rotate(1.0f);
		//obj2.rotate(-1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}