#pragma once

#include <string>
#include <sstream>

class Vector2 {
public:
  Vector2();
  Vector2(float x_);
  Vector2(float x_, float y_);

  float x, y;

  void set(float x_, float y_);

  const Vector2 operator+(const Vector2 &other);
  const Vector2 operator-(const Vector2 &other);
  const Vector2 operator*(const float &scale);

  Vector2 &operator+=(const Vector2 &other);
  Vector2 &operator-=(const Vector2 &other);
  Vector2 &operator*=(const float &scale);

  const char* toString();
};