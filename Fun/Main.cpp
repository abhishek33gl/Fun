#include"opengl/GLSample.h"
#include"opengl/GLShaderCompiler.h"
#include"opengl/GLHelper.h"
#include<GLFW/glfw3.h>
#include<fmt/core.h>
namespace ak {
	
	class RectSample :public GLSample
	{
		float color[4] = { 1,1,0,1 };

		GLShaderCompiler shaderCompiler;
		
		float vertices[12] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[6] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		unsigned int VBO, VAO, EBO;

	public:
		RectSample() :GLSample("RectSample") 
		{
			/*shaderCompiler.CreateFromFile("shaders\\tri_sam_.vert", 
				"shaders\\tri_sam_.frag");*/
			shaderCompiler.CreateFromFile(
				GetResourcePath("shaders\\tri_sam_").c_str()
			);

			//
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

		}
	protected:
		virtual void OnVisible() override
		{

		}
		virtual void OnImgui() override
		{
			ImGui::Begin(name.c_str());
			ImGui::Text("triangle");
			ImGui::SliderFloat4("color", color, 0, 1);
			ImGui::End();
		}
		virtual void OnGLDraw() override
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			shaderCompiler.Use();
			shaderCompiler.setVec4("u_color", color[0], color[1], color[2], color[3]);
			glBindVertexArray(VAO); 
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		virtual void OnFrameBufferSize(SizeEvent e) override
		{
		}
		virtual void Onkey(KeyEvent e) override
		{

		}
		virtual void OnChar(CharEvent e)override
		{

		}
		virtual void OnScroll(ScrollEvent e)override
		{

		}
		virtual void OnMouseMove(MouseEvent e)override
		{
			
		}

	};
	class VertexPlusColorAttribSample :public GLSample
	{

		GLShaderCompiler shaderCompiler;

		float vertices[18] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};
		unsigned int indices[3] = {  // note that we start from 0!
			0, 1, 2
		};
		unsigned int VBO, VAO, EBO;

