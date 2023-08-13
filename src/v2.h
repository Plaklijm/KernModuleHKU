#pragma once

#include <SFML/Graphics.hpp>

class v2
{
public:
    float x, y;

public:
    v2();
    v2(float _x, float _y);
    v2(const v2& otherVec);
    ~v2();

    v2 Normalized() const;
    v2& Normalize();

    v2 Inversed() const;
    v2& Inverse();

    float Distance(const v2& OtherVec) const;
    float SqrDistance(const v2& OtherVec) const;

    float Dot(const v2& OtherVec) const;
    float Cross(const v2& OtherVec) const;

    float Magnitude() const;
    float SqrMagnitude() const;

    float Length(v2 vec) const;

#pragma region Static_Cast Conversion

    //Vector Addition
    //Vector +/+= Vector
    v2 operator+(const v2& otherVec);
    v2& operator+=(const v2& otherVec);
    //Vector + / += number
    v2 operator+(float Z);
    v2& operator+=(float Z);

    //Vector Subtraction
    //Vector -/-= Vector 
    v2 operator-(const v2& otherVec);
    v2& operator-=(const v2& otherVec);
    //Vector -/-= number
    v2 operator-(float Z);
    v2& operator-=(float Z);

    //Vector Multiplication
    v2 operator*(const v2& otherVec);
    //Vector */*= number
    v2 operator*(float Z);
    v2& operator*=(float Z);

    //Vector Division
    //Vector ///= number
    v2 operator/(float Z);
    v2& operator/=(float Z);

    //Vector converter
    operator sf::Vector2f() const;

    static v2 Zero() { return {0, 0}; }
    static v2 Left() { return {-7.5f, 0}; }
    static v2 Right() { return {7.5f, 0}; }

#pragma endregion
};


//Log Vector
std::ostream& operator<<(std::ostream& ostream, v2& vectors);

#pragma region Bool Operators
//Bool operators
bool operator<(const v2& leftVec, const v2& rightVec);
bool operator>(const v2& leftVec, const v2& rightVec);
bool operator==(const v2& leftVec, const v2& rightVec);
bool operator!=(const v2& leftVec, const v2& rightVec);
bool operator<=(const v2& leftVec, const v2& rightVec);
bool operator>=(const v2& leftVec, const v2& rightVec);
#pragma endregion
