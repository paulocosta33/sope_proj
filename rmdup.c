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
	if(argc != 2)
	{
		printf("Usage: %s <dir>\n", argv[0]);
		exit(1);
	}

	FILE* f;

	char files[200];

	strcpy(files, argv[1]);
	strcat(files, "/files.txt");

	if((f = fopen(files, "w")) == NULL)
	{
		perror("Could not open files.txt for writing");
		exit(2);
	}

	fclose(f);

	pid_t pid;

	pid = fork();

	if(pid == -1)
	{
		perror("Fork error");
		exit(3);
	}

	if(pid == 0)
	{
		execlp("./execlsdir", "execlsdir", argv[1], NULL);
	}

	int status;

	wait(&status);

	if((f = fopen(files, "r")) == NULL)
	{
		perror("Could not open files.txt for reading");
		exit(4);
	}

	pid = fork();

	if(pid == -1)
	{
		perror("Fork error");
		exit(5);
	}

	if(pid == 0)
	{
		execlp("sort", "sort", "-o", files, files, NULL);
	}

	wait(&status);

	char name[200];
	char dir[200];
	int size;
	char mode[200];
	long long timeCreation;

	char name2[200];
	char dir2[200];
	int size2;
	char mode2[200];
	long long timeCreation2;

	char hlinks[200];

	strcpy(hlinks, argv[1]);
	strcat(hlinks, "/hlinks.txt");

	FILE* output;

	if((output = fopen(hlinks, "w")) == NULL)
	{
		perror("Could not open hlinks.txt");
		exit(2);
	}

	if(fscanf(f, "%s %s %d %s %lld", name, dir, &size, mode, &timeCreation) == EOF)
	{
		return 0;
	}

	while(fscanf(f, "%s %s %d %s %lld", name2, dir2, &size2, mode2, &timeCreation2) != EOF)
	{
		if(strcmp(name, name2) == 0 && size == size2 && strcmp(mode, mode2) == 0)
		{
			char path1[200];
			char path2[200];

			strcpy(path1, dir);
			strcat(path1, "/");
			strcat(path1, name);

			strcpy(path2, dir2);
			strcat(path2, "/");
			strcat(path2, name2);

			pid = fork();

			if(pid == -1)
			{
				perror("Fork error");
				exit(6);
			}

			if(pid == 0)
			{
				execlp("diff", "diff", path1, path2, NULL);
			}

			wait(&status);

			if(status == 0)
			{
				pid = fork();

				if(pid == -1)
				{
					perror("Fork error");
					exit(7);
				}

				if(pid == 0)
				{
					if(timeCreation < timeCreation2)
					{
						pid = fork();

						if(pid == -1)
						{
							perror("Fork error");
							exit(8);
						}

						if(pid == 0)
						{
							execlp("rm", "rm", path2, NULL);
						}

						wait(&status);

						execlp("ln", "ln", path1, path2, NULL);
					}
					else
					{
						pid = fork();

						if(pid == -1)
						{
							perror("Fork error");
							exit(9);
						}

						if(pid == 0)
						{
							execlp("rm", "rm", path1, NULL);
						}

						wait(&status);

						execlp("ln", "ln", path2, path1, NULL);
					}
				}

				wait(&status);

				if(timeCreation < timeCreation2)
				{
					fprintf(output, "%s -> %s\n", path2, path1);
				}
				else
				{
					fprintf(output, "%s -> %s\n", path1, path2);
				}
			}
		}

		strcpy(name, name2);
		timeCreation = timeCreation2;
		strcpy(mode, mode2);
		size = size2;
		strcpy(dir, dir2);
	}

	fclose(output);

	return 0;
}
