##Introduction
Console application based on **eleven** sorting algorithms :books:.                                                           
I wrote it in C-language to keep the speed.  

##How it works
You have to write **one** number between 1-45 000 000, don't worry about mistake programm care about exceptions. If you wrote a
number you will see the time of each sorting algorithms.

Linux                                                                                                                     
![1](https://cloud.githubusercontent.com/assets/19840443/17803547/5bb7dcf2-65f7-11e6-873d-83ccdbdc0e33.png)

##In detail
**Align to center**                                                                                                         
1. You need to know console width.
2. In C add:
######include <sys/ioctl.h>	// winsize
######include <stdio.h>      // printf

######void centre( int w, char* s )
######{
######	unsigned long len = strlen( s );
######	int nr = ( w - len ) /2;
	
######	for( int i = 0; i < nr; ++i )
######	{
######		printf( " " );
######	}
	
######	printf( "%s", s );
######}
