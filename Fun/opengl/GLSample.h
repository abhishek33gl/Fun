#pragma once
#include"..\GlfwWindow.h"
#include<vector>
namespace ak
{
	class GLSample;
	class GLSampleWindow :public GLWindow
	{
		std::vector<GLSample*> samples;
		friend class GLSample;
		int active_sample_index = -1;
		void VisibleGLSample(int index);
	public:
		GLSampleWindow();
		void AddGLSample(GLSample& sample);

	protected:
		virtual void OnImgui();
		virtual void OnGLDraw();
		virtual void OnContextCreated();
		virtual void OnFrameBufferSize(SizeEvent e);
		virtual void Onkey(KeyEvent e) override;
		virtual void OnChar(CharEvent e) override;
		virtual void OnScroll(ScrollEvent e) override;
		virtual void OnMouseMove(MouseEvent e) override;
		virtual void OnMouseUpDown(MouseEvent e)override;
		
	};
	class GLSample
	{
	protected:
		GLSampleWindow* window=nullptr;
		friend class GLSampleWindow;
		std::string name;
	public:
		GLSample(std::string name_="Sample");
	protected:
		int GetWidth();
		int GetHeight();
		virtual void OnVisible();
		virtual void OnImgui();
		virtual void OnGLDraw();
		virtual void OnFrameBufferSize(SizeEvent e);
		virtual void Onkey(KeyEvent e) {};
		virtual void OnChar(CharEvent e) {};
		virtual void OnScroll(ScrollEvent e) {};
		virtual void OnMouseMove(MouseEvent e) {};
		virtual void OnMouseUpDown(MouseEvent e) {};
	};
	
}
