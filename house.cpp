#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void semicircle();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = 
"#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char* fragmentShaderSource = 
"#version 450 core\n"
"out vec4 FragmentColor;\n"
"void main()\n"
"{\n"
"   FragmentColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char *fragmentShader1Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *fragmentShader2Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

// glfw: when window size changed this callback function executes // glfwSetFramebufferSizeCallback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // glfw: the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

// glfw: process keys
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // glfw: initialize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "House", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << "\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << "\n";
        return -1;
    }

    // build and compile shader program
    int success;
    char errorInfo[512] = "";

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram();

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShaderOrange,1,&fragmentShader1Source,NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow,1,&fragmentShader2Source,NULL);
    glCompileShader(fragmentShaderYellow);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorInfo);
        std::cout << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << errorInfo << "\n";
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorInfo);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << errorInfo << "\n";
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorInfo);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << errorInfo << "\n";
    }

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set vertex data 
    float vertices[] = {
       0.4f,  -0.1f, 0.0f,  // top right // 0
       0.4f, -0.7f, 0.0f,  // bottom right // 1
      -0.4f, -0.7f, 0.0f,  // bottom left // 2
      -0.4f,  -0.1f, 0.0f   // top left  // 3
    };
    float roof[] = {
      -0.5f,  0.1f, 0.0f,   // top left //0 
      -0.5f,  -0.1f, 0.0f,   // bottom left //1
       0.5f,  0.1f, 0.0f,  // top right //2
       0.5f,  -0.1f, 0.0f  // bottom right //3
     };
     float door[]={
        0.1f,  -0.3f, 0.0f,  // top right // 0
       0.1f, -0.7f, 0.0f,  // bottom right // 1
      -0.1f, -0.7f, 0.0f,  // bottom left // 2
      -0.1f,  -0.3f, 0.0f   // top left  // 3
    };
    // index buffer // Element Buffer Objects (EBO)
    unsigned int indices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices1[]={
        0, 1, 3,   // first triangle
        0, 2, 3  
    };
    unsigned int indices2[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };


    // set vertex buffer object anb vertex array object and element buffer objects 
    unsigned int VBOs[5], VAOs[5], EBOs[3];
    glGenVertexArrays(5, VAOs);
    glGenBuffers(5, VBOs);
    glGenBuffers(3, EBOs);
    
//rectangle body setup 
    // bind vertex array object
    glBindVertexArray(VAOs[0]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

//rectangle roof setup
    // bind vertex array object
    glBindVertexArray(VAOs[1]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roof), roof, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

//door setup
    // bind vertex array object
    glBindVertexArray(VAOs[3]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(door), door, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
         // draw triangles for rectangle that is orange
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[0]); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // then we draw the roof using the data from the second VAO// when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);	// this call should output a yellow triangle        
 
 
        //Draw the circle using the next VAO
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[2]);
        semicircle();

        // draw rectangle door that is orange
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[3]); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
/* 
        //Draw the circle for crescent using the next VAO
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[4]);
        circle1(); */

        // glfw: swap buffers
        glfwSwapBuffers(window);

        // glfw: poll IO events (keys & mouse)
        glfwPollEvents();

    }

    // de-allocate all resources
    glDeleteVertexArrays(5, VAOs);
    glDeleteBuffers(5, VBOs);
    glDeleteBuffers(3, EBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);

    // glfw: terminate and clear all previously GLFW allocated resources
    glfwTerminate();
    return 0;
}
void semicircle(){
    // Number of segments the circle is divided into.
const unsigned DIV_COUNT = 100;

// Will use a triangle fan rooted at the origin to draw the circle. So one additional
// point is needed for the origin, and another one because the first point is repeated
// as the last one to close the circle.
GLfloat* coordA = new GLfloat[(DIV_COUNT + 2) * 2];

// Origin.
unsigned coordIdx = 0;
coordA[coordIdx++] = 0.0f;
coordA[coordIdx++] = 0.0f;

// Calculate angle increment from point to point, and its cos/sin.
float angInc = 2.0f * M_PI / static_cast<float>(DIV_COUNT);
float cosInc = cos(angInc);
float sinInc = sin(angInc);

// Start with vector (1.0f, 0.0f), ...
coordA[coordIdx++] = 0.4f;
coordA[coordIdx++] = 0.0f;

// ... and then rotate it by angInc for each point.
float xc = 0.4f;
float yc = 0.0f;
for (unsigned iDiv = 1; iDiv < DIV_COUNT; ++iDiv) {
    float xcNew = cosInc * xc - sinInc * yc;
    yc = sinInc * xc + cosInc * yc;
    xc = xcNew;

    coordA[coordIdx++] = xc;
    coordA[coordIdx++] = yc;
}

// Repeat first point as last point to close circle.
coordA[coordIdx++] = 0.4f;
coordA[coordIdx++] = 0.0f;

GLuint vboId = 0;
glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glBufferData(GL_ARRAY_BUFFER, (DIV_COUNT + 2) * 2 * sizeof(GLfloat), coordA, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

delete[] coordA;


glBindBuffer(GL_ARRAY_BUFFER, vboId);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
glEnableVertexAttribArray(0);

glDrawArrays(GL_TRIANGLE_FAN, 0, DIV_COUNT/2 +2);

glBindBuffer(GL_ARRAY_BUFFER, 0);
}