	public:
		VertexPlusColorAttribSample() :GLSample("VertexPlusColorAttribSample")
		{
			
			shaderCompiler.CreateFromFile(
				GetResourcePath("shaders\\VertexPlusColorAttribSample").c_str()
			);

			//
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			/*-----------buffer--------------*/
			//pos+color
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			/*--------pointer----------*/
			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

		}
	protected:
		virtual void OnVisible() override
		{

		}
		virtual void OnImgui() override
		{
			ImGui::Begin(name.c_str());
			ImGui::End();
		}
		virtual void OnGLDraw() override
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			shaderCompiler.Use();
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		}
		virtual void OnFrameBufferSize(SizeEvent e) override
		{
		}
		virtual void Onkey(KeyEvent e) override
		{

		}
		virtual void OnChar(CharEvent e)override
		{

		}
		virtual void OnScroll(ScrollEvent e)override
		{

		}
		virtual void OnMouseMove(MouseEvent e)override
		{

		}

	};
	class BasicSample :public GLSample
	{

		GLShaderCompiler shaderCompiler;

		
		unsigned int VBO, VAO, EBO;

	public:
		BasicSample() :GLSample("BasicSample")
		{
			float vertices[] = {
				0.5f,  0.5f, 0.0f,  
				0.5f, -0.5f, 0.0f, 
			   -0.5f, -0.5f, 0.0f,  
			   -0.5f,  0.5f, 0.0f   
			};
			unsigned int indices[] = { 
				0, 1, 3,  
				1, 2, 3  
			};
			shaderCompiler.CreateFromFile(
				GetResourcePath("shaders\\tri_sam_").c_str()
			);

			//
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			//VAO
			glBindVertexArray(VAO);
			/*-------------------data---------------*/
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			/*------------pointer-----------------*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			/*----unbind--VAO-------*/
			glBindVertexArray(0);

		}
	protected:
		virtual void OnVisible() override
		{

		}
		virtual void OnImgui() override
		{
			ImGui::Begin(name.c_str());
			
			ImGui::End();
		}
		virtual void OnGLDraw() override
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			shaderCompiler.Use();                                                                                                                                                          
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		virtual void OnFrameBufferSize(SizeEvent e) override
		{
		}
		virtual void Onkey(KeyEvent e) override
		{

		}
		virtual void OnChar(CharEvent e)override
		{

		}
		virtual void OnScroll(ScrollEvent e)override
		{

		}
		virtual void OnMouseMove(MouseEvent e)override
		{

		}

	};
	class TextureSample :public GLSample
	{

		GLShaderCompiler shaderCompiler;
		unsigned int VBO, VAO, EBO;
		GLTexture texDice,texContainer;
		bool isDice = false;
	public:
		TextureSample() :GLSample("TextureSample")
		{
			float vertices[] = {
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
				 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
			};
			unsigned int indices[] = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};
			shaderCompiler.CreateFromFile(
				GetResourcePath("shaders\\TextureSample").c_str()
			);

			//
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			//VAO
			glBindVertexArray(VAO);
			/*-------------------data---------------*/
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			/*------------pointer-----------------*/
			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			/*----unbind--VAO-------*/
			glBindVertexArray(0);

			/*-----------texture----------------*/
			texDice.GenerateFromFile("dice.png");
			texContainer.GenerateFromFile("container.jpg");

		}
	protected:
		virtual void OnVisible() override
		{

		}
		virtual void OnImgui() override
		{
			ImGui::Begin(name.c_str());
			if (ImGui::Button((!isDice?"dice":"container")))
			{
				isDice = !isDice;
			}
			ImGui::End();
		}
		virtual void OnGLDraw() override
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			shaderCompiler.Use();
			// bind Texture
			if (isDice)
				texDice.Bind();
			else
				texContainer.Bind();

			glBindVertexArray(VAO);

			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		virtual void OnFrameBufferSize(SizeEvent e) override
		{
		}
		virtual void Onkey(KeyEvent e) override
		{

		}
		virtual void OnChar(CharEvent e)override
		{

		}
		virtual void OnScroll(ScrollEvent e)override
		{

		}
		virtual void OnMouseMove(MouseEvent e)override
		{

		}

	};
	class Camera2DSample :public GLSample
	{

		GLShaderCompiler shaderCompiler;


		unsigned int VBO, VAO, EBO;
		Camera2D camera;
		bool m_isMouseDown = false;
	public:
		Camera2DSample() :GLSample("Camera2DSample")
		{
			float vertices[] = {
				100.0f,  100.0f, 0.0f,
				100.0f, -100.0f, 0.0f,
			   -100.0f, -100.0f, 0.0f,
			   -100.0f,  100.0f, 0.0f
			};
			unsigned int indices[] = {
				0, 1, 3,
				1, 2, 3
			};
			shaderCompiler.CreateFromFile(
				GetResourcePath("shaders\\Camera2DSample").c_str()
			);

			//
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			//VAO
			glBindVertexArray(VAO);
			/*-------------------data---------------*/
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			/*------------pointer-----------------*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			/*----unbind--VAO-------*/
			glBindVertexArray(0);

		}
	protected:
		virtual void OnVisible() override
		{

		}
		virtual void OnImgui() override
		{
			ImGui::Begin(name.c_str());

			ImGui::End();
		}
		virtual void OnGLDraw() override
		{
			//camera.SetWH(Vec2((float)GetWidth(), (float)GetHeight()));
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			shaderCompiler.Use();
			{
				Matrix33 mat = Matrix33::CreateProjection2D(Vec2(
					GetWidth(), GetHeight()
				));
				shaderCompiler.setMat3("proj", camera.GetProjectionMatrix33().arr);
			}
			glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		virtual void OnFrameBufferSize(SizeEvent e) override
		{
			camera.SetWH(Vec2((float)e.w, (float)e.h));
		}
		virtual void Onkey(KeyEvent e) override
		{
			
		}
		virtual void OnChar(CharEvent e)override
		{

		}
		virtual void OnScroll(ScrollEvent e)override
		{
			camera.SetMouseWheel(e.yoffset);
		}
		virtual void OnMouseMove(MouseEvent e)override
		{
			camera.SetMouseMove(Vec2(e.x, e.y), m_isMouseDown);
		}
		virtual void OnMouseUpDown(MouseEvent e) 
		{
			if (e.action == GLFW_PRESS)
			{
				camera.SetMouseDown(Vec2(e.x, e.y));
				m_isMouseDown = true;
			}
			else
				m_isMouseDown = false;


		};

	};
}
using namespace ak;
int main()
{
	
	
	glfw::Init();
	glfw::InitGLCore();

	GLSampleWindow window;
	//samples
	window.AddGLSample(*(new RectSample()));
	window.AddGLSample(*(new VertexPlusColorAttribSample()));
	window.AddGLSample(*(new TextureSample()));
	window.AddGLSample(*(new Camera2DSample()));
	//loop
	while (!window.IsWindowShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		window.RePaint();
		glfw::WaitEvents();
		//glfw::PollEvents();
	}
	glfw::Terminate();
}
