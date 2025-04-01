#include <glew/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

float posX = 0.0f, posY = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// Convert mouse coordinates to OpenGL's [-1,1] range
	posX = (2.0f * xpos / width) - 1.0f;
	posY = 1.0f - (2.0f * ypos / height);  // Flip Y axis

	std::cout << "Mouse position: " << posX << ", " << posY << std::endl;
}


int vertexScalingShaderSetUp() {
	const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform float sizeScale;
void main() {
	gl_Position = vec4(aPos.x * sizeScale, aPos.y * sizeScale, aPos.z, 1.0);
	
}
)glsl";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	return vertexShader;
}
int vertexMouseShaderSetUp() {
	const char* vertexShaderSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform vec2 mousePos;
        void main() {
            gl_Position = vec4(aPos.x + mousePos.x, aPos.y + mousePos.y, aPos.z, 1.0);
        }
    )glsl";
	unsigned int vertexShader  = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	return vertexShader;
}
int vertexShaderSetup() {

	const char* vertexShaderSource = R"glsl(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		
		void main() {
			gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
		}
		)glsl";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	return vertexShader;

}

int fragmenteShaderSetUp() {

	const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
void main() {
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)glsl";



	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	return fragmentShader;
}

int shaderProgramSetup(int vertexShader, int fragmentShader) {

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	return shaderProgram;

}

void polygonSetup() {
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // Bottom-left
	0.5f, -0.5f, 0.0f, // Bottom-right
	0.0f,  0.5f, 0.0f  // Top-center
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void scalePolygon(int shaderProgram) {

	static float scale = 0.0f;
	scale += 0.01f;
	float sizeScale = 0.5f + sin(scale) * 0.5f;

	// Set the scale uniform
	GLint scaleLoc = glGetUniformLocation(shaderProgram, "sizeScale");
	glUniform1f(scaleLoc, sizeScale);

}

void movePolygon(int shaderProgram) {

	// Set the offset uniform
	GLint mousePosLoc = glGetUniformLocation(shaderProgram, "mousePos");

	glUniform2f(mousePosLoc, posX, posY);
}

int shadersmain() {
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Window creation
	GLFWwindow* window = glfwCreateWindow(640, 480, "Shaders", NULL, NULL);

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
	//glfwSetCursorPosCallback(window, mouse_callback);

	//int vertexShader = vertexMouseShaderSetUp();
	int vertexShader = vertexScalingShaderSetUp();
	int fragmentShader = fragmenteShaderSetUp();

	int shaderProgram = shaderProgramSetup(vertexShader, fragmentShader);

	polygonSetup();

	// While window is open 
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		// Calculate scaling factor (pulse between 0.5 and 1.5)

		scalePolygon(shaderProgram);
		//movePolygon(shaderProgram);

		// draw
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Once window is no longer open - END
	glfwTerminate();


	return 0;
}


