/*
Gabriel Tibola Castagnera
Willian Brun
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
// função que lê um arquivo e mostra no terminal usan system calls
void printFile(char *fileName, int size)
{
    int file = open(fileName, 0);
    char *buffer = (char *)malloc(sizeof(char) * size);
    read(file, buffer, size);
    write(1, buffer, size);
    write(1, "\n", 1);
    free(buffer);
}

int main(int argc, char *argv[])
{

    // Verifica se apenas/exatamente um parâmetro foi informado
    if (argc < 2)
    {
        printf("Missing parameter\n");
        exit(1);
    }
    else if (argc > 2)
    {
        printf("Too many arguments\n");
        exit(1);
    }
    // Verifica se o caminho informado é valido
    if (access(argv[1], F_OK) != 0)
    {
        printf("File path invalid.\n");
        exit(1);
    }
    char fileName[100];
    strcpy(fileName, argv[1]);
    printf("File Information\n");
    printf("File name: %s\n", argv[1]);
    // Verifica se é possível ler o arquivo
    if (fopen(fileName, "r"))
    {
        printf("The current process can read the file.\n");
    }
    else
    {
        printf("The current process cannot read the file.\n");
    }
    // Verifica se é possível escrever no arquivo
    if (fopen(fileName, "a"))
    {
        printf("The current process can write the file.\n");
    }
    else
    {
        printf("The current process cannot write the file.\n");
    }
    // cria o comando para saber o tipo dele
    char comand[100];
    strcpy(comand, "file ");
    strcat(comand, fileName);
    // mostra o tipo
    system(comand);
    // Pegar os dados do arquivo
    struct stat st;
    stat(fileName, &st);
    // tamanho do arquivo
    off_t size = st.st_size;
    //último acesso
    long int lastAccess = st.st_atime;
    //última modificação
    long int lastModification = st.st_mtime;
    // printa os dados
    printf("File size: %ld bytes\n", size);
    printf("Last file access: %s", ctime(&lastAccess));
    printf("Last file modification: %s", ctime(&lastModification));

    // printa o conteúdo do arquivo
    printf("\nFile content:\n");
    printFile(fileName, size);

    // printa os dados do processo
    printf("\nProcess Information of %s:\n", argv[0]);
    printf("ID process: %d\n", getpid());
    printf("Group ID: %d\n", getgid());

    return 0;
}