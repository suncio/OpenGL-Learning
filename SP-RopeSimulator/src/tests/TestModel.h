#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "Model.h"
#include "Camera.h"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>
#include <functional>
 
namespace test {
	class TestModel : public Test
	{
	public:
		TestModel();
		~TestModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		int SCREEN_WIDTH, SCREEN_HEIGHT;
		GLfloat ZOOM;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Model> m_Model;
	};
}