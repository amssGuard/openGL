#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* windnow, int width, int height);

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