/*********************************************************************
 *
 * Description: Handles user input commands for creating shapes, performing calculations
 *              (area, perimeter, distance, length), and listing created shapes using
 *              a command-line interface
 *
*********************************************************************/

#include "geometric_calculator/geometric_calculator.h"
#include <ros/ros.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "geometric_calculator_node");
  ros::NodeHandle nh;
  ROS_WARN("Initialized geometric_calculator node\n");

  map<string, Point> points;
  map<string, Circle> circles;
  map<string, Line> lines;
  map<string, Rectangle> rectangles;
  set<string> shapeNames;
  string command;

  cout << "Geometric Calculator (type 'exit' to quit)\n";

  while (ros::ok()) {
    cout << "\033[34m  > Enter command : \033[0m";
    getline(cin, command);

    if (command.empty()) {
      cout << "\033[31mError: No command entered. Please enter a command\033[0m"
           << endl;
      continue;
    }

    if (command == "exit") {
      cout << "\033[35mClosing the calculator gracefully :)\033[0m\n";
      break;
    }

    istringstream strStream(command);
    string query;
    strStream >> query;

    if (query == "create") {
      string shapeType, shapeName;
      strStream >> shapeType >> shapeName;

      if (shapeType.empty() || shapeName.empty() ||
          !isValidShapeName(shapeName)) {
        cout << "\033[31mError: Shape type or name not provided or "
                "invalid\033[0m"
             << endl;
        continue;
      }

      if (shapeType == "point") {
        if (shapeNames.find(shapeName) != shapeNames.end()) {
          cout << "\033[31mError: Shape with name '" << shapeName
               << "' already exists\033[0m" << endl;
          continue;
        }

        double x, y;
        cout << "Enter x and y coordinates for " << shapeName
             << " (separated by space): ";

        string coordinates;
        getline(cin, coordinates);

        istringstream coordStream(coordinates);
        string xStr, yStr;

        if (coordStream >> xStr >> yStr && isValidNumber(xStr) &&
            isValidNumber(yStr)) {
          x = stod(xStr);
          y = stod(yStr);

          // Create a point and store it in the map and set
          points[shapeName] = Point(x, y);
          shapeNames.insert(shapeName);
          cout << "Created Point " << shapeName << " at (" << x << ", " << y
               << ")\n";
        } else {
          cout << "Invalid input, please enter two valid numbers\n";
        }
      } else if (shapeType == "circle") {
        if (shapeNames.find(shapeName) != shapeNames.end()) {
          cout << "\033[31mError: Shape with name '" << shapeName
               << "' already exists\033[0m" << endl;
          continue;
        }

        string centerName;
        double radius;

        cout << "Enter the center point name for " << shapeName << ": ";
        getline(cin, centerName);

        if (centerName.empty()) {
          cout << "\033[31mError: Center point name not provided\033[0m"
               << endl;
          continue;
        }

        if (points.find(centerName) != points.end()) {
          cout << "Enter the radius for " << shapeName << ": ";
          radius = getValidatedRadiusInput();

          circles[shapeName] = Circle(points[centerName], radius);
          shapeNames.insert(shapeName);
          cout << "Created Circle " << shapeName << " with center "
               << centerName << " and radius " << radius << "\n";
        } else {
          cout << "\033[31mError: Center point '" << centerName
               << "' not found\033[0m\n";
        }
      } else if (shapeType == "line") {
        if (shapeNames.find(shapeName) != shapeNames.end()) {
          cout << "\033[31mError: Shape with name '" << shapeName
               << "' already exists\033[0m" << endl;
          continue;
        }

        string point1Name, point2Name;
        cout << "Enter the first point name for " << shapeName << ": ";
        getline(cin, point1Name);
        cout << "Enter the second point name for " << shapeName << ": ";
        getline(cin, point2Name);

        if (points.find(point1Name) != points.end() &&
            points.find(point2Name) != points.end()) {
          lines[shapeName] = Line(points[point1Name], points[point2Name]);
          shapeNames.insert(shapeName);
          cout << "Created Line " << shapeName << " from " << point1Name
               << " to " << point2Name
               << " with length: " << lines[shapeName].getLineLength() << endl;
        } else {
          cout << "\033[31mError: One or both points not found\033[0m" << endl;
        }
      } else if (shapeType == "rectangle") {
        if (shapeNames.find(shapeName) != shapeNames.end()) {
          cout << "\033[31mError: Shape with name '" << shapeName
               << "' already exists\033[0m" << endl;
          continue;
        }

        string bottomLeftName, topRightName;
        cout << "Enter the bottom left point name for " << shapeName << ": ";
        getline(cin, bottomLeftName);
        cout << "Enter the top right point name for " << shapeName << ": ";
        getline(cin, topRightName);

        if (points.find(bottomLeftName) != points.end() &&
            points.find(topRightName) != points.end()) {
          if (points[bottomLeftName].x > points[topRightName].x ||
              points[bottomLeftName].y > points[topRightName].y) {
            cout << "\033[31mError: Invalid rectangle points\033[0m" << endl;
            continue;
          }

          rectangles[shapeName] =
              Rectangle(points[bottomLeftName], points[topRightName]);
          shapeNames.insert(shapeName);
          cout << "Created Rectangle " << shapeName << " with corners ";
          points[bottomLeftName].print();
          cout << " and ";
          points[topRightName].print();
          cout << ", Area: " << rectangles[shapeName].getRectArea()
               << ", Perimeter: " << rectangles[shapeName].getRectPerimeter()
               << endl;
        } else {
          cout << "\033[31mError: One or both corner points not found\033[0m"
               << endl;
        }
      } else {
        cout << "\033[31mError: Unknown shape type \033[0m" << shapeType
             << endl;
      }
    } else if (query == "list") {
      std::string shapeType;
      strStream >> shapeType;

      if (shapeType == "points") {
        if (points.empty()) {
          std::cout << "No points created yet\n";
        } else {
          std::cout << "List of points:\n";
          for (const auto& pair : points) {
            std::cout << pair.first << ": ";
            pair.second.print();
            std::cout << "\n";
          }
        }
      } else if (shapeType == "circles") {
        if (circles.empty()) {
          std::cout << "No circles created yet\n";
        } else {
          std::cout << "List of circles:\n";
          for (const auto& pair : circles) {
            std::cout << pair.first << ": ";
            pair.second.print();
          }
        }
      } else if (shapeType == "lines") {
        if (lines.empty()) {
          std::cout << "No lines created yet\n";
        } else {
          std::cout << "List of lines:\n";
          for (const auto& pair : lines) {
            std::cout << pair.first << ": ";
            pair.second.print();
          }
        }
      } else if (shapeType == "rectangles") {
        if (rectangles.empty()) {
          std::cout << "No rectangles created yet\n";
        } else {
          std::cout << "List of rectangles:\n";
          for (const auto& pair : rectangles) {
            std::cout << pair.first << ": ";
            pair.second.print();
          }
        }
      } else {
        std::cout << "Unknown shape type for listing: " << shapeType << ".\n";
      }
    } else if (query == "length") {
      string shapeName;
      strStream >> shapeName;

      try {
        double length = evaluateExpression("length " + shapeName, points,
                                           circles, rectangles, lines);
        cout << "Length of " << shapeName << ": " << length << endl;
      } catch (const runtime_error& e) {
        cout << e.what() << endl;
      }
    } else {
      // Handle arithmetic expressions involving perimeter, area, circumference,
      // and distance
      try {
        double result =
            evaluateExpression(command, points, circles, rectangles, lines);
        cout << "Result: " << result << endl;
      } catch (const runtime_error& e) {
        cout << e.what() << endl;
      }
    }
  }

  return 0;
}
