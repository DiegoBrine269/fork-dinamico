#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

void infoProceso(int i, pid_t pid);

int main(int argc, char *argv[]){

    pid_t pid;
    int i, niveles, hijos;

    niveles = atoi(argv[1]);
    hijos = atoi(argv[2]);
    pid=-1;
    
    for (i = 1; i <= niveles; i++){

        int numeroHijos;
        for(numeroHijos=0; numeroHijos<hijos; numeroHijos++){
            pid=fork();
            if (pid <= 0) break;
        }
        if (pid > 0) break;
    }

    while(wait(NULL) > 0) ; 

    infoProceso(i, pid);
    
    return 0;
}

void infoProceso(int i, pid_t pid){
    printf("Nivel:%d ID de proceso:%ld ID del padre:%ld ID del hijo:%ld\n",i, (long)getpid(), (long)getppid(), (long)pid);
}