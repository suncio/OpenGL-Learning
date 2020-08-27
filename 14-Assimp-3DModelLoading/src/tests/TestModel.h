#pragma once

#include "Test.h"

#include "Model.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>


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
		std::string m_FilePath;
		Model m_Model{ "res/models/4-low-poly-wolfs/source/Sketchfab_2020_04_19_20_57_46.blend" };
		//glm::mat4 m_Proj, m_View;
		//glm::vec3 m_TranslationA, m_TranslationB;
	};
}