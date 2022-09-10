#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){

    //Verifica se apenas/exatamente um parâmetro foi informado
    if(argc < 2)
    {
        printf("Missing parameter\n");
        exit(1);
    }
    else if(argc > 2)
    {
        printf("Too many arguments\n");
        exit(1);
    }

    //Verifica se o caminho informado é valido
    if (access(argv[1], F_OK) != 0) {
        printf("File path invalid.\n");
        exit(1);
    }

    printf("File name: %s\n", argv[1]);
    return 0;
}