#include "Test.h"
#include "imgui/imgui.h"

namespace test {
	struct ShaderDeleter {
		void operator() (Test* p) {
			std::cout << "Calling delete for Shader object... \n";
			delete p;
		}
	};

	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{

	}

	const std::string TestMenu::GetTypeName() 
	{ 
		return "TestMenu"; 
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}