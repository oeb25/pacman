#include "vector2.h"

Vector2::Vector2() : x(0), y(0) {};
Vector2::Vector2(float x_) : x(x_), y(0) {};
Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {};

void Vector2::set(float x_, float y_) {
  this->x = x_;
  this->y = y_;
}

const Vector2 Vector2::operator+(const Vector2 &other) {
  Vector2 out(this->x + other.x, this->y + other.y);

  return out;
}

const Vector2 Vector2::operator-(const Vector2 &other) {
  Vector2 out(this->x - other.x, this->y - other.y);

  return out;
}

const Vector2 Vector2::operator*(const float &scale) {
  Vector2 out(this->x * scale, this->y * scale);

  return out;
}

Vector2 &Vector2::operator+=(const Vector2 &other) {
  this->x += other.x;
  this->y += other.y;

  return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other) {
  this->x -= other.x;
  this->y -= other.y;

  return *this;
}

Vector2 &Vector2::operator*=(const float &scale) {
  this->x *= scale;
  this->y *= scale;

  return *this;
}

const char* Vector2::toString() {
  std::stringstream out;

  out << "(" << this->x << ", " << this->y << ")";

  const std::string& tmp = out.str();
  return tmp.c_str();
}