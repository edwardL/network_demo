#ifndef VECTOR2D_H
#define VECTOR2D_H

#include<math.h>

#define MATH_EPSILON			1.0e-5f

template<class T> struct TVector2
{
	union
	{
		struct
		{
			T x,y;
		};
		T v[2];
	};
	//----------------------------
	// 构造函数
	TVector2(){}
	TVector2(const T x, const T y):x(x),y(y) { }
	TVector2(const TVector2& v):x(v.x),y(v.y) { }
	TVector2(const T f[2]){ v[0] = f[0]; v[1] = f[1]; }

	///初始化函数
	void Init(T a=0, T b=0);
	void Init(const TVector2& v);
	void Init(const T f[2]);

	// 矢量的基本运算
	// 矢量长度的平方
	T MagSqr() const;
	// 矢量的长度
	T Mag()const;
	// 返回一个原矢量的单位矢量，原矢量不改变
	const TVector2 Unit() const;

	// 将自身单位化
	const TVector2& Normalize();

	// 判断一个矢量是否等于0 （在指定的精度内）
	bool IsZero(float fTol = MATH_EPSILON) const;
	// 判断是否等于另外一个矢量
	bool IsEqual(const TVector2& b, const T r = MATH_EPSILON) const;
	bool IsLongerThan(T len) const;
};

template<class T> inline T TVector2::Mag()const
{
	return (T)sqrtf(x*x + y*y);
}

// 矢量长度的平方
template<class T> inline T TVector2<T>::MagSqr() const
{
	return x*x + y*y;
}

//  返回一个原矢量的单位矢量，原矢量不改变
template<class T> inline const TVector2<T> TVector2<T>::Unit() const
{
	float fLen = this->Mag();
	return (*this) / fLen;
}

//将自身单位化
template<class T> inline const TVector2<T>& TVector2<T>::Normalize()
{
	float flen = this->Mag();
	(*this) /= flen;
	return *this;
}

inline bool gIsZero(float a, float fTol = MATH_EPSILON)
{
	return (a <= 0.0f) ? (a >= -fTol) : (a <= fTol);
}

//判断一个矢量是否等于零(在指定的精度内) ，fTol为比较的精度
template<class T> inline bool TVector2<T>::IsZero(float fTol) const
{
	if (gIsZero(x,fTol) && gIsZero(y,fTol))
		return true;
	else
		return false;
}

template<class T> inline bool TVector2<T>::IsLongerThan(T len) const
{
	return (x*x + y*y) > (len * len);
}

template<class T> inline bool TVector2<T>::IsEqual(const TVector2<T>& b, const T r /* = MATH_EPSILON */)
{
	//  略
}

#endif