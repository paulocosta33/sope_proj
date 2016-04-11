#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
		DIR* dirp;
		struct dirent* direntp;
		struct stat stat_buf;
		char* str;
		char name[200];
		char path[200];
		char lsdir[200];
		char execlsdir[200];
		char files[200];
		char filesLocation[200];

		if(argc < 2)
		{
			printf("Usage: %s <dir>\n", argv[0]);
			exit(1);
		}

		if(argc == 2)
		{
			strcpy(filesLocation, argv[1]);
			strcat(filesLocation, "/files.txt");
			strcpy(files, argv[1]);
		}

		if(argc > 2)
		{
			strcpy(files, argv[2]);
			strcat(files, "/");
			strcat(files, argv[1]);
			strcpy(filesLocation, argv[3]);
		}

		if((dirp = opendir(files)) == NULL)
		{
			perror("Could not launch execlsdir");
			exit(2);
		}

		pid_t pid;

		pid = fork();

		if(pid == 0)
		{
			execlp("./lsdir", "lsdir", files, files, filesLocation, NULL);
		}

		while((direntp = readdir(dirp)) != NULL)
		{
			sprintf(name, "%s/%s", files, direntp->d_name);

			if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
			{
				continue;
			}

			if((stat(name, &stat_buf)) == -1)
			{
				perror("stat error");
				exit(3);
			}

			if(S_ISDIR(stat_buf.st_mode))
			{
				pid = fork();

				if(pid == 0)
				{
					execlp("./execlsdir", "execlsdir", direntp->d_name, files, filesLocation, NULL);
				}
				else
				{

				}
			}
		}

		return 0;
}
