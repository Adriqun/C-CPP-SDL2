/* compute crc's */
/* crc-ccitt is based on the polynomial x^16+x^12+x^5+1 */
/* The prescription for determining the mask to use for a given polynomial
	is as follows:
		1.  Represent the polynomial by a 17-bit number
		2.  Assume that the most and least significant bits are 1
		3.  Place the right 16 bits into an integer

	Celem Cwiczenia jest modyfikacja kodu, aby liczyl prawidlowo sume CRC dla wielomianu
	CRC64:
	x^{{64}}+x^{{62}}+x^{{57}}+x^{{55}}+x^{{54}}+x^{{53}}+x^{{52}}+
	x^{{47}}+x^{{46}}+x^{{45}}+x^{{40}}+x^{{39}}+x^{{38}}+x^{{37}}+x^{{35}}+x^{{33}}+ x^{{32}}+
	x^{{31}}+x^{{29}}+x^{{27}}+x^{{24}}+x^{{23}}+x^{{22}}+x^{{21}}+x^{{19}}+x^{{17}}+
	x^{{13}}+x^{{12}}+x^{{10}}+x^{9}+x^{7}+x^{4}+x+1

	CRC64: 1010000101111000011100001111010111010100111101010011011010010011
	CRC64:
	64		1
	63-48	0100001011110000
	47-32	1110000111101011
	31-16	1010100111101010
	15-0	0011011010010011

	MTT = 0x42F0E1EBA9EA3693
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MTT 0x42F0E1EBA9EA3693 // Polynomial, crc-ccitt mask
#define CLK_TCK CLOCKS_PER_SEC

// Update crc
unsigned long long updcrc(unsigned long long crc, unsigned long long c, unsigned long long mask)
{
	int i;
	crc ^= c << 56;
	for (i = 0; i < 8; i++)
	{
		if ((crc & 0x8000000000000000) != 0)
			crc = (crc << 1) ^ mask;
		else
			crc <<= 1;
	}

	return crc;
}

void GenerateInputDataFile(void* data, int bytes, const char* filename)
{
	FILE* file = fopen(filename, "wb");
	fwrite(data, bytes, 1, file);
	fclose(file);
}

// Driver
int main(int argc, char** argv)
{
	char* filename_out = "test.bin";
	unsigned long long data = 0xFAFAFAFAFAFAFAFA;
	//unsigned long long data = 0xFFFFFFFFFFFFFFFF;
	GenerateInputDataFile(&data, 8, filename_out);

	if (argc > 2)
	{
		printf("Usage:  ccitt [filename]");
		exit(1);
	}

	char filename[100];
	if (argc == 2)
		strcpy(filename, argv[1]);
	else
	{
		printf("\nEnter filename:  ");
		gets(filename);
	}

	FILE* fp;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("Can't open file");
		exit(1);
	}
		
	unsigned long nbytes = 0L;
	unsigned long long result = 0; // CRCTT

	clock_t end, start = clock();
	int ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		nbytes++;
		result = updcrc(result, ch, MTT);
	}
	end = clock();
	fclose(fp);

	printf("\nNumber of bytes = %lu\nCRCTT = %llX\n", nbytes, result);
	printf("Execution time: %f\n", (double)(end - start) / CLK_TCK);
	return 0;
}
