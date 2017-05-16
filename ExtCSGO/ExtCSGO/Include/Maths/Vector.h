#pragma once
#include <iostream>
namespace ExtCSGO
{
	class vec3
	{
	public:
		vec3();
		vec3(const float & x, const float & y, const float & z);
		vec3(const vec3 & v);
		~vec3();

		vec3 & Add(const vec3 & v);
		vec3 & Subtract(const vec3 & v);
		vec3 & Divide(const vec3 & v);
		vec3 & Multiply(const vec3 & v);

		vec3 & operator+=(const vec3 & v);
		vec3 operator+(const vec3 & v) const;

		vec3 & operator-=(const vec3 & v);
		vec3 operator-(const vec3 & v) const;

		vec3 & operator/=(const vec3 & v);
		vec3 operator/(const vec3 & v) const;

		vec3 & operator*=(const vec3 & v);
		vec3 operator*(const vec3 & v) const;
		vec3 operator*(const float & v) const;

		vec3 & operator=(const float & v);

		bool operator==(const vec3 & v) const;
		bool operator==(const float & v) const;
		bool operator!=(const vec3 & v) const;

		float Dot(const vec3& v) const;

		float LengthSqr() const;

		friend std::ostream& operator <<(std::ostream& os, const vec3& dt);

		float x, y, z;
	};
	typedef float matrix3x4_t[3][4];

	void GetArrayData(const char* Array, const int & dwOffset, void* buffer);

}