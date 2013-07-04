#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: cp source destination\n");
        return 1;
    }
  char buffer[10];
        FILE* fp=fopen(argv[1],"r");
        FILE* fp2=fopen(argv[2],"w");
	fread(buffer,9,1,fp);
 	fwrite(buffer,1,3,fp2);
	fclose(fp);
        fclose(fp2);

    return 0;
}

