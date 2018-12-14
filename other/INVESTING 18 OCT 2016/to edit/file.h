#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class File
{
	fstream file;
	
	float eur;
	float usd;
	float gbp;
	
public:

	File();
	~File();
	
	bool load();
	float get( string type );
};