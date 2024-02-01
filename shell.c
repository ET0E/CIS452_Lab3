#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

void run_commands(char* args[]){
    int status;

    if(strcmp(args[0], "cd") == 0){
        char *new_dir = args[1];
        if (chdir(new_dir) != 0) {
            perror("Error changing directory");
        }
        return ;
    }

     pid_t who = fork();
        if(who == 0){
            if(execvp(args[0], args) < 0){
                perror("Error running exec");
            }
            exit(1);
        }
        else{
            wait(&status);
            //printf("Task completed with exit status %d\n", WEXITSTATUS(status));
        }
        
}

int main(){
    char user_input[20];
    struct rusage usage;
    
    while(1){

        printf("User Input: ");
        scanf("%[^\n]", user_input);

        if((strcmp(user_input, "quit") == 0)){
            break;
        }

        char* tok = strtok(user_input, " ");
        char* args[10];
        int i = 0;
        while(tok != NULL){
            args[i++] = tok;
            tok = strtok(NULL, " ");
        }
        args[i] = NULL;

        run_commands(args);

        getrusage(getpid(), &usage);
        printf("%lu\n", usage.ru_utime);
        printf("%lu\n", usage.ru_nvcsw);
    }
    return 0;
}
