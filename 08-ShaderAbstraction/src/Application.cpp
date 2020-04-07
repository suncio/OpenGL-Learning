#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Vertex Arrays", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	/* Initialize the GLEW library */
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
		
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	{
		float positions[] = {
			-0.5f, -0.5f, // 0
			 0.5f, -0.5f, // 1
			 0.5f,  0.5f, // 2
			-0.5f,  0.5f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
	
		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		
		// Create index buffer
		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float increment = 0.1;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			// Clear the screen
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			// Set shader and set uniform color
			shader.Bind();
			shader.SetUniform4f("u_Color", r, g, b, 1.0f);

			// Instead of binding vertex buffer, attrib pointer, just bind Vertex Array Object
			va.Bind();

			// Bind index buffer
			ib.Bind();

			// Draw
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			// Increment rgb
			if (b > 1.0f)
				increment = -0.01f;
			else if (g < 0.0f)
				increment = 0.1f;
			r += increment;
			g += 0.7f * increment;
			b += 1.3f * increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}