#include <stdio.h>



int main()
{
    char mybuffer[80];

    FILE * pFile;
    pFile = fopen ("example.txt","r+");

    if (pFile == NULL)
        perror ("Error opening file");
    else
    {
        fputs ("Adrian Michalek",pFile);
        fflush (pFile);    // flushing or repositioning required
        fgets (mybuffer,80,pFile);
        puts (mybuffer);
        fclose (pFile);
        return 0;
    }
}
