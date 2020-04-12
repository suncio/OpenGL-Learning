#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
	window = glfwCreateWindow(3200, 1600, "Vertex Arrays", NULL, NULL);
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
			500.0f, 500.0f, 0.0f, 0.0f, // 0
			1000.0f, 500.0f, 1.0f, 0.0f, // 1
			1000.0f, 1000.0f, 1.0f, 1.0f, // 2
			500.0f, 1000.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
	
		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		
		// Create index buffer
		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 3200.0f, 0.0f, 1600.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-300, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(500, 500, 0));

		glm::mat4 mvp = proj * view * model;

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		Texture texture("res/textures/text.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float increment = 0.1;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			// Clear the screen
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, g, b, 1.0f);

			renderer.Draw(va, ib, shader);

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