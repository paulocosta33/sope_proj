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

	DIR* dirp;
	struct dirent* direntp;
	struct stat stat_buf;
	char* str;
	char name[200];
	FILE* f;

	int i;

	if((f = fopen(argv[3], "a")) == NULL)
	{
		perror("Could not open files.txt");
		exit(4);
	}

	if((dirp = opendir(argv[1])) == NULL)
	{
		perror(argv[1]);
		exit(2);
	}

	while((direntp = readdir(dirp)) != NULL)
	{
		sprintf(name, "%s/%s", argv[1], direntp->d_name);

		if((lstat(name, &stat_buf)) == -1)
		{
			perror("stat error");
			exit(3);
		}

		if(S_ISREG(stat_buf.st_mode))
		{
			/*fwrite(direntp->d_name, sizeof(char), sizeof(direntp->d_name), f);
			fwrite(argv[2], sizeof(char), sizeof(argv[2]), f);
			fwrite(&stat_buf.st_size, sizeof(long long), sizeof(stat_buf.st_size), f);
			fwrite(&stat_buf.st_mode, sizeof(unsigned long), sizeof(stat_buf.st_mode), f);

			int tmp = ctime(&stat_buf.st_ctim);
			fwrite(&tmp, sizeof(int), sizeof(ctime(&stat_buf.st_ctim)), f);*/
			//fprintf(f, "%s\n", direntp->d_name);
			fprintf(f, "%s %s %lld %lo %d\n", direntp->d_name, argv[2], (long long)stat_buf.st_size, (unsigned long)stat_buf.st_mode, ctime(&stat_buf.st_ctim));
		}
	}

	return 0;
}
