#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "../imgui-1.87/imgui.h"
#include "../imgui-1.87/backends/imgui_impl_sdl.h"
#include "../imgui-1.87/backends/imgui_impl_opengl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, glm::vec4 destRect, glm::vec4 srcRect) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(destRect.x);
	dst.y = static_cast<int>(destRect.y);
	dst.w = static_cast<int>(destRect.z);
	dst.h = static_cast<int>(destRect.w);

	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.z);
	src.h = static_cast<int>(srcRect.w);


	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderLine(int x1, int y1, int x2, int y2) const
{
	SDL_SetRenderDrawColor(m_Renderer, 1, 0, 0, 1);
	SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
}