/*
 * Boas! Até agora o que fiz foi a parte de ir aos diretórios todos e meter a
 * informação toda no files.txt
 * Basicamente temos 3 aplicações:
 * - o lsdir mete todos os ficheiros regulares de um diretorio no files.txt
 * - o execlsdir vai a todos os diretorios executar o lsdir
 * - o rmdup executa o execlsdir e depois lê o files.txt e altera os links para
 * ficheiros duplicados. Falta essa parte basicamente.
 */

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

	if(pid == 0)
	{
		execlp("./execlsdir", "execlsdir", argv[1], NULL);
	}

	int status;

	wait(&status);

	if((f = fopen(files, "r")) == NULL)
	{
		perror("Could not open files.txt for reading");
		exit(2);
	}

	pid = fork();

	if(pid == 0)
	{
		execlp("sort", "sort", "-o", files, files, NULL);
	}

	wait(&status);

	char name[200];
	char dir[200];
	int size;
	char mode[200];
	char timeCreation[200];

	char name2[200];
	char dir2[200];
	int size2;
	char mode2[200];
	char timeCreation2[200];

	char hlinks[200];

	strcpy(hlinks, argv[1]);
	strcat(hlinks, "/hlinks.txt");

	FILE* output;

	if((output = fopen(hlinks, "w")) == NULL)
	{
		perror("Could not open hlinks.txt");
		exit(2);
	}

	if(fscanf(f, "%s %s %d %s %s", name, dir, &size, mode, timeCreation) == EOF)
	{
		return 0;
	}

	while(fscanf(f, "%s %s %d %s %s", name2, dir2, &size2, mode2, timeCreation2) != EOF)
	{
		if(strcmp(name, name2) == 0 && size == size2 && strcmp(mode, mode2) == 0 && timeCreation == timeCreation2)
		{

		}
	}

	return 0;
}
