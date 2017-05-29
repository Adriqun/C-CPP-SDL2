#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <stack>

using namespace std;

string to_pl( string text )
{
    string result;
    for( const auto &it :text )
	{
		switch( it )
		{
			case 'ą': result += static_cast <char> ( 0xa5 ); break;
			case 'ć': result += static_cast <char> ( 0x86 ); break;
			case 'ę': result += static_cast <char> ( 0xa9 ); break;
			case 'ł': result += static_cast <char> ( 0x88 ); break;
			case 'ń': result += static_cast <char> ( 0xe4 ); break;
			case 'ó': result += static_cast <char> ( 0xa2 ); break;
			case 'ś': result += static_cast <char> ( 0x98 ); break;
			case 'ż': result += static_cast <char> ( 0xbe ); break;
			case 'ź': result += static_cast <char> ( 0xab ); break;
			case 'Ą': result += static_cast <char> ( 0xa4 ); break;
			case 'Ć': result += static_cast <char> ( 0x8f ); break;
			case 'Ę': result += static_cast <char> ( 0xa8 ); break;
			case 'Ł': result += static_cast <char> ( 0x9d ); break;
			case 'Ń': result += static_cast <char> ( 0xe3 ); break;
			case 'Ó': result += static_cast <char> ( 0xe0 ); break;
			case 'Ś': result += static_cast <char> ( 0x97 ); break;
			case 'Ż': result += static_cast <char> ( 0xbd ); break;
			case 'Ź': result += static_cast <char> ( 0x8d ); break;
			default: result += it; break;
		}
	}
	
    return result;
}

void print_exam()
{
	printf( "\e[39m\e[100mVocabulary exam\e[49m\n\n" );
}

void print_message()
{
	printf( "Write name of file to open: \e[92m" );
}

int main()
{
	srand( time( NULL ) );
	
	vector <string> polish;
	vector <string> english;
	
	// #1
	while( true )
	{
		print_exam();
		print_message();
		
		string path;
		cin >> path;
		
		system( "clear" );
		print_exam();
		
		fstream file;
		file.open( path );
		if( !file.good() )
		{
			printf( "\e[91mCannot find file\e[39m %s | Try again! \n", path.c_str() );
			usleep( 3000000 );
			system( "clear" );
			file.close();
		}
		else
		{
			polish.clear();
			english.clear();
			
			string line;
			string pl;
			string eng;
			unsigned counter = 1;
			
			vector <int> errors;
			
			while( getline( file, line ) )
			{
				pl = "";
				eng = "";
				for( unsigned i = 0; i < line.size(); i++ )
				{
					if( line[ i +1 ] == '#' )
					{
						counter ++;
						for( unsigned j = i+3; j < line.size(); j++ )
						{
							eng += line[ j ];
						}
						
						break;
					}
					
					pl += line[ i ];
				}
				
				polish.push_back( pl );
				english.push_back( eng );
				
				if( polish.size() != english.size() ||
				polish.size() != counter ||
				english.size() != counter )
				{
					counter = polish.size();
					errors.push_back( polish.size() );
				}
			}
			
			// printf( "%d %d %d\n", polish.size(), english.size(), counter );
			
			if( polish.size() != english.size() ||
				polish.size() != counter ||
				english.size() != counter ||
				errors.size() > 1 )
			{
				printf( "\e[91mFile\e[39m %s\e[91m is corrupted!\e[39m | Try again! \n", path.c_str() );
				if( errors.size() > 1 )
				{
					printf( "# Error below: \n" );
					for( unsigned i = 1; i < errors.size(); i++ )
					{
						printf( "Line %d\n", errors[ i ] );
					}
				}
				
				
				usleep( 4000000 );
				system( "clear" );
				file.close();
				continue;
			}
			
			printf( "%s \e[92mloaded correctly!\e[39m\n", path.c_str() );
			usleep( 1500000 );
			system( "clear" );
			file.close();
			break;
		}
	}
	
	
	vector <int> numbers;
	int numbers_size;
	
	for( unsigned i = 0; i < polish.size(); i++ )
	{
		numbers.push_back( i );
	}
	
	numbers_size = polish.size();
	
	string a;
	getline( cin, a );
	
	while( true )
	{
		int result = 1;
		for( auto it: numbers )
		{
			if( it == -1 )
			{
				result ++;
			}
		}
		
		if( numbers.size() -result +1 == 0 )
		{
			numbers.clear();
			printf( "Nice, you finished exam, well done!\n\n" );
			break;
		}
		
		// Show progress
		printf( "Progress " );
		printf( "\e[104m" );
		float a = static_cast <float> (10000 /polish.size()) *(result -1);
		for( int i = 0; i < static_cast <int> (a) /300; i++ )
		{
			printf( " " );
		}
		printf( "\e[49m %d%c\n", static_cast <int> (a) /100, 37 );
		// ---
		
		printf( "Words left: %d\n\n", numbers.size() -result +1 );
		
		int nr;
		while( true )
		{
			int chosen = rand() %numbers.size();
			if( numbers[ chosen ] != -1 )
			{
				nr = numbers[ chosen ];
				break;
			}
		}
		
		printf( "Write answer for: \e[96m%s\e[39m\n", polish[ nr ].c_str() );
		printf( "Your answer: \e[93m" );
		
		string answer;
		getline( cin, answer );
		
		printf( "\e[39m\nResult:  " );
		
		if( answer == english[ nr ] )
		{
			printf( "\e[92mGreat!\e[39m\n" );
			numbers[ nr ] = -1;
			usleep( 2500000 );
		}
		else
		{
			printf( "\e[91mWrong!\e[39m  Correct is: %s\n", english[ nr ].c_str() );
			usleep( 3500000 );
		}
		
		system( "clear" );
	}
	
	polish.clear();
	english.clear();
	
	return 0;
}