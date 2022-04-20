#include "GlfwWindow.h"

namespace glfw
{
	Window::Window(int w, int h, std::string name)
	{
		glfw::Init();
		glfw::InitGLCore();
		//
		window = ::glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
		::glfwSetWindowUserPointer(window, this);
		//key
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->keyEventListener)
				win->keyEventListener({ key,scancode,action,mods });
			win->Onkey({ key,scancode,action,mods });

			});
		//mouse up down
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			/*if (win->mouseEventListener)
				win->mouseEventListener({ button,action, });*/
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			win->OnMouseUpDown({ button,action,mods,xpos,ypos});
			
			});
		//mouse move
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			if (win->mouseEventListener)
				win->mouseEventListener({ 0,0,0,xpos,ypos });
			win->OnMouseMove({ 0,0,0,xpos,ypos });

			});
		//char
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->charEventListener)
				win->charEventListener({ codepoint });
			win->OnChar({ codepoint });

			});
		//scroll
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->scrollEventListener)
				win->scrollEventListener({ xoffset,yoffset });
			win->OnScroll({ xoffset,yoffset });

			});
		//enter exit
		glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->mouseEnterExitEventListener)
				win->mouseEnterExitEventListener({ (bool)entered });
			win->OnMouseEnterExit({ (bool)entered });
			});
		//frame buffer
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->OnFrameBufferSize({ w,h });
			});


	}



	void Window::MakeContext()
	{
		::glfwMakeContextCurrent(window);
	}

	void Window::SwapBuffer()
	{
		::glfwSwapBuffers(window);
	}

	bool Window::IsWindowShouldClose()
	{
		return (bool)::glfwWindowShouldClose(window);
	}

	void Window::Destroy()
	{
		::glfwDestroyWindow(window);
	}

	int Window::GetWidth()
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return w;
	}

	int Window::GetHeight()
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return h;
	}

	void Window::AddKeyEventListener(std::function<void(KeyEvent)> _listener)
	{
		keyEventListener = _listener;
	}

	void Window::AddCharEventListener(std::function<void(CharEvent)> _listener)
	{
		charEventListener = _listener;
	}

	void Window::AddMouseEventListener(std::function<void(MouseEvent)> _listener)
	{
		mouseEventListener = _listener;
	}

	void Window::AddScrollEventListener(std::function<void(ScrollEvent)> _listener)
	{
		scrollEventListener = _listener;
	}

	void Window::AddMouseEnterExitEventListener(std::function<void(MouseEnterExitEvent)> _listener)
	{
		mouseEnterExitEventListener = _listener;
	}

	void PollEvents()
	{
		::glfwPollEvents();
	}

	void WaitEvents()
	{
		::glfwWaitEvents();
	}

	void Init()
	{
		::glfwInit();
	}

	void Terminate()
	{
		::glfwTerminate();
	}

	void InitGLCore()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	void VSync(bool _vsync)
	{
		_vsync ? glfwSwapInterval(1) : glfwSwapInterval(0);
	}

	void Vsync()
	{
		::glfwSwapInterval(1);
	}


}
namespace glad
{
	void Init()
	{
		::gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

}

namespace imgui
{
	void Init(glfw::Window* win)
	{
		const char* glsl_version = "#version 130";
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(win->window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

	}

	void NewFrame()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void EndFrame()
	{
		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void CleanUp()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}


namespace ak
{
	GLWindow::GLWindow(int w, int h, std::string name):Window(w, h, name)
	{
		MakeContext();
		OnContextCreated();
		//
		glad::Init();
		glfw::VSync(true);

		imgui::Init(this);

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF(font_robot_medium.c_str(), 20);

	}

	GLWindow::~GLWindow()
	{
		std::cout << "GLWindow::~GLWindow()" << "\n";
		//info.CleanUp();
	}

	void GLWindow::RePaint()
	{


		OnGLDraw();
		//imgui
		{
			imgui::NewFrame();
			OnImgui();
			imgui::EndFrame();
		}

		SwapBuffer();
	}

	void GLWindow::OnImgui()
	{

		ImGui::Begin("Window");
		ImGui::Text("this is text");
		ImGui::End();

	}

	void GLWindow::OnContextCreated()
	{
	}
	void GLWindow::OnGLDraw()
	{

	}

	void GLWindow::OnFrameBufferSize(glfw::SizeEvent e)
	{
		if (e.w != 0 && e.h != 0)
		{
			//info.Init(e.w, e.h);
			glViewport(0, 0, e.w, e.h);
			RePaint();
		}

	}

}
