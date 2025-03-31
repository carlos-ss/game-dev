#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>



int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    // Configure window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple Hexagon", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) return -1;

    // Hexagon vertices (6 points)
    glm::vec3 hexagonPoints[] = {
    {    0.0f, 0.0f, 0.0f,},
    { 0.0f, 0.5f, 0.0f },     // Top (0)
    { 0.433f, 0.25f, 0.0f },   // Top-right (1)
    { 0.433f, -0.25f, 0.0f },  // Bottom-right (2)
    { 0.0f, -0.5f, 0.0f },     // Bottom (3)
    { -0.433f, -0.25f, 0.0f }, // Bottom-left (4)
    { -0.433f, 0.25f, 0.0f }   // Top-left (5)
    };

    glm::mat4 hexagonTransform = glm::mat4(1.0f);
    hexagonTransform = glm::translate(hexagonTransform, glm::vec3(0.0f, 0.0f, 0.0f));
    hexagonTransform = glm::scale(hexagonTransform, glm::vec3(0.5f, 0.5f, 1.0f));

    // Create VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hexagonPoints), hexagonPoints, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int indices[] = {
        // Triangle fan around center point (vertex 0)
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1
    };


    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Shader sources
    const char* vertexShaderSource = R"glsl(
    #version 400 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
    }
    )glsl";


    const char* fragmentShaderSource = R"glsl(
    #version 400 core
    out vec4 FragColor;
    
    void main() {
        FragColor = vec4(0.5, 0.8, 1.0, 1.0); // Light blue color
    }
    )glsl";


    // Tessellation control shader
    const char* tessControlShaderSource = R"glsl(
    #version 400 core
    layout(vertices = 3) out;
    void main() {
    if (gl_InvocationID == 0) {
        // Set tessellation levels for all edges
        gl_TessLevelOuter[0] = 5.0;
        gl_TessLevelOuter[1] = 5.0;
        gl_TessLevelOuter[2] = 5.0;
        gl_TessLevelInner[0] = 5.0;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    }
    )glsl";

    // Tessellation evaluation shader
    const char* tessEvalShaderSource = R"glsl(
    #version 400 core
 layout(triangles, equal_spacing, ccw) in;
    void main() {
 
        gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) + 
                      (gl_TessCoord.y * gl_in[1].gl_Position) + 
                      (gl_TessCoord.z * gl_in[2].gl_Position);
    }
    )glsl";



    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint tessControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
    glShaderSource(tessControlShader, 1, &tessControlShaderSource, NULL);
    glCompileShader(tessControlShader);


    GLuint tessEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    glShaderSource(tessEvalShader, 1, &tessEvalShaderSource, NULL);
    glCompileShader(tessEvalShader);
    

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
 

    // Create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, tessControlShader);
    glAttachShader(shaderProgram, tessEvalShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	glDeleteShader(tessControlShader);
	glDeleteShader(tessEvalShader);



    // Enable wireframe mode (optional)
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Pass transformation matrix to shader
        GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(hexagonTransform));

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        //glPatchParameteri(GL_PATCH_VERTICES, 6);  // Tell OpenGL we're using 6-vertex patches
        //glDrawArrays(GL_PATCHES, 0, 6);  // Draw as patches instead of triangles

        //glPatchParameteri(GL_PATCH_VERTICES, 3);  // Now using triangles
        //glDrawElements(GL_PATCHES, 8, GL_UNSIGNED_INT, 0);  // Draw as triangle fan

        glPatchParameteri(GL_PATCH_VERTICES, 3);
        glDrawElements(GL_PATCHES, 18, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}