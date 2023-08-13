#include "v2.h"

//initializers
v2::v2()
{
	x = 0;
	y = 0;
}
v2::v2(float _x, float _y)
{
	x = _x;
	y = _y;
}
v2::v2(const v2& otherVec)
{
	x = otherVec.x;
	y = otherVec.y;
}
v2::~v2() = default;

v2 v2::Normalized() const
{
	if (Length(v2(x, y)) != 0.0)
	{
		const float magnitude = Magnitude();
		return {x / magnitude, y / magnitude};
	}
	return Zero();
}

v2& v2::Normalize()
{
	if (Length(v2(x, y)) != 0)
	{
		const float magnitude = Magnitude();
		this->x /= magnitude;
		this->y /= magnitude;
		return *this;
	}
	return *this;
}

v2 v2::Inversed() const
{
	return {x * -1, y * -1};
}

v2& v2::Inverse()
{
	this->x *= -1;
	this->y *= -1;

	return *this;
}

float v2::Distance(const v2& OtherVec) const
{
	return sqrt(pow(OtherVec.x - x, 2) + pow(OtherVec.y - y, 2));
}

float v2::SqrDistance(const v2& OtherVec) const
{
	return pow(OtherVec.x - x, 2) + pow(OtherVec.y - y, 2);
}

float v2::Dot(const v2& OtherVec) const
{
	return x * OtherVec.x + y * OtherVec.y;
}

float v2::Cross(const v2& OtherVec) const
{
	return x * OtherVec.x - y * OtherVec.y;
}

float v2::Magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float v2::SqrMagnitude() const
{
	return pow(x, 2) + pow(y, 2);
}

float v2::Length(v2 vec) const
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

//Vector Addition
//Vector + / += Vector
v2 v2::operator+(const v2& otherVec)
{
	x += otherVec.x;
	y += otherVec.y;
	return *this;
}
v2& v2::operator+=(const v2& otherVec)
{
	x += otherVec.x;
	y += otherVec.y;
	return *this;
}
//Vector + / += number
v2 v2::operator+(float Z)
{
	x += Z;
	y += Z;
	return *this;
}
v2& v2::operator+=(float Z)
{
	x += Z;
	y += Z;
	return *this;
}

//Vector Subtraction
//Vector - / -= Vector
v2 v2::operator-(const v2& otherVec)
{
	x -= otherVec.x;
	y -= otherVec.y;
	return *this;
}
v2& v2::operator-=(const v2& otherVec)
{
	x -= otherVec.x;
	y -= otherVec.y;
	return *this;
}
//Vector - / -= number
v2 v2::operator-(float Z)
{
	x -= Z;
	y -= Z;
	return *this;
}
v2& v2::operator-=(float Z)
{
	x -= Z;
	y -= Z;
	return *this;
}

v2 v2::operator*(const v2& otherVec)
{
	x *= otherVec.x;
	y *= otherVec.y;
	return *this;
}

//Vector Multiplication
v2 v2::operator*(float Z)
{
	x *= Z;
	y *= Z;
	return *this;
}

v2& v2::operator*=(float Z)
{
	x *= Z;
	y *= Z;
	return *this;
}

//Vector Division
v2 v2::operator/(float Z)
{
	x /= Z;
	y /= Z;
	return *this;
}
v2& v2::operator/=(float Z)
{
	x /= Z;
	y /= Z;
	return *this;
}

v2::operator sf::Vector2f() const
{
	return {x, y};
}

//Log Vector
std::ostream& operator<<(std::ostream& ostream, v2& vector)
{
	return ostream << "(" << vector.x << "," << vector.y << ")";
}

//Bool operators
bool operator<(const v2& leftVec, const v2& rightVec)
{
	return ((leftVec.x < rightVec.x) || (leftVec.x == rightVec.x && leftVec.y < rightVec.y));
}
bool operator>(const v2& leftVec, const v2& rightVec)
{
	return ((leftVec.x > rightVec.x) || (leftVec.x == rightVec.x && leftVec.y > rightVec.y));
}
bool operator==(const v2& leftVec, const v2& rightVec)
{
	return (leftVec.x == rightVec.x && leftVec.y == rightVec.y);
}
bool operator!=(const v2& leftVec, const v2& rightVec)
{
	return !operator == (leftVec, rightVec);
}
bool operator <= (const v2& leftVec, const v2& rightVec)
{
	return !operator < (leftVec, rightVec);
}
bool operator >= (const v2& leftVec, const v2& rightVec)
{
	return !operator > (leftVec, rightVec);
}