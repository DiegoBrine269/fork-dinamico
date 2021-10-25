#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void errorEnFork();
void procesoHijo();
void procesoPadre(pid_t pid);

int main () {
    pid_t pid;
    int status;

    int numeroHijos = 2;

    //Creamos 2 hijos
    for (size_t i = 0; i < numeroHijos; i++){

        pid = fork();

        if (pid == -1){
            errorEnFork();
        }
        else if (pid == 0){//Ejecución del hijo
            
            //Cada hijo, crea 1 hijo
            procesoHijo();
  
            pid = fork();

            if (pid == -1){
                errorEnFork();
            }
            else if (pid == 0){//Ejecución del hijo  
                //Cada hijo, creará otro hijo
                procesoHijo();
            }
            else{
                //Ejecución del padre
                procesoPadre(pid);
            }
            // wait(NULL);

            break;
        }
        else{//Ejecución del padre
            procesoPadre(pid);
        }    
        // wait(NULL);       
    }

    // for (size_t i = 0; i < numeroHijos; i++){
    //     wait(NULL);
    // }

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

void procesoHijo(){
    pid_t miID = getpid();
    pid_t padreID = getppid();

    if(miID == padreID+1){
        printf("\nYo soy el proceso hijo de la izquierda, mi ID es %d El ID del padre es %d\n", miID, padreID);
    }
    else{
        printf("\nYo soy el proceso hijo de la derecha, mi ID es %d El ID del padre es %d\n", miID, padreID);
    }
}