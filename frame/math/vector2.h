#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <assert.h>
#include <ostream>

class Vector2
{
public:
	float x,y;

public:
	inline Vector2()
	{
	}

	inline Vector2(const float fx, const float fy)
		: x(fx),y(fy)
	{
	}

	inline explicit Vector2(const float scaler)
		: x(scaler),y(scaler)
	{
	}

	inline explicit Vector2(const float Cords[2])
		: x(Cords[0]),
		  y(Cords[1])
	{
	}

	inline explicit Vector2(const int Cords[2])
	{
		x = (float)Cords[0];
		y = (float)Cords[1];
	}

	inline void swap(Vector2& other)
	{
		std::swap(x,other.x);
		std::swap(y,other.y);
	}

	inline float operator[](const size_t i) const
	{
		assert(i < 2);
		return *(&x+i);
	}

	inline float* ptr()
	{
		return &x;
	}

	inline const float* ptr() const
	{
		return &x;
	}

	inline Vector2& operator = (const Vector2& rVector2)
	{
		x = rVector2.x;
		y = rVector2.y;
		return *this;
	}
	inline Vector2& operator = (const float scaler)
	{
		x = scaler;
		y = scaler;
		return *this;
	}

	inline bool operator == (const Vector2& rVector) const
	{
		return (x == rVector.x && y == rVector.y);
	}

	inline bool operator != (const Vector2& rVector) const
	{
		return (x != rVector.x || y != rVector.y);
	}

	inline Vector2 operator + (const Vector2& rVector) const
	{
		return Vector2(x + rVector.x , y + rVector.y);
	}

	inline Vector2 operator - (const Vector2& rVector) const
	{
		return Vector2(x - rVector.x , y - rVector.y);
	}

	inline Vector2 operator * (const float scaler) const
	{
		return Vector2(x * scaler , y * scaler);
	}

	//
	inline Vector2 operator * (const Vector2& rhs) const
	{
		return Vector2(x * rhs.x , y * rhs.y);
	}

	inline Vector2 operator / (const float scale) const
	{
		return Vector2(x / scale , y / scale);
	}

	inline const Vector2& operator + () const
	{
		return *this;
	}

	inline Vector2 operator - () const
	{
		return Vector2(-x , -y);
	}

	inline Vector2& operator += (const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	inline Vector2& operator += (const float scale)
	{
		x += scale;
		y += scale;
		return *this;
	}

	inline Vector2& operator -= (const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	inline Vector2& operator -= (const float scale)
	{
		x -= scale;
		y -= scale;
		return *this;
	}

	inline float length() const
	{
		return (float)sqrt(x*x + y*y);
	}

	inline float squaredLength() const
	{
		return x*x + y*y;
	}

	inline float distance(const Vector2& rhs) const
	{
		return (*this - rhs).length();
	}

	// 点乘， 两个向量 分量乘积的和。 返回标量
	// 用来计算两个向量之间的夹角
	inline float dotProduct(const Vector2& vec) const
	{
		return x * vec.x + y * vec.y;
	}

	// 叉乘， 返回一个向量，且该向量与 两个向量都垂直。
	//a×b=c,其中|c|=|a||b|·sinθ,c的方向遵守右手定则
	// 不会==
//	inline float crossProduct(const Vector2& vec)const
//	{
//		return x * vec.y - y * vec.x;
//	}

	inline float normalize()
	{
		float flength = length();
		if(flength > (float)0.0f)
		{
			x *= (1.0f / flength);
			y *= (1.0f / flength);
		}
		return flength;
	}

	inline Vector2 midPoint(const Vector2& vec)const
	{
		return Vector2((x+vec.x)*0.5f, (y+vec.y)*0.5f);
	}
	
	/// 输出到一个输出流中
	inline friend std::ostream& operator << (std::ostream& o, const Vector2& v)
	{
		o << "Vector2(" << v.x << "," << v.y << ")";
		return o;
	}

	static const Vector2 ZERO;

};




#endif