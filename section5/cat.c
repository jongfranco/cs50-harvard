#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: cat filename [filename ...]\n");
        return 1;
    }
    FILE* fp;
    char buffer[10];
    int x;
    for(int i=1;i<argc;i++)
	{
		fp=fopen(argv[i],"r");
		fread()
	}
   fclose(fp);

    return 0;
}

