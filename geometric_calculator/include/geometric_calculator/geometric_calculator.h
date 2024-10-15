/*********************************************************************
 *
 * Description: Header file defines the classes for geometric shapes 
 *              (Point, Circle, Line, Rectangle) and declares utility functions
 *              used in the geometric calculator, including validation 
 *              and evaluation functions
 *
*********************************************************************/

#ifndef GEOMETRIC_CALCULATOR_H
#define GEOMETRIC_CALCULATOR_H

#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

using namespace std;

constexpr double PI = 3.14;

class Point {
 public:
  double x, y;
  Point(double xValue = 0, double yValue = 0);
  double getPointDistance(const Point& pt) const;
  void print() const;
};

class Circle {
 public:
  Point center;
  double radius;
  Circle();
  Circle(const Point& centerValue, double radiusValue);
  double getCircleArea() const;
  double getCircleCircumference() const;
  void print() const;
};

class Line {
 public:
  Point p1, p2;
  Line();
  Line(const Point& point1, const Point& point2);
  double getLineLength() const;
  void print() const;
};

class Rectangle {
 public:
  Point bottomLeft, topRight;
  Rectangle();
  Rectangle(const Point& blValue, const Point& trValue);
  double getRectArea() const;
  double getRectPerimeter() const;
  void print() const;
};

bool isValidNumber(const string& input);
double getValidatedRadiusInput();
bool isValidShapeName(const string& name);
double evaluateExpression(const string& expression,
                          const map<string, Point>& points,
                          const map<string, Circle>& circles,
                          const map<string, Rectangle>& rectangles,
                          const map<string, Line>& lines);

#endif  // GEOMETRIC_CALCULATOR_H