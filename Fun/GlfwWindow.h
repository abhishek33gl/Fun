#pragma once
#include<string>
#include<vector>
#include<string>
#include<iostream>
#define GL_FRAMEBUFFER_SRGB 0x8DB9
#define GL_SRGB8_ALPHA8 0x8C43
#define repeat_for(times) for(int i=0;i<times;i++)
#define S__(s) std::string(s).c_str()
#define TO_S(s) std::to_string(s)
#define FONT_PATH_ROBOTO(name) 
static auto font_robot = [](std::string name = "Medium")->std::string {
	return std::string("D:\\win10\\software\\fonts\\Roboto\\Roboto-" + name + ".ttf");
};
static auto font_robot_medium = font_robot();
#include<functional>
#include"glad/glad.h"
#include<GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace glfw
{
	struct KeyEvent
	{
		int key, scancode, action, mods;
	};
	
	struct CharEvent
	{
		unsigned int codepoint;
	};
	struct MouseEvent
	{
		int button, action, mods;
		double x, y;
	};
	struct ScrollEvent
	{
		double xoffset, yoffset;
	};
	struct MouseEnterExitEvent
	{
		bool isEntered;
	};
	struct SizeEvent
	{
		int w, h;
	};
	class Window
	{

	public:
		GLFWwindow* window;
		//listener
		std::function<void(KeyEvent)> keyEventListener = nullptr;
		std::function<void(CharEvent)> charEventListener = nullptr;
		std::function<void(MouseEvent)> mouseEventListener = nullptr;
		std::function<void(ScrollEvent)> scrollEventListener = nullptr;
		std::function<void(MouseEnterExitEvent)> mouseEnterExitEventListener = nullptr;


		Window(int w, int h, std::string name);
		~Window() {};
		void MakeContext();
		void SwapBuffer();
		bool IsWindowShouldClose();
		void Destroy();
		int GetWidth();
		int GetHeight();

		void AddKeyEventListener(std::function<void(KeyEvent)> _listener);
		void AddCharEventListener(std::function<void(CharEvent)> _listener);
		void AddMouseEventListener(std::function<void(MouseEvent)> _listener);
		void AddScrollEventListener(std::function<void(ScrollEvent)> _listener);
		void AddMouseEnterExitEventListener(std::function<void(MouseEnterExitEvent)> _listener);

	protected:
		virtual void OnFrameBufferSize(SizeEvent e) {};
		virtual void Onkey(KeyEvent e) {};
		virtual void OnChar(CharEvent e) {};
		virtual void OnScroll(ScrollEvent e) {};
		virtual void OnMouseEnterExit(MouseEnterExitEvent e) {};
		virtual void OnMouseMove(MouseEvent e) {};
		virtual void OnMouseUpDown(MouseEvent e) {};

	};

	void PollEvents();
	void WaitEvents();
	void Init();
	void Terminate();
	void InitGLCore();
	void VSync(bool _vsync);

}
namespace glad
{
	void Init();
}

namespace imgui
{
	void Init(glfw::Window* win);
	void NewFrame();
	void EndFrame();
	void CleanUp();
}


namespace ak
{
	using namespace glfw;
	class GLWindow :public Window
	{
	public:

		GLWindow(int w, int h, std::string name);
		~GLWindow();
		void RePaint();
		virtual void OnImgui();
		virtual void OnGLDraw();
		virtual void OnContextCreated();
		virtual void OnFrameBufferSize(SizeEvent e) override;
	};
}
