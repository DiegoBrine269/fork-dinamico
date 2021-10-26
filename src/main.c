#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void errorEnFork();
void procesoHijo(char *niveles);
void procesoPadre(pid_t pid);

int main (int argc, char *argv[]) {
    pid_t pid;
    int status;

    int i;
    char *niveles;

    niveles = argv[1];

    if (argc != 2) {
        fprintf(stderr, "Insuficientes parámetros"); 
        return 1;
    }
    
    int numeroHijos = 2;

    //Creamos 2 hijos
    for (size_t i = 0; i < numeroHijos; i++){

        pid = fork();

        if (pid == -1){
            errorEnFork();
        }
        else if (pid == 0){//Ejecución del hijo
            
            //Cada hijo, crea 1 hijo
            procesoHijo(niveles);
            
            break;
        }
        else{
            procesoPadre(pid);
        }    
        wait(NULL);       
    }

    for (size_t i = 0; i < numeroHijos; i++){
        wait(NULL);
    }

    exit(0);
}

void errorEnFork(){
    printf("\nNo se pudo crear un proceso hijo");
}

void procesoPadre(pid_t pid){
    pid_t miID = getpid();
    pid_t hijoID = pid;
    printf("\nYo soy el proceso padre, mi ID es: %d El ID del hijo es %d\n", miID, hijoID);
}

void procesoHijo(char *niveles){
    pid_t miID = getpid();
    pid_t padreID = getppid();

    if(miID == padreID+1){
        //Hijo que creará dos hijos en cada nivel
        printf("\nYo soy el proceso hijo de la izquierda, mi ID es %d El ID del padre es %d\n", miID, padreID);
        
        char *argumentos [] = {"./clonacion_proceso", niveles, "2"};
        execvp(argumentos[0], argumentos);
        fprintf(stderr, "Failed to execvp() '%s' (%d: %s)\n", argumentos[0], errno, strerror(errno));
    }
    else{
        //Hijo que creará 3 hijos en cada nivel
        printf("\nYo soy el proceso hijo de la derecha, mi ID es %d El ID del padre es %d\n", miID, padreID);

        char *argumentos [] = {"./clonacion_proceso", niveles, "3"};
        execvp(argumentos[0], argumentos);
        fprintf(stderr, "Failed to execvp() '%s' (%d: %s)\n", argumentos[0], errno, strerror(errno));    
    }
}