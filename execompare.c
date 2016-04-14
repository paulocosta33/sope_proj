#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("Usage: %s <dir>\n", argv[0]);
		exit(1);
	}
   
   FILE *fp1, *fp2;
   int ch1, ch2;
   char fname1[40], fname2[40];
 
   printf("Name of the first file :");
   gets(fname1);
 
   printf("Name of the second file:");
   gets(fname2);
 
   fp1 = fopen(fname1, "r");
   fp2 = fopen(fname2, "r");
 
   if (fp1 == NULL) {
      printf("Cannot open %s for reading ", fname1);
      exit(1);
   } else if (fp2 == NULL) {
      printf("Cannot open %s for reading ", fname2);
      exit(1);
   } else {
      ch1 = getc(fp1);
      ch2 = getc(fp2);
 
      while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
         ch1 = getc(fp1);
         ch2 = getc(fp2);
      }
 
      if (ch1 == ch2)
         printf("Files are identical n");
      else if (ch1 != ch2)
         printf("Files are Not identical n");
 
      fclose(fp1);
      fclose(fp2);
   }
   return (0);
}