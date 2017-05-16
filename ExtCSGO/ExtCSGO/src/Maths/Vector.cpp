#include "Maths\Vector.h"

namespace ExtCSGO
{
	vec3::vec3() :
		x(0.0f), y(0.0f), z(0.0f)
	{
	}

	vec3::vec3(const float & x, const float & y, const float & z) :
		x(x),
		y(y),
		z(z)
	{
	}

	vec3::vec3(const vec3 & v) :
		x(v.x),
		y(v.y),
		z(v.z)
	{
	}

	vec3::~vec3()
	{
	}

	vec3 & vec3::Add(const vec3 & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3 & vec3::Subtract(const vec3 & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec3 & vec3::Divide(const vec3 & v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	vec3 & vec3::Multiply(const vec3 & v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	vec3 & vec3::operator+=(const vec3 & v)
	{
		return Add(v);
	}

	vec3 vec3::operator+(const vec3 & v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 & vec3::operator-=(const vec3 & v) 
	{
		return Subtract(v);
	}

	vec3 vec3::operator-(const vec3 & v) const
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	vec3 & vec3::operator/=(const vec3 & v)
	{
		return Divide(v);
	}

	vec3 vec3::operator/(const vec3 & v) const
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}

	vec3 & vec3::operator*=(const vec3 & v) 
	{
		return Multiply(v);
	}

	vec3 vec3::operator*(const vec3 & v) const
	{
		return vec3(x * v.x, y * v.y, z * v.z);
	}

	vec3 vec3::operator*(const float & v) const
	{
		return vec3(x * v, y * v, z * v);
	}

	vec3 & vec3::operator=(const float & v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	bool vec3::operator==(const vec3 & v) const
	{
		return (
			x == v.x &&
			y == v.y &&
			z == v.z );
	}

	bool vec3::operator==(const float & v) const
	{
		return (
			x == v &&
			y == v &&
			z == v);
	}

	bool vec3::operator!=(const vec3 & v) const
	{
		return ( 
			x != v.x ||
			y != v.y ||
			z != v.z );
	}

	float vec3::Dot(const vec3 & v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	float vec3::LengthSqr() const
	{
		return (x * x + y * y + z * z);
	}

	std::ostream & operator<<(std::ostream & os, const vec3 & dt)
	{
		return os << "vec3(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
	}

	void GetArrayData(const char* Array, const int & dwOffset, void* buffer)
	{
		*(void**)buffer = (void*)*(void**)(Array + dwOffset);
	}
}