#include "canpch.h"
#include "Can.h"
#include "Can/EntryPoint.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "GameLayer.h"

class FlappyBird : public Can::Application
{
public:
	FlappyBird(const Can::WindowProps& props)
		:Application(props)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF("assets/fonts/Poppins/Poppins-Light.otf", 32.0f);
		PushLayer(new GameLayer());
	}

	~FlappyBird()
	{

	}
};

Can::Application* Can::CreateApplication(const Can::WindowProps& props)
{
	return new FlappyBird(props);
}