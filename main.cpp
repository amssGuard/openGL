#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* windnow, int width, int height);

//now we declare our vertex shader.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";

//now we declare our fragment shader.
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main() {
	glfwInit();
	//THE VERSION WE WANT TO USE OF OPENGL WE INITIALIZE THAT IS 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//TELLING GLFW THAT WE WANT TO USE A SUBSET OF OPENGL WITHOUT BACKWARDS COMPATIBLE FEATURES WHICH WE NO LONGER NEED.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//returning a window object that we'll later need for other GLFW operations.
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//telling GLFW to make the context of our window the main context on the current thread.
	glfwMakeContextCurrent(window);

	//as GLAD manages function poinntners for OpenGL so we want to initialize GLAD before we call any OpenGL function
	//we pass GLAD the function to load the address of the OpenGL function pointers which is OS-specific.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	//before rendering telling OpenGL the coordinnates and the size of the rendering window.
	glViewport(0, 0, 800, 600);

	//if resizing the window the viewport should be adjusted as well. we register a callback function (frambuffer_size_callback) on the window, that gets call everytime window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//we now specify three vertices, each vertex having a 3D position
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f
	};

	//This is the first occurrence of an OpenGL object, this buffer has a uniqueID that corresponds with the buffer,so we can generate one with a bufferID  using the glGenBuffers fnt
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//we now bind the buffer to the GL_ARRAY_BUFFER targe with the glBindBuffer function
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*
	 from this point on any buffer calls we make on the GL_ARRAT_BUFFER will be used to configure the currently bound buffer, which is VBO.
	 Then we can make a call to glBufferData function that copies the previously defined vertex data into the buffer's memory
	*/

	//glBUfferData is a function targeted to copy user-defined datat into the a currently bound buffer.
	//the first argument is the type of the buffer, second argument is the size of the data in bytes, third arrgument is the data and fourth is how we want the gpu to manage the data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//we have GL_STREAM_DRAW, GL_STATIC_DRAM, GL_DYNAMIC_DRAW

	//now we store the vertex shader as an unsigned int and create the shader with glCreateShader and specify the type of shader we want 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//next we attach the haderr source code to the shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//the glShadersource function, first arg takes the shader object to compile, sec arg no. of string we're passing as souce code, third the actual source code of the vertex,fourth we keep it null

	//The process for compiling a fragment shader is similar to the vertex shader, we just use the GL_FRAGMENT_SHADER constant as the shader type.
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//checking if the shader is was compiled
	/*int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "SHADER::FRAGMENT::COMPILATION SUCCESS"<<std::endl;
	}*/

	//so now don't wasnt the application to draw a single image and then  immediately quit and close the window, so we now call the render loop
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}

	glfwTerminate();
	return	0;
}

void framebuffer_size_callback(GLFWwindow* windnow, int width, int height) {
	glViewport(0, 0, width, height);
}