#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << 
			function << " " << file << ":" << line << 
			std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSource 
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FREAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FREAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	GLCall( unsigned int id = glCreateShader(type) );
	const char* src = source.c_str();
	GLCall( glShaderSource(id, 1, &src, nullptr) );
	GLCall( glCompileShader(id) );

	int result;
	GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
	if (result == GL_FALSE)
	{
		int length;
		GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
		char* message = (char *)alloca(length * sizeof(char));
		GLCall( glGetShaderInfoLog(id, length, &length, message) );
		std::cout << "Failed to compile"  <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<  "shader!"
			<< std::endl;
		std::cout << message << std::endl;
		GLCall( glDeleteShader(id) );
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall( glAttachShader(program, vs) );
	GLCall( glAttachShader(program, fs) );
	GLCall( glLinkProgram(program) );

	GLint program_linked;
	GLCall( glGetProgramiv(program, GL_LINK_STATUS, &program_linked) );
	std::cout << "Program link status: " << program_linked << std::endl;
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
		std::cout << "Failed to link program" << std::endl;
		std::cout << message << std::endl;
	}

	GLCall( glValidateProgram(program) );

	GLCall( glDeleteShader(vs) );
	GLCall( glDeleteShader(fs) );

	return program;
}

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

	// Create vao explicitly
	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	// Create buffer and copy data
	unsigned int buffer;
	GLCall( glGenBuffers(1, &buffer) );
	GLCall( glBindBuffer(GL_ARRAY_BUFFER, buffer) );
	GLCall( glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW) );

	// Define vertex layout
	GLCall( glEnableVertexAttribArray(0) );
	GLCall( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0) );

	// Create index buffer
	unsigned int ibo;
	GLCall( glGenBuffers(1, &ibo) );
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo) );
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW) );

	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	std::cout << "Vertex" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "Fragment" << std::endl;
	std::cout << source.FragmentSource << std::endl;
	
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLCall( glUseProgram(shader) );

	GLCall( int u_Color = glGetUniformLocation(shader, "u_Color") );
	ASSERT(u_Color != -1);

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float increment = 0.1;

	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// Clear the screen
		GLCall( glClear(GL_COLOR_BUFFER_BIT) );

		// Set shader and set uniform color
		GLCall(glUseProgram(shader));
		GLCall(glUniform4f(u_Color ,r, g, b, 1.0f));

		// Instead of binding vertex buffer, attrib pointer, just bind Vertex Array Object
		GLCall(glBindVertexArray(vao));

		// Bind index buffer
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

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

	// Clean up VBO
	GLCall( glDeleteBuffers(1, &buffer) );
	GLCall( glDeleteProgram(shader) );

	glfwTerminate();
	return 0;
}