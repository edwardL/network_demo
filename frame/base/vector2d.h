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
	// ���캯��
	TVector2(){}
	TVector2(const T x, const T y):x(x),y(y) { }
	TVector2(const TVector2& v):x(v.x),y(v.y) { }
	TVector2(const T f[2]){ v[0] = f[0]; v[1] = f[1]; }

	///��ʼ������
	void Init(T a=0, T b=0);
	void Init(const TVector2& v);
	void Init(const T f[2]);

	// ʸ���Ļ�������
	// ʸ�����ȵ�ƽ��
	T MagSqr() const;
	// ʸ���ĳ���
	T Mag()const;
	// ����һ��ԭʸ���ĵ�λʸ����ԭʸ�����ı�
	const TVector2 Unit() const;

	// ������λ��
	const TVector2& Normalize();

	// �ж�һ��ʸ���Ƿ����0 ����ָ���ľ����ڣ�
	bool IsZero(float fTol = MATH_EPSILON) const;
	// �ж��Ƿ��������һ��ʸ��
	bool IsEqual(const TVector2& b, const T r = MATH_EPSILON) const;
	bool IsLongerThan(T len) const;
};

template<class T> inline T TVector2::Mag()const
{
	return (T)sqrtf(x*x + y*y);
}

// ʸ�����ȵ�ƽ��
template<class T> inline T TVector2<T>::MagSqr() const
{
	return x*x + y*y;
}

//  ����һ��ԭʸ���ĵ�λʸ����ԭʸ�����ı�
template<class T> inline const TVector2<T> TVector2<T>::Unit() const
{
	float fLen = this->Mag();
	return (*this) / fLen;
}

//������λ��
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

//�ж�һ��ʸ���Ƿ������(��ָ���ľ�����) ��fTolΪ�Ƚϵľ���
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
	//  ��
}

#endif