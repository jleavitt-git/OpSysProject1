#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    int pid = getpid();
    int seedFile;
    if(argc == 2){
        seedFile = atoi(argv[1]);
    }
    else{
        printf("No arguments supplied, goodbye. \n");
        exit(-1);
    }

    int seed;
    switch(seedFile){
        case 1:
            seed = getSeed("seed_slug_1.txt");
            break;
        case 2:
            seed = getSeed("seed_slug_2.txt");
            break;
        case 3:
            seed = getSeed("seed_slug_3.txt");
            break;
        case 4:
            seed = getSeed("seed_slug_4.txt");
            break;
        default:
            printf("Invalid argument supplied, goodbye.\n");
            exit(-1);
    }

    printf("[Slug PID: %d] Read seed value (converted to integer): %d\n", pid, seed);

    srand(seed);

    int waitVal = getRand(2, 6);
    int coinFlip = getRand(0, 1);

    printf("[Slug PID: %d] Delay time is %d seconds. Coin flip: %d\n", pid, waitVal, coinFlip);
    printf("[Slug PID: %d] I'll get the job done. Eventually...\n", pid);
    sleep(waitVal);

    if(coinFlip > 0){
        printf("[Slug PID: %d] Break time is over! I am running the '%s' command.\n", pid, "id --group");
        char *args[3];
        args[0] = "id";
        args[1] = "--group";
        args[2] = NULL;
        execvp("id", args);
    }
    else{
        printf("[Slug PID: %d] Break time is over! I am running the '%s' command.\n", pid, "last -i -x");
        char *args[4];
        args[0] = "last";
        args[1] = "-i";
        args[2] = "-x";
        args[3] = NULL;
        execvp("last", args);;
    }

}

int getSeed(const char* file_name){

    FILE* file = fopen (file_name, "r");
    int i = 0;

    fscanf (file, "%d", &i);    

    printf("[Slug PID: %d] Read seed value: %d\n\n", getpid(), i);

    fclose (file);
    return i;
}

int getRand(int low, int high){
    int random = (rand() % (high - low + 1)) + low;
    return random;
}