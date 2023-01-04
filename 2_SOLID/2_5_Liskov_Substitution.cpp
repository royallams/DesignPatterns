

/* 
Rectangle 
- has height and width
- has setter and getter function
- has area calculation function

Another Fuction that process this Rectangle
- just takes the rectangle 
- and calls its own calculate area function 

Lets say Rect r{3,4}

But what if we wanna make a square that inherits from Rectangle?
- setheight and Setwidth virtual 
- so in square we redefine the way setwidth and setheight works
- But this is the place where we broke the lisko substitution problem 
- How?
- Because the child cannot be directly replaced with the parent function .. 
- Because the area function for square has completely changed and wont work for Rectangle 
- How do we fix this ? 
- -- The very idea of inheriting square from Rectangle is not a good idea. 
---- We can keep a boolean flag to handle square or not. 
---- Or we can create a factory responsible for create square and rectangle seperately but they return a rectangle base class. 
--- in  this case the sQUARE can be replaced by a Rectangle base class
----- what we did was seperating out the construction logic for square and rectangle. 
----- this construction logic will take the redefinition seperately ..
---- And area log remains same. 

*/
// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

#include <iostream>

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(const int width, const int height)
    : width{width}, height{height} { }

  int get_width() const { return width; }
  virtual void set_width(const int width) { this->width = width; }
  int get_height() const { return height; }
  virtual void set_height(const int height) { this->height = height; }

  int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {}
  void set_width(const int width) override {
    this->width = height = width;
  }
  void set_height(const int height) override {
    this->height = width = height;
  }
};

struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};

void process(Rectangle& r)
{
  int w = r.get_width();
  r.set_height(10);

  std::cout << "expected area = " << (w * 10) 
    << ", got " << r.area() << std::endl;
}

// int main()
// {
//   Rectangle r{ 5,5 };
//   process(r);

//   Square s{ 5 };
//   process(s);

//   getchar();
//   return 0;
// }
