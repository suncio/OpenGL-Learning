#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "RopeSimulator.h"


namespace test {
	class TestRopeSimulator : public Test
	{
	public:
		TestRopeSimulator();
		~TestRopeSimulator();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

		void DrawPoints();

		void Setup();
	private:
		RopeSimulator rope;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBufferPoints;
		std::unique_ptr<IndexBuffer> m_IndexBufferLines;
	};
}