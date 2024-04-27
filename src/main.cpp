#define STB_IMAGE_IMPLEMENTATION
#include <stbimg/stb_image.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shaderlink/shaderlink.h>
#include <cmath>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}   
void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main() {
	std:string root = "";
	//glfw initialization + window
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (window == NULL)
	{
    		std::cout << "Failed to create GLFW window" << std::endl;
   		glfwTerminate();
    		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	
	
	
	glfwSwapInterval(1);

	float vertices[] = {
     		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
    		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
     		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
    		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f  // top left
	};
	unsigned int indices[] = {  
    		0, 1, 3,   // first triangle
    		1, 2, 3    // second triangle
	};  
	float texCoords[] = {
   		1.0f, 1.0f,  //these all correspond to their vertex indices
		1.0f, 0.0f,  
    		0.0f, 1.0f,
		0.0f, 0.0f
	};
	//buffer objects and vertex attrib initialization
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);  
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	//vertex array obj
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//vertex attribute pointer init (+ vertex attribue array enabling ig)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	//init junk
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
	glfwSetErrorCallback(error_callback);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	//init texture shit
	int width, height, nrChannels;
	unsigned char *data = stbi_load(root << "assets/textures/wormie.png", &width, &height, &nrChannels, 0); 
	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);


        Shader shader(root << "assets/shaders/test.vs",root << "assets/shaders/test.fs");
	shader.use();
	while(!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		shader.use();
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		std::cout << std::to_string(greenValue);
		shader.setFloat4("color", 0.0f, greenValue, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);

	}
	
	glfwTerminate();	
	return 0;
}
