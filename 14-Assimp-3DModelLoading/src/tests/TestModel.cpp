#include "TestModel.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	TestModel::TestModel()
		/*
		: m_Proj(glm::ortho(0.0f, 3200.0f, 0.0f, 1600.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-300, 0, 0))),
		m_TranslationA(500, 500, 0), m_TranslationB(1200, 500, 0)
		*/
	{
		m_Model.draw();
	}

	TestModel::~TestModel()
	{
	}

	void TestModel::OnUpdate(float deltaTime)
	{

	}

	void TestModel::OnRender()
	{
		//GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		/*
		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		*/
	}

	void TestModel::OnImGuiRender()
	{
		/*
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 800.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 800.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		*/
	}

}