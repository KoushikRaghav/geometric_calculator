# geometric_calculator

A Geometric Calculator Application to measure the shapes in a 2D space

## Objective

Develop a geometric calculator to measure shapes in a 2D space. This application will allow the users to define certain shapes in a 2D space, and then measure the distance, area and circumference

## Key Features
### 1. Shapes
- Point
- Line
- Circle
- Rectangle
  
### 2. Queries
 - Area of a shape
 - Length / Circumference / Perimeter of a shape
 - Distance between two shapes

### 3. Supported data types
  - Shapes
  - Floating point numbers

### 4. Arithmetic operations
  - Support for arithmetic numeric calculations


## Setup Steps

- Create a ROS1 Noetic Workspace
- ``` cd workspace/src/ ```
- ``` Unzip the folder```
- ```cd ..``` 
- ``` catkin build ```

## Run the Calculator


- Terminal 1 
  - ```roscore```
- Terminal 2 
  - ```source devel/setup.bash ``` 
  - ``` rosrun geometric_calculator geometric_calculator_node```
## Command Line Interface (CLI) for calculation (with examples)

Note : For any shape, basic requirement is to create atleast a point with x,y coordinates

### Step 1
- create shape with a name
   - ```create point {shapename}```
   - ```create line {shapename}```
   - ```create rectangle {shapename}```
   - ```create circle {shapename}```
- enter coordinates/values/pointnames seperated by space

### Step 2
- find length of a line
   - ```length {linename}```
- find distance between two shapes
   - ```distance {shape1name} {shape2name} ```
- find area of a circle
  - ```area {circlename}```
- find circumference of a circle
  - ```circumference {circlename}```
- find perimeter of a rectangle
  - ```perimeter {rectanglename}```
- find area of a rectangle
  - ```area {rectanglename}```
- list number of each shapes created 
  - ```list circles```
  - ```list points```
  - ```list rectangles```
  - ```list lines```
- arithmetic calculations (sum, sub, mul, div)
  - ```distance {shape1} {shape2} + distance {shape1} {shape2} ```
- close calculator
  - ```exit```

## Code Structure

- geometric_calculator.cpp --> Main ROS Node getting command line inputs from the user
- geometric_calculator.h --> Header file containing class and method declarations
- calculator_utils.cpp --> Utility methods for different shapes and other helper methods

## Other 
- Error Handling
  - The user cannot create a shape with a name that is already created 
  - The user shall enter whole numbers/floating point numbers for the values
  - The user shall enter shape name in string format followed by any numbers (like point1, circle4)
  - The user shall not enter any special characters while entering any input
  - The user cannot calculate length for a point
- VSCode Extensions used for maintaining code standards
  - cpplint
  - C++ Code Formatter
