#include "GLHelper.h"
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include<fmt/core.h>
#include"../glad/glad.h"

namespace ak
{
	
	std::string GetResourcePath(std::string name)
	{
		return std::string("res\\" + name);
	}

	ImageLoader::ImageLoader()
	{
	}

	ImageLoader::~ImageLoader()
	{
		Free();
	}

	unsigned char* ImageLoader::LoadFromRes(std::string name)
	{
		static bool first = false;
		if (!first)
		{
			first = true;
			stbi_set_flip_vertically_on_load(true);
		}

		Free();
		data = stbi_load(
			GetResourcePath("images\\" + name).c_str(),
			&w,
			&h, 
			&channel,
			0
		);
		if (!data)
		{
			std::cout << "could't load data\n";
		}
		return data;
	}


	void ImageLoader::PrintInfo()
	{
		fmt::print("w {0} h {1} channel {2}\n", w, h, channel);
	}

	void ImageLoader::Free()
	{
		if (data)
		{
			stbi_image_free(data);
			fmt::print("ImageLoader::free\n");
		}
	}

	/*--------GLTextureRGBA------------------------------*/
	GLTexture::GLTexture()
		:w(0), h(0), format(GL_RGBA), wrap_s(GL_REPEAT),
		wrap_t(GL_REPEAT), filter_min(GL_LINEAR),
		filter_max(GL_LINEAR), id(0)
	{
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &this->id);
		//fmt::print("GLTexture::free id {0}", id);
	}

	void GLTexture::GenerateFromFile(std::string name)
	{
		
		ImageLoader img;
		img.LoadFromRes(name);
		img.PrintInfo();
		this->w = img.w;
		this->h = img.h;
		if (img.channel == 3)
			this->format = GL_RGB;
		else
			this->format = GL_RGBA;
		/*-----------oopengl---------*/
		glGenTextures(1, &this->id);
		// bind
		glBindTexture(GL_TEXTURE_2D, this->id);
		glTexImage2D(GL_TEXTURE_2D, 0, this->format,w , h, 0, this->format, GL_UNSIGNED_BYTE,img.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// set Texture wrap and filter modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
		// unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void GLTexture::Bind(unsigned int index) const
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, this->id);

	}

	/*-----------------Vec2---------------------------*/

	 Vec2::Vec2() :x(0), y(0) {}

	 Vec2::Vec2(float x, float y) : x(x), y(y) {}

	 Vec2::Vec2(float xy) : x(xy), y(xy) {}

	 void Vec2::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vec2 Vec2::operator-() const { Vec2 v; v.Set(-x, -y); return v; }
	void Vec2::operator += (const Vec2& v)
	{
		x += v.x; y += v.y;
	}

	void Vec2::operator -= (const Vec2& v)
	{
		x -= v.x; y -= v.y;
	}
	Vec2 Vec2::operator - (const Vec2& v)
	{
		return Vec2(x - v.x, y - v.y);
	}
	Vec2 Vec2::operator + (const Vec2& v)
	{
		return Vec2(x + v.x, y + v.y);
	}
	void Vec2::operator *= (float a)
	{
		x *= a; y *= a;
	}
	 void Vec2::Print(const char* msg)
	{
		fmt::print("{0} x {1} y {2} \n", msg, x, y);
	}
	/*--------------------Matrix33--------------------*/

	 Matrix33::Matrix33(float arr2[9])
	{
		arr[0] = arr2[0]; arr[1] = arr2[1]; arr[2] = arr2[2];
		arr[3] = arr2[3]; arr[4] = arr2[4]; arr[5] = arr2[5];
		arr[6] = arr2[6]; arr[7] = arr2[7]; arr[8] = arr2[8];
	}

	 Matrix33::Matrix33()
	{
		//00 01 02 
		//10 11 12 
		//20 21 22 
		MakeIdentity();
	}

	 void Matrix33::MakeIdentity()
	{
		arr[0] = 1.0f; arr[1] = 0.0f; arr[2] = 0.0f;
		arr[3] = 0.0f; arr[4] = 1.0f; arr[5] = 0.0f;
		arr[6] = 0.0f; arr[7] = 0.0f; arr[8] = 1.0f;
	}

	 Matrix33 Matrix33::FromTranslation(float x, float y)
	{
		float arr[9] = { 0 };
		arr[0] = 1;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		arr[4] = 1;
		arr[5] = 0;
		arr[6] = x;
		arr[7] = y;
		arr[8] = 1;
		return Matrix33(arr);
	}

	 Matrix33 Matrix33::FromRotation(float rad)
	{
		float arr[9] = { 0 };
		float s = sinf(rad),
			c = cosf(rad);
		arr[0] = c;
		arr[1] = s;
		arr[2] = 0;
		arr[3] = -s;
		arr[4] = c;
		arr[5] = 0;
		arr[6] = 0;
		arr[7] = 0;
		arr[8] = 1;
		return Matrix33(arr);

	}

	 Matrix33 Matrix33::FromScale(float sx, float sy)
	{
		float arr[9] = { 0 };
		arr[0] = sx;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		arr[4] = sy;
		arr[5] = 0;
		arr[6] = 0;
		arr[7] = 0;
		arr[8] = 1;
		return Matrix33(arr);

	}

	 Matrix33 Matrix33::Multiply(Matrix33 matA, Matrix33 matB)
	{
		float arr[9] = { 0 };
		float* a = matA.arr;
		float* b = matB.arr;
		float a00 = a[0],
			a01 = a[1],
			a02 = a[2];
		float a10 = a[3],
			a11 = a[4],
			a12 = a[5];
		float a20 = a[6],
			a21 = a[7],
			a22 = a[8];
		float b00 = b[0],
			b01 = b[1],
			b02 = b[2];
		float b10 = b[3],
			b11 = b[4],
			b12 = b[5];
		float b20 = b[6],
			b21 = b[7],
			b22 = b[8];
		arr[0] = b00 * a00 + b01 * a10 + b02 * a20;
		arr[1] = b00 * a01 + b01 * a11 + b02 * a21;
		arr[2] = b00 * a02 + b01 * a12 + b02 * a22;
		arr[3] = b10 * a00 + b11 * a10 + b12 * a20;
		arr[4] = b10 * a01 + b11 * a11 + b12 * a21;
		arr[5] = b10 * a02 + b11 * a12 + b12 * a22;
		arr[6] = b20 * a00 + b21 * a10 + b22 * a20;
		arr[7] = b20 * a01 + b21 * a11 + b22 * a21;
		arr[8] = b20 * a02 + b21 * a12 + b22 * a22;
		return Matrix33(arr);
	}

	 Matrix33 Matrix33::CreateProjection2D(Vec2 size)
	{
		float arr[9] =
		{
			2.0 / size.x,0.0f,0.0f,
			0.0f,2.0f / size.y,0.0f,
			0.0f,0.0f,1.0f
		};
		return Matrix33(arr);
	}

	 Matrix33 Matrix33::TranslateAndScale(Vec2 point, Vec2 zoom)
	{
		return  Matrix33::Multiply(Matrix33::FromScale(zoom.x, zoom.y), Matrix33::FromTranslation(point.x, point.y));
	}

	void Matrix33::Print()
	{
		//fmt::print("arr {}\n", arr);
		fmt::print("{0} {1} {2}\n", arr[0], arr[1], arr[2]);
		fmt::print("{0} {1} {2}\n", arr[3], arr[4], arr[5]);
		fmt::print("{0} {1} {2}\n", arr[6], arr[7], arr[8]);
	}

	/*------------------Camera2D-----------------------*/
	 void Camera2D::SetOffset(Vec2 offset)
	{
		m_offset = offset;
	}

	 void Camera2D::SetWH(Vec2 size)
	{
		m_size = size;
	}

	 void Camera2D::SetMouseDown(Vec2 v)
	{
		m_downPt = Vec2(v.x - (m_size.x / 2.0f), -(v.y - (m_size.y / 2.0f)));
	}

	 void Camera2D::SetMouseMove(Vec2 v, bool isDown)
	{
		Vec2 movPt = Vec2(v.x - (m_size.x / 2.0f), -(v.y - (m_size.y / 2.0f)));
		m_lastMouseMovePt = movPt;

		if (isDown)
		{
			m_offset.x += (movPt.x - m_downPt.x) / m_zoom.x;
			m_offset.y += (movPt.y - m_downPt.y) / m_zoom.y;
			m_downPt = movPt;
		}

	}

	 void Camera2D::SetMouseWheel(int dir)
	{
		Vec2 mouseWorld_beforeZoom = ScrnToWorld(m_lastMouseMovePt);

		if (dir < 0)
		{
			m_zoom *= 1.02f;
		}
		else
		{
			m_zoom *= 0.979f;
		}
		Vec2 mouseWorld_afterZoom = ScrnToWorld(m_lastMouseMovePt);
		{
			m_offset.x -= -1.0f * (mouseWorld_afterZoom.x - mouseWorld_beforeZoom.x);
			m_offset.y -= -1.0f * (mouseWorld_afterZoom.y - mouseWorld_beforeZoom.y);
		}
	}

	 void Camera2D::ZoomIn()
	{
		SetMouseWheel(+1);
	}

	 void Camera2D::ZoomOut()
	{
		SetMouseWheel(-1);

	}

	 Vec2 Camera2D::WorldToScrn(Vec2 world)
	{
		return Vec2((world.x - m_offset.x) * m_zoom.x, (world.y - m_offset.y) * m_zoom.y);
	}

	 Vec2 Camera2D::ScrnToWorld(Vec2 scrn)
	{
		return Vec2((scrn.x / m_zoom.x + m_offset.x), (scrn.y / m_zoom.x + m_offset.y));
	}

	 Matrix33 Camera2D::GetProjectionMatrix33()
	{
		return Matrix33::Multiply(Matrix33::CreateProjection2D(m_size),
			Matrix33::TranslateAndScale(m_offset, Vec2(m_zoom)));
	}


}