#include <GLFW/glfw3.h>
#include <freeglut/glut.h>

#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class Coords {
	private:
		float position_x = 0.0f;
		float position_y = 0.0f;
		float width = 0.0f;
		float height = 0.0f;
		float color_r = 0.0f;
		float color_g = 0.0f;
		float color_b = 0.0f;

	public: 
		Coords() {}

	void set_position(float x, float y) {
		position_x = x;
		position_y = y;
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
		glTranslatef(position_x, position_y, 0.0f);
	
		glColor3f(color_r, color_g, color_b);

		glBegin(GL_QUADS);
			glVertex2d(-width / 2, -height / 2);
			glVertex2d(width / 2, -height / 2);
			glVertex2d(width / 2, height / 2);
			glVertex2d(-width / 2, height / 2);
		glEnd();
		glPopMatrix();

	}
};


int main() {
	// GLFW init
	if (!glfwInit()) return -1;	

	// window init
	GLFWwindow* window = glfwCreateWindow(640, 480, "Transformations", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
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



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}