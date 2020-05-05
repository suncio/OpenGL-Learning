#include "TestShaderToy.h"

#include "Renderer.h"
#include "imgui/imgui.h"


namespace test {

	TestShaderToy::TestShaderToy()
	{
		float positions[] = {
			-500.0f, -500.0f, 0.0f, 0.0f, // 0
			 500.0f, -500.0f, 1.0f, 0.0f, // 1
			 500.0f,  500.0f, 1.0f, 1.0f, // 2
			-500.0f,  500.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		/*
		uniform vec3 iResolution;
		uniform float iTime;
		uniform vec4 iMouse;
		in vec2 texcoord;
		*/

		std::cout << "Make unique Shader ptr for TestShaderToy \n";
		m_Shader = std::make_unique<Shader>("res/shaders/ShaderToyTest.shader");
		m_Shader->Bind();
		// m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);	

		glm::vec3 iResolution = glm::vec3(2400, 1800, 0);
		m_Shader->SetUniformVec3("iResolution", iResolution);
		// m_Shader->SetUniform3f("iResolution", 2400, 1800, 0);
	}

	TestShaderToy::~TestShaderToy()
	{

	}

	const std::string TestShaderToy::GetTypeName()
	{
		return "TestShaderToy";
	}

	void TestShaderToy::OnUpdate(float deltaTime)
	{

	}

	void TestShaderToy::OnRender()
	{
		Renderer renderer;

		// m_Texture->Bind();

		{
			/*
			uniform vec3 iResolution;
			uniform float iTime;
			uniform vec4 iMouse;
			*/
			m_Shader->Bind();
			m_Shader->SetUniform1f("iTime", playtime_in_second);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
			m_Shader->SetUniform4f("iMouse", ImGui::GetMousePos().x, ImGui::GetMousePos().y, ImGui::GetMousePos().x, ImGui::GetMousePos().y);
		}
	}

	void TestShaderToy::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("iMouse Pos: %f, %f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	}

}