#include "TestModel.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	TestModel::TestModel()
		: 
		SCREEN_WIDTH(1920), 
		SCREEN_HEIGHT(1920),
		ZOOM(45.0f)
	{

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		glm::mat4 projection = glm::perspective(ZOOM, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down

		m_Shader = std::make_unique<Shader>("res/shaders/ModelLoad.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("projection", projection);
		m_Shader->SetUniformMat4f("view", view);
		m_Shader->SetUniformMat4f("model", model);

		m_Model = std::make_unique<Model>("res/models/backpack/backpack.obj");
		
	}

	TestModel::~TestModel()
	{

	}

	void TestModel::OnUpdate(float deltaTime)
	{
		// m_UpdateFunction(m_Camera);
	}

	void TestModel::OnRender()
	{
		// Renderer renderer;
		m_Model->draw(m_Shader);	
	}

	void TestModel::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}

