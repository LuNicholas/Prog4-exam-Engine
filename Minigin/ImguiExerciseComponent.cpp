#include "MiniginPCH.h"
#include "ImguiExerciseComponent.h"
#include "../imgui-1.87/imgui.h"
#include "../imgui-1.87/backends/imgui_impl_sdl.h"
#include "../imgui-1.87/backends/imgui_impl_opengl2.h"
#include "../imgui-1.87/imgui_plot.h"



dae::ImguiComponent::ImguiComponent()
	:m_Window(nullptr)
{
	m_SamplesExcercise1 = new int(1);
	m_SamplesExcercise2 = new int(1);
}
dae::ImguiComponent::~ImguiComponent()
{
	delete m_SamplesExcercise1;
	delete m_SamplesExcercise2;
}
void dae::ImguiComponent::SetWindow(SDL_Window* sdlWindow)
{
	m_Window = sdlWindow;
}

void dae::ImguiComponent::Update(float)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ImGui::Begin("Excercise1");
	ImGui::SetWindowSize(ImVec2(300, 450));
	ImGui::InputInt("#samples", m_SamplesExcercise1);
	if (*m_SamplesExcercise1 < 1)
		*m_SamplesExcercise1 = 1;

	if (ImGui::Button("Trash the cash"))
	{

		m_stepSizes.clear();
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
			m_stepSizes.push_back(float(stepsize));


		m_ValuesExcercise1.clear();
		for (int j = 0; j < int(m_stepSizes.size()); j++)
			m_ValuesExcercise1.push_back(0);

		m_ValuesExcercise1 = TrashTheCash<int>(*m_SamplesExcercise1, int(m_stepSizes.size()));
	}
	ImGui::End();



	ImGui::Begin("Excercise2");
	ImGui::SetWindowSize(ImVec2(300, 450));
	ImGui::InputInt("#samples", m_SamplesExcercise2);
	if (*m_SamplesExcercise2 < 1)
		*m_SamplesExcercise2 = 1;

	if (ImGui::Button("Trash the cash with gameObject3D"))
	{

		m_stepSizes.clear();
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
			m_stepSizes.push_back(float(stepsize));


		m_ValuesExcercise2Go.clear();
		for (int j = 0; j < int(m_stepSizes.size()); j++)
			m_ValuesExcercise2Go.push_back(0);

		m_ValuesExcercise2Go = TrashTheCash<GameObject3D>(*m_SamplesExcercise2, int(m_stepSizes.size()));

	}
	if (ImGui::Button("Trash the cash with gameObject3DAlt"))
	{

		m_stepSizes.clear();
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
			m_stepSizes.push_back(float(stepsize));


		m_ValuesExcercise2Alt.clear();
		for (int j = 0; j < int(m_stepSizes.size()); j++)
			m_ValuesExcercise2Alt.push_back(0);

		m_ValuesExcercise2Alt = TrashTheCash<GameObject3DAlt>(*m_SamplesExcercise2, int(m_stepSizes.size()));

	}
	ImGui::End();



}
void dae::ImguiComponent::FixedUpdate(float)
{
}

void dae::ImguiComponent::Render() const
{

	ImGui::Begin("Excercise1");
	if (m_ValuesExcercise1.size() > 0)
	{	
		ImGui::PlotConfig conf;
		conf.values.xs = m_stepSizes.data();
		conf.values.ys = m_ValuesExcercise1.data();
		conf.values.count = int(m_ValuesExcercise1.size());
		conf.scale.min = -1;
		conf.scale.max = *std::max_element(m_ValuesExcercise1.begin(), m_ValuesExcercise1.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(250, 150);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot1", conf);
	}
	ImGui::End();



	ImGui::Begin("Excercise2");

	if (m_ValuesExcercise2Go.size() > 0)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_stepSizes.data();
		conf.values.ys = m_ValuesExcercise2Go.data();
		conf.values.count = int(m_ValuesExcercise2Go.size());
		conf.scale.min = -1;
		conf.scale.max = *std::max_element(m_ValuesExcercise2Go.begin(), m_ValuesExcercise2Go.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 1.f;

		ImGui::Plot("GameObject", conf);
	}

	if (m_ValuesExcercise2Alt.size() > 0)
	{
		ImGui::PlotConfig conf;
		conf.values.xs = m_stepSizes.data();
		conf.values.ys = m_ValuesExcercise2Alt.data();
		conf.values.count = int(m_ValuesExcercise2Alt.size());
		conf.scale.min = -1;
		conf.scale.max = *std::max_element(m_ValuesExcercise2Alt.begin(), m_ValuesExcercise2Alt.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 1.f;

		ImGui::Plot("GameObjectAlt", conf);
	}


	if (m_ValuesExcercise2Go.size() > 0 && m_ValuesExcercise2Alt.size() > 0)
	{
		ImGui::Text("combined:");

		const float* y_data[] = { m_ValuesExcercise2Go.data(), m_ValuesExcercise2Alt.data()};


		ImGui::PlotConfig conf;
		conf.values.xs = m_stepSizes.data();
		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
		conf.values.count = int(m_ValuesExcercise2Go.size());
		conf.scale.min = -1;
		conf.scale.max = *std::max_element(m_ValuesExcercise2Go.begin(), m_ValuesExcercise2Go.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 1.f;

		ImGui::Plot("GameObject", conf);
	}

	ImGui::End();



	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}



