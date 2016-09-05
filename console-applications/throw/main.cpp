#include <iostream>

double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   
   return (a/b);
}

int main(int argc, char **argv)
{
    std::cout << division( 10, 0 );
	
    return 0;
}
