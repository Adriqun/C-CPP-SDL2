#include "file.h"

File::File()
{
	// empty
}

File::~File()
{
	// empty
}

bool File::load()
{
	file.open( "data/ratio.txt" );
	if( file.bad() )
	{
		cout << "Not loaded file data/ratio.txt!\n";
		return false;
	}
	else
	{
		string line;
		std::string::size_type alias;
		
		getline( file, line );
		eur = stof( line, &alias);
		
		getline( file, line );
		usd = stof( line, &alias);
		
		getline( file, line );
		gbp = stof( line, &alias);
	}
	file.close();
	
	return true;
}

float File::get( string type )
{
	if( type == "eur" )
	{
		return eur;
	}
	else if( type == "usd" )
	{
		return usd;
	}
	else if( type == "gbp" )
	{
		return gbp;
	}
	else
	{
		return 0.0;
	}
}
