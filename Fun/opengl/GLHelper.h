#pragma once
#include<string>
namespace ak
{
	 std::string GetResourcePath(std::string name);
	 class ImageLoader
	 {
	 public:
		 unsigned char* data = nullptr;
		 int w=0, h=0, channel=0;
		 ImageLoader();
		 ~ImageLoader();
		 unsigned char* LoadFromRes(std::string name);
		 void PrintInfo();
		 
	 protected:
		 void Free();
	 };
	 class GLTexture
	 {
	 public:
		 unsigned int id, w, h, format, wrap_s, wrap_t, filter_min, filter_max;
		 GLTexture();
		 ~GLTexture();
		 void GenerateFromFile(std::string name);
		 void Bind(unsigned int index = 0) const;
	 };
	 struct Vec2
	 {
		 float x, y;
		 Vec2();
		 Vec2(float x, float y);
		 Vec2(float xy);
		 void Set(float x, float y);
		 /// Negate this vector.
		 Vec2 operator -() const;
		 /// Add a vector to this vector.
		 void operator += (const Vec2& v);
		 /// Subtract a vector from this vector.
		 void operator -= (const Vec2& v);
		 Vec2 operator - (const Vec2& v);
		 Vec2 operator + (const Vec2& v);
		 /// Multiply this vector by a scalar.
		 void operator *= (float a);
		 void Print(const char* msg = "");
	 };
	 class Matrix33
	 {
	 public:
		 float arr[9] = { 0 };
		 Matrix33(float arr2[9]);
		 Matrix33();
		 void MakeIdentity();
		 static Matrix33 FromTranslation(float x, float y);
		 static Matrix33  FromRotation(float rad);
		 static Matrix33  FromScale(float sx, float sy);
		 static Matrix33  Multiply(Matrix33 matA, Matrix33 matB);
		 static Matrix33 CreateProjection2D(Vec2 size);
		 static Matrix33 TranslateAndScale(Vec2 point, Vec2 zoom);
		 void Print();
	 };

	 class Camera2D
	 {
		 Vec2 m_zoom{ 1.0f,1.0f };
		 Vec2 m_downPt, m_lastMouseMovePt, m_offset;
		 Vec2 m_size;
	 public:
		 void SetOffset(Vec2 offset);
		 void SetWH(Vec2 size);
		 void SetMouseDown(Vec2 v);
		 void SetMouseMove(Vec2 v, bool isDown);
		 void SetMouseWheel(int dir);
		 void ZoomIn();
		 void ZoomOut();
		 Vec2 WorldToScrn(Vec2 world);
		 Vec2 ScrnToWorld(Vec2 scrn);
		 Matrix33 GetProjectionMatrix33();
	 };
}
