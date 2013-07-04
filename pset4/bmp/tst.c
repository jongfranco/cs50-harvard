#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define SIZE 2
typedef struct{
    char* age;
    char* id;
}students; 

int main(int argc, char* argv[])
{
    //   students student;
       char* a="qwert";
	int x=2;
       FILE* fp=fopen(argv[1],"w");
       //student.age=GetString();
       while(x>0){
       fwrite(a,strlen(a),1,fp);
	x--;	
} 
      fclose(fp);
	return 0;
}
