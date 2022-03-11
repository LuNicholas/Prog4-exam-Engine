#pragma once
#include "GameObject.h"
#include "Component.h"
#include <chrono>

struct Transform
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	Transform transform;
	int ID;

	inline GameObject3D operator+=(GameObject3D a)
	{
		ID += a.ID;
		return *this;
	}
};

class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;

	inline GameObject3DAlt operator+=(GameObject3DAlt a)
	{
		ID += a.ID;
		return *this;
	}
};

namespace dae
{
	class ImguiComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;
		void SetWindow(SDL_Window* sdlWindow);

		~ImguiComponent();
		ImguiComponent(const ImguiComponent& other) = delete;
		ImguiComponent(ImguiComponent&& other) = delete;
		ImguiComponent& operator=(const ImguiComponent& other) = delete;
		ImguiComponent& operator=(ImguiComponent&& other) = delete;

	private:
		ImguiComponent();

		int* m_SamplesExcercise1 = nullptr;
		int* m_SamplesExcercise2 = nullptr;
		std::vector<float> m_ValuesExcercise1;
		std::vector<float> m_ValuesExcercise2Go;
		std::vector<float> m_ValuesExcercise2Alt;
		std::vector<float> m_stepSizes;

		SDL_Window* m_Window;

		template <class T>
		std::vector<float> TrashTheCash(int samples, int stepSizesSize);

	};
}

template <class T>
std::vector<float> dae::ImguiComponent::TrashTheCash(int samples, int stepSizes)
{
	std::vector<float> output;

	for (int j = 0; j < stepSizes; j++)
		output.push_back(0);

	for (int currentSample = 0; currentSample < samples; currentSample++)
	{
		std::vector<T> arr;
		arr.resize(1000000);
		std::vector<float> results;


		auto startTime = std::chrono::high_resolution_clock::now();

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			startTime = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < int(arr.size()); i += stepsize)
			{
				arr[i] += arr[i];
			}

			auto endTime = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();


			results.push_back(float(time));
		}
		for (int j = 0; j < int(output.size()) - 1; j++)
		{
			output.at(j) += results.at(j);
		}
	}
	for (float& value : output)
	{
		value /= samples;
	}

	return output;
}