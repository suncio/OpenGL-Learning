#include "TestRopeSimulator.h"

#include "imgui/imgui.h"

namespace test {

	TestRopeSimulator::TestRopeSimulator()
		: rope(10)
	{
		Setup();
	}

	TestRopeSimulator::~TestRopeSimulator()
	{
	}

	void TestRopeSimulator::OnUpdate(float deltaTime)
	{
		rope.updateStates(deltaTime);
		Setup();
	}

	void TestRopeSimulator::OnRender()
	{
		DrawPoints();
	}

	void TestRopeSimulator::OnImGuiRender()
	{
		
		if (ImGui::Button("Initialize"))
		{
			rope.init();
		}
		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void TestRopeSimulator::DrawPoints()
	{
		GLCall(glClearColor(255, 250, 250, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		/*
		for (int i = 0; i < rope.masses.size(); i++)
		{
			std::cout << "x: " << rope.masses[i]->getPos().x
				<< ",  y: " << rope.masses[i]->getPos().y << std::endl;
		}
		std::cout << std::endl;
		*/

		{
			m_VAO->Bind();
			m_IndexBufferPoints->Bind();
			GLCall(glPointSize(25.0f));
			GLCall(glDrawElements(GL_POINTS, m_IndexBufferPoints->GetCount(), GL_UNSIGNED_INT, nullptr));
			m_VAO->Unbind();
			m_IndexBufferPoints->Unbind();
		}

		{
			m_VAO->Bind();
			m_IndexBufferLines->Bind();
			// GLCall(glLineWidth(2.0f));
			GLCall(glDrawElements(GL_LINES, m_IndexBufferLines->GetCount(), GL_UNSIGNED_INT, nullptr));
			m_VAO->Unbind();
			m_IndexBufferLines->Unbind();
		}
	}

	void TestRopeSimulator::Setup()
	{
		float *positions = new float[2 * rope.masses.size()];
		for (int i = 0; i < rope.masses.size(); i++)
		{
			positions[2 * i + 0] = rope.masses[i]->getPos().x / 10.0f;
			positions[2 * i + 1] = rope.masses[i]->getPos().y / 10.0f;
		}

		unsigned int *indices_points = new unsigned int[rope.masses.size()];
		for (int i = 0; i < rope.masses.size(); i++)
		{
			indices_points[i] = i;
		}

		unsigned int *indices_lines = new unsigned int[2 * rope.edges.size()];
		for (int i = 0; i < rope.edges.size(); i++)
		{
			indices_lines[2 * i + 0] = i;
			indices_lines[2 * i + 1] = i + 1;
		}


		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2 * rope.masses.size() * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBufferPoints = std::make_unique<IndexBuffer>(indices_points, rope.masses.size());
		m_IndexBufferLines = std::make_unique<IndexBuffer>(indices_lines, 2 * rope.edges.size());
	}
}