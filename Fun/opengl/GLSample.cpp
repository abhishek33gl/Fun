#include "GLSample.h"
namespace ak
{
	void GLSampleWindow::VisibleGLSample(int index)
	{
		active_sample_index = index;
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnVisible();
		}
		
	}
	GLSampleWindow::GLSampleWindow()
		:GLWindow(700,500,"Opengl Core 3.3")
	{

	}

	void GLSampleWindow::OnImgui()
	{
		static bool isFill = true;
		ImGui::Begin("Samples");
		if (ImGui::Button(isFill ? "Line" : "Fill"))
		{
			isFill = !isFill;
			glPolygonMode(GL_FRONT_AND_BACK, isFill ? GL_FILL : GL_LINE);
		}
		for (size_t i = 0; i < samples.size(); i++)
		{
			const auto sample = samples[i];
			if (ImGui::RadioButton(sample->name.c_str(), &active_sample_index, i)) {
				VisibleGLSample(active_sample_index);
			}
		}
		ImGui::End();
		//
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnImgui();
		}
	}

	void GLSampleWindow::OnGLDraw()
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnGLDraw();
		}
	}

	void GLSampleWindow::OnContextCreated()
	{
	}

	void GLSampleWindow::OnFrameBufferSize(SizeEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnFrameBufferSize(e);
		}
		glViewport(0, 0, GetWidth(), GetHeight());
		RePaint();
	}

	void GLSampleWindow::Onkey(KeyEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->Onkey(e);
		}
	}

	void GLSampleWindow::OnChar(CharEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnChar(e);
		}
	}

	void GLSampleWindow::OnScroll(ScrollEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnScroll(e);
		}
	}

	void GLSampleWindow::OnMouseMove(MouseEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnMouseMove(e);
		}
	}

	void GLSampleWindow::OnMouseUpDown(MouseEvent e)
	{
		if (active_sample_index != -1) {
			samples[active_sample_index]->OnMouseUpDown(e);
		}
	}

	void GLSampleWindow::AddGLSample(GLSample& sample)
	{
		sample.OnFrameBufferSize({GetWidth(),GetHeight()});
		samples.push_back(&sample);
		sample.window = this;

		active_sample_index = samples.size() - 1;
	}
	/*------------------GLSample----------------------*/
	GLSample::GLSample(std::string name_)
	{
		name = name_;
	}

	int GLSample::GetWidth()
	{
		return window->GetWidth();
	}

	int GLSample::GetHeight()
	{
		return window->GetHeight();
	}

	void GLSample::OnVisible()
	{
		
	}

	void GLSample::OnImgui()
	{
		ImGui::Begin(name.c_str());
		ImGui::Text("@@@@");
		ImGui::End();
	}

	void GLSample::OnGLDraw()
	{
	}

	void GLSample::OnFrameBufferSize(SizeEvent e)
	{
	}

	


}