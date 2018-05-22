#include <iostream>

using namespace std;

class Dog
{
public:
	Dog() = default;
	Dog( string name ) {/*...*/};
};

int main(int argc, char **argv)
{
	Dog dog1;
	Dog dog2( "" );
	
	return 0;
}
