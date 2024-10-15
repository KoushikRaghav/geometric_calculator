/*********************************************************************
 *
 * Description: Implements the utility functions and methods for geometric 
 *              shapes, including calculations for area, perimeter, length, distance, 
 *              and expression evaluation for different shapes
 *
*********************************************************************/


#include "geometric_calculator/geometric_calculator.h"

// Point class methods
Point::Point(double xValue, double yValue) : x(xValue), y(yValue) {}

double Point::getPointDistance(const Point& pt) const {
  return sqrt(pow(pt.x - x, 2) + pow(pt.y - y, 2));
}

void Point::print() const { cout << "(" << x << ", " << y << ")"; }

// Circle class methods
Circle::Circle() : center(Point()), radius(0) {}

Circle::Circle(const Point& centerValue, double radiusValue)
    : center(centerValue), radius(radiusValue) {}

double Circle::getCircleArea() const { return PI * radius * radius; }

double Circle::getCircleCircumference() const { return 2 * PI * radius; }

void Circle::print() const {
  cout << "Circle with center ";
  center.print();
  cout << " and radius " << radius << endl;
}

// Line class methods
Line::Line() : p1(Point(0, 0)), p2(Point(0, 0)) {}

Line::Line(const Point& point1, const Point& point2) : p1(point1), p2(point2) {}

double Line::getLineLength() const { return p1.getPointDistance(p2); }

void Line::print() const {
  cout << "Line from ";
  p1.print();
  cout << " to ";
  p2.print();
  cout << " with length: " << getLineLength() << endl;
}

// Rectangle class methods
Rectangle::Rectangle() : bottomLeft(Point(0, 0)), topRight(Point(0, 0)) {}

Rectangle::Rectangle(const Point& blValue, const Point& trValue)
    : bottomLeft(blValue), topRight(trValue) {}

double Rectangle::getRectArea() const {
  double width = topRight.x - bottomLeft.x;
  double height = topRight.y - bottomLeft.y;
  return width * height;
}

double Rectangle::getRectPerimeter() const {
  double width = topRight.x - bottomLeft.x;
  double height = topRight.y - bottomLeft.y;
  return 2 * (width + height);
}

void Rectangle::print() const {
  cout << "Rectangle with corners ";
  bottomLeft.print();
  cout << " and ";
  topRight.print();
  cout << ", Area: " << getRectArea() << ", Perimeter: " << getRectPerimeter()
       << endl;
}

// Utility functions
bool isValidNumber(const string& input) {
  regex float_regex("^-?\\d*\\.?\\d+$");
  return regex_match(input, float_regex);
}

double getValidatedRadiusInput() {
  string input;
  while (true) {
    getline(cin, input);
    if (isValidNumber(input)) {
      return stod(input);
    } else {
      cout << "Invalid input. Please enter a valid number for radius ";
    }
  }
}

bool isValidShapeName(const string& name) {
  regex regexObj("^[a-zA-Z0-9_]+$");
  return regex_match(name, regexObj);
}

double evaluateExpression(const string& expression,
                          const map<string, Point>& points,
                          const map<string, Circle>& circles,
                          const map<string, Rectangle>& rectangles,
                          const map<string, Line>& lines) {
  istringstream iss(expression);
  string query;
  double result = 0;
  char operation = '+';

  while (iss >> query) {
    double value = 0;

    if (query == "length") {
      string shapeName;
      iss >> shapeName;

      // Check for line length
      if (lines.find(shapeName) != lines.end()) {
        value = lines.at(shapeName).getLineLength();
      } else if (circles.find(shapeName) != circles.end()) {
        // Check for circle length (circumference)
        value = circles.at(shapeName).getCircleCircumference();
      } else if (rectangles.find(shapeName) != rectangles.end()) {
        // Check for rectangle length (perimeter)
        value = rectangles.at(shapeName).getRectPerimeter();
      } else if (points.find(shapeName) != points.end()) {
        // Handle point error
        throw runtime_error("\033[31mError: Cannot find length of a point: " +
                            shapeName + "\033[0m");
      } else {
        throw runtime_error("\033[31mError: Shape " + shapeName +
                            " not found for length\033[0m");
      }
    } else if (query == "perimeter") {
      string shapeName;
      iss >> shapeName;

      if (rectangles.find(shapeName) != rectangles.end()) {
        value = rectangles.at(shapeName).getRectPerimeter();
      } else {
        throw runtime_error("\033[31mError: Shape " + shapeName +
                            " not found for perimeter\033[0m");
      }
    } else if (query == "area") {
      string shapeName;
      iss >> shapeName;

      if (rectangles.find(shapeName) != rectangles.end()) {
        value = rectangles.at(shapeName).getRectArea();
      } else if (circles.find(shapeName) != circles.end()) {
        value = circles.at(shapeName).getCircleArea();
      } else {
        throw runtime_error("\033[31mError: Shape " + shapeName +
                            " not found for area\033[0m");
      }
    } else if (query == "circumference") {
      string shapeName;
      iss >> shapeName;
      if (circles.find(shapeName) != circles.end()) {
        value = circles.at(shapeName).getCircleCircumference();
      } else {
        throw runtime_error("\033[31mError: Shape " + shapeName +
                            " not found for circumference\033[0m");
      }
    } else if (query == "distance") {
      string shape1Name, shape2Name;
      iss >> shape1Name >> shape2Name;

      // Distance between two points
      if (points.find(shape1Name) != points.end() &&
          points.find(shape2Name) != points.end()) {
        value = points.at(shape1Name).getPointDistance(points.at(shape2Name));
      } else if (points.find(shape1Name) != points.end() &&
                 circles.find(shape2Name) != circles.end()) {
        // Distance from a point to a circle
        value = points.at(shape1Name)
                    .getPointDistance(circles.at(shape2Name).center);
      } else if (circles.find(shape1Name) != circles.end() &&
                 points.find(shape2Name) != points.end()) {
        // Distance from a circle to a point
        value = points.at(shape2Name)
                    .getPointDistance(circles.at(shape1Name).center);
      } else if (circles.find(shape1Name) != circles.end() &&
                 circles.find(shape2Name) != circles.end()) {
        // Distance between two circles (between their centers)
        value = circles.at(shape1Name)
                    .center.getPointDistance(circles.at(shape2Name).center);
      } else {
        throw runtime_error(
            "\033[31mError: One or both shapes not found for distance\033[0m");
      }
    } else if (query == "+") {  // Handle arithmetic operators
      operation = '+';
      continue;
    } else if (query == "-") {
      operation = '-';
      continue;
    } else if (query == "*") {
      operation = '*';
      continue;
    } else if (query == "/") {
      operation = '/';
      continue;
    } else {
      throw runtime_error("\033[31mError: Unknown command or operator\033[0m");
    }

    // Perform the operation with the previous result
    if (operation == '+') {
      result += value;
    } else if (operation == '-') {
      result -= value;
    } else if (operation == '*') {
      result *= value;
    } else if (operation == '/') {
      if (value == 0) {
        throw runtime_error("\033[31mError: Division by zero\033[0m");
      }
      result /= value;
    } else {
      result = value;
    }
  }
  return result;
}
