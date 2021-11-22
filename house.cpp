#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include<vector>

#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void mainCircle(GLuint& vao, GLuint& vbo, GLfloat x, GLfloat y, GLdouble radius);

void semicircle();
void circle();

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

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";
const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
"}\n\0";
const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.3f, 0.4f, 1.0f);\n"
"}\n\0";

// glfw: when window size changed this callback function executes the code // glfwSetFramebufferSizeCallback
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
    // glfw: initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: creating the  window
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

    // build and compiling the shader program
    int success;
    char errorInfo[512] = "";

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderBlack = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderBackground = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram();
    unsigned int shaderProgramBlack = glCreateProgram(); 
    unsigned int shaderProgramBackground = glCreateProgram(); 


    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    glShaderSource(fragmentShaderBlack, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShaderBlack); 
    glShaderSource(fragmentShaderBackground, 1, &fragmentShader5Source, NULL);
    glCompileShader(fragmentShaderBackground); 


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

    glAttachShader(shaderProgramBlack, vertexShader);
    glAttachShader(shaderProgramBlack , fragmentShaderBlack);
    glLinkProgram(shaderProgramBlack); 

    glAttachShader(shaderProgramBackground, vertexShader);
    glAttachShader(shaderProgramBackground , fragmentShaderBackground);
    glLinkProgram(shaderProgramBackground); 


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorInfo);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << errorInfo << "\n";
    }

    // delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set vertex data 
    GLfloat vertices[] = {
       0.4f,  -0.1f, 0.0f,  // top right // 0
       0.4f, -0.7f, 0.0f,  // bottom right // 1
      -0.4f, -0.7f, 0.0f,  // bottom left // 2
      -0.4f,  -0.1f, 0.0f   // top left  // 3
    };
    GLfloat roof[] = {
      -0.5f,  0.1f, 0.0f,   // top left //0 
      -0.5f,  -0.1f, 0.0f,   // bottom left //1
       0.5f,  0.1f, 0.0f,  // top right //2
       0.5f,  -0.1f, 0.0f  // bottom right //3
    };
    GLfloat door[] = {
       0.1f,  -0.3f, 0.0f,  // top right // 0
      0.1f, -0.7f, 0.0f,  // bottom right // 1
     -0.1f, -0.7f, 0.0f,  // bottom left // 2
     -0.1f,  -0.3f, 0.0f   // top left  // 3
    };
    GLfloat windows1[] = {
       -0.15f,  -0.25f, 0.0f,  // top right // 0
      -0.15f, -0.45f, 0.0f,  // bottom right // 1
     -0.35f, -0.45f, 0.0f,  // bottom left // 2
     -0.35f,  -0.25f, 0.0f   // top left  // 3
    };
    GLfloat windows2[] = {
      0.35f,  -0.25f, 0.0f,  // top right // 0
      0.35f, -0.45f, 0.0f,  // bottom right // 1
      0.15f, -0.45f, 0.0f,  // bottom left // 2
      0.15f,  -0.25f, 0.0f   // top left  // 3
    };
    GLfloat mini1[] = {
       -0.155f,  -0.255f, 0.0f,  // top right // 0
      -0.155f, -0.345f, 0.0f,  // bottom right // 1
     -0.245f, -0.345f, 0.0f,  // bottom left // 2
     -0.245f,  -0.255f, 0.0f   // top left  // 3
    };
    GLfloat mini2[] = {
       -0.155f,  -0.355f, 0.0f,  // top right // 0
      -0.155f, -0.445f, 0.0f,  // bottom right // 1
     -0.245f, -0.445f, 0.0f,  // bottom left // 2
     -0.245f,  -0.355f, 0.0f   // top left  // 3
    };
    GLfloat mini3[] = {
       -0.255f,  -0.355f, 0.0f,  // top right // 0
      -0.255f, -0.445f, 0.0f,  // bottom right // 1
     -0.345f, -0.445f, 0.0f,  // bottom left // 2
     -0.345f,  -0.355f, 0.0f   // top left  // 3
    };
    GLfloat mini4[] = {
       -0.255f,  -0.255f, 0.0f,  // top right // 0
      -0.255f, -0.345f, 0.0f,  // bottom right // 1
     -0.345f, -0.345f, 0.0f,  // bottom left // 2
     -0.345f,  -0.255f, 0.0f   // top left  // 3
    };
    GLfloat mini5[] = {
       0.345f,  -0.255f, 0.0f,  // top right // 0
      0.345f, -0.345f, 0.0f,  // bottom right // 1
     0.255f, -0.345f, 0.0f,  // bottom left // 2
     0.255f,  -0.255f, 0.0f   // top left  // 3
    };
    GLfloat mini6[] = {
       0.345f,  -0.355f, 0.0f,  // top right // 0
      0.345f, -0.445f, 0.0f,  // bottom right // 1
     0.255f, -0.445f, 0.0f,  // bottom left // 2
     0.255f,  -0.355f, 0.0f   // top left  // 3
    };
    GLfloat mini7[] = {
       0.245f,  -0.355f, 0.0f,  // top right // 0
      0.245f, -0.445f, 0.0f,  // bottom right // 1
     0.155f, -0.445f, 0.0f,  // bottom left // 2
     0.155f,  -0.355f, 0.0f   // top left  // 3
    };
    GLfloat mini8[] = {
       0.245f,  -0.255f, 0.0f,  // top right // 0
      0.245f, -0.345f, 0.0f,  // bottom right // 1
     0.155f, -0.345f, 0.0f,  // bottom left // 2
     0.155f,  -0.255f, 0.0f   // top left  // 3
    };
    
    // index buffer // Element Buffer Objects (EBO)
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices1[] = {
        0, 1, 3,   // first triangle
        0, 2, 3
    };
    unsigned int indices2[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices3[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices4[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices5[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices6[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices7[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices8[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices9[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices10[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices11[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };
    unsigned int indices12[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second rectangle
    };

    // set vertex buffer object anb vertex array object and element buffer objects 
    unsigned int VBOs[17], VAOs[17], EBOs[14];
    glGenVertexArrays(17, VAOs);
    glGenBuffers(17, VBOs);
    glGenBuffers(14, EBOs);

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
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(door), door, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //windows setup
       // bind vertex array object
    glBindVertexArray(VAOs[4]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(windows1), windows1, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //windows2 setup
       // bind vertex array object
    glBindVertexArray(VAOs[5]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(windows2), windows2, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini1 setup
       // bind vertex array object
    glBindVertexArray(VAOs[9]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini1), mini1, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices5), indices5, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini2 setup
       // bind vertex array object
    glBindVertexArray(VAOs[10]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini2), mini2, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices6), indices6, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini3 setup
       // bind vertex array object
    glBindVertexArray(VAOs[11]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini3), mini3, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[5]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices7), indices7, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini4 setup
       // bind vertex array object
    glBindVertexArray(VAOs[12]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[12]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini4), mini4, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[6]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices8), indices8, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //mini5 setup
       // bind vertex array object
    glBindVertexArray(VAOs[13]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[13]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini5), mini5, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[7]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices9), indices9, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //mini6 setup
       // bind vertex array object
    glBindVertexArray(VAOs[14]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[14]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini6), mini6, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[8]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices10), indices10, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini7 setup
       // bind vertex array object
    glBindVertexArray(VAOs[15]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[15]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini7), mini7, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[9]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices11), indices11, GL_STATIC_DRAW);

    // registered VBO as the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //mini8 setup
       // bind vertex array object
    glBindVertexArray(VAOs[16]);

    // bind vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[16]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mini8), mini8, GL_STATIC_DRAW);

    // bind element buffer objects
    // EBO is stored in the VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[10]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices12), indices12, GL_STATIC_DRAW);

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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// this call should output a yellow triangle        

        //Draw the circle using the next VAO
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[2]);
        semicircle();


        // draw rectangle door that is orange
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[3]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // draw square window that is black
        glUseProgram(shaderProgramBlack);
        glBindVertexArray(VAOs[4]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // draw square window that is black
        glUseProgram(shaderProgramBlack);
        glBindVertexArray(VAOs[5]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Draw the doorknob using the next VAO
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[6]);
        mainCircle(VAOs[6],VBOs[6],0.06f,-0.5f,0.02);

        //Draw the crescent Circle using the next VAO
        glUseProgram(shaderProgramYellow);
        mainCircle(VAOs[7],VBOs[7],0.4f,0.7f,0.2);

        //Draw the crescent background using the next VAO
        glUseProgram(shaderProgramBackground);
        mainCircle(VAOs[8],VBOs[8],0.3f,0.7f,0.2);

        // mini1
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[9]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini2
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[10]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini3
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[11]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini4
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[12]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini5
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[13]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini6
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[14]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini7
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[15]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // mini8
        glUseProgram(shaderProgramBackground);
        glBindVertexArray(VAOs[16]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers
        glfwSwapBuffers(window);

        // glfw: poll IO events (keys & mouse)
        glfwPollEvents();

    }

    // de-allocate all resources
    glDeleteVertexArrays(17, VAOs);
    glDeleteBuffers(17, VBOs);
    glDeleteBuffers(14, EBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramBlack);

    // glfw: terminate and clear all previously GLFW allocated resources
    glfwTerminate();
    return 0;
}
void semicircle() {
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

    glDrawArrays(GL_TRIANGLE_FAN, 0, DIV_COUNT / 2 + 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void circle() {
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
    coordA[coordIdx++] = 0.03f;
    coordA[coordIdx++] = 0.0f;

    // ... and then rotate it by angInc for each point.
    float xc = 0.03f;
    float yc = 0.0f;
    for (unsigned iDiv = 1; iDiv < DIV_COUNT; ++iDiv) {
        float xcNew = cosInc * xc - sinInc * yc;
        yc = sinInc * xc + cosInc * yc;
        xc = xcNew;

        coordA[coordIdx++] = xc;
        coordA[coordIdx++] = yc;
    }

    // Repeat first point as last point to close circle.
    coordA[coordIdx++] = 0.03f;
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

    glDrawArrays(GL_TRIANGLE_FAN, 0, DIV_COUNT + 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void mainCircle(GLuint& vao, GLuint& vbo, GLfloat x, GLfloat y, GLdouble radius){
    GLint numberOfSides=100;
    int numVertices = numberOfSides + 2;

    GLdouble twicePi = 8.0f * M_PI;

    std::vector<GLdouble> circleVerticesX;
    std::vector<GLdouble> circleVerticesY;

    circleVerticesX.push_back(x);
    circleVerticesY.push_back(y);

    for (int i = 1; i < numVertices; i++) {
        circleVerticesX.push_back(x + (radius *
            cos(i * twicePi / numberOfSides)));
        circleVerticesY.push_back(y + (radius *
            sin(i * twicePi / numberOfSides)));
    }

    std::vector<GLdouble> vertices;
    for (int i = 0; i < numVertices; i++) {
        vertices.push_back(circleVerticesX[i]);
        vertices.push_back(circleVerticesY[i]);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLdouble), vertices.data(), GL_STATIC_DRAW);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE,2 * sizeof(GLdouble), (void*)0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 27);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
