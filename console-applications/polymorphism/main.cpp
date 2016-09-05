#include <iostream> 
using namespace std;
 
class Shape
{
	
protected:
   
      int width;
	  int height;
	  
public:

      Shape( int a = 0, int b = 0 )
      {
         width = a;
         height = b;
      }
	  
      virtual void area() = 0;
	  
};
class Rectangle: public Shape
{
	
public:
   
      Rectangle( int a = 0, int b = 0 ):Shape( a, b ) { }
      void area ()
      { 
         cout << "Rectangle class area : " << (width * height)<< endl;
      }
	  
};

class Triangle: public Shape
{
	
public:
   
      Triangle( int a = 0, int b = 0 ):Shape( a, b ) { }
      void area ()
      { 
         cout << "Triangle class area : " << (width * height / 2) << endl;
      }
	  
};

int main( )
{
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);

   // store the address of Rectangle
   shape = &rec;
   // call rectangle area.
   shape->area();

   // store the address of Triangle
   shape = &tri;
   
   // call triangle area.
   shape->area();
   
   return 0;
}
