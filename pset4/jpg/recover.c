/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define SIZE 512
#define RESERVED 4
FILE* IMG;
int main(void)
{
// Declare JPEG bytes.
uint8_t jpeg[RESERVED] = {0xff, 0xd8, 0xff, 0xe0};
uint8_t jpeg2[RESERVED] = {0xff, 0xd8, 0xff, 0xe1};
uint8_t buffer[SIZE];
uint8_t byte[RESERVED];
//Image Counter
int image=0,mode=0;
// Open .raw
FILE* file = fopen("card.raw", "r");	

	if(file == NULL)	
		{	
		fclose(file);
		fprintf(stderr, "File is invalid or not found!\n");
		return 1;
		}

fread(buffer, SIZE, 1, file);	

while(fread(buffer, SIZE, 1, file) > 0)
{
// Copy RESERVED bytes
	int i=0;
	while(i<RESERVED)
	{
	   	byte[i]=buffer[i];
		i++;	
	}
// Check for JPEGs, compare bytes using memcmp
	if((memcmp(jpeg, byte, RESERVED) == 0 ) || (memcmp(jpeg2, byte, sizeof(byte)) == 0))
	{
	// Create filenames
		char* filename;
		filename=malloc(8);
		sprintf(filename, "%03d.jpg", image);
		switch(mode)
		{
		  case 0:
			IMG = fopen(filename, "w");
			fwrite(buffer, sizeof(buffer), 1, IMG);
			mode = 1;
		  case 1:
			fclose(IMG);
			IMG = fopen(filename, "w");
			fwrite(buffer, sizeof(buffer), 1, IMG);
			image++;
			break;
		}
		free(filename);
	}
	else
	{
		if(mode == 1)
		fwrite(buffer, sizeof(buffer), 1, IMG);
	}
}
    
// Close files
fclose(IMG);
fclose(file);
return 0;
}

