#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
/*TODO:

Make execvp work
make sure logic checks proper CPID or Status to see if program terminates.

*/
double getRaceTime(struct timespec, struct timespec);

int main(){

    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);
    printf("START: %lf\n", start.tv_nsec);
    int parent = getpid();
    int children[4];
    int numChild;
    for(int i = 0; i < 4; i++){
        if(getpid() == parent){
            children[i] = fork();
            numChild = i+1;
        }
    }
    if(getpid() != parent){
        char program[80], *args[3], num[10];
        strcpy(program, "./slug");
        sprintf(num, "%d", numChild);
        args[0] = "./slug";
        args[1] = num;
        args[2] = NULL;
        printf("[Child, PID: %d] Executing './slug %d' command...\n", getpid(), numChild);
        execvp(program, args);
    }

    bool race = true;

    if(getpid() == parent){
        while(race){
            usleep(330000);
            race = false;
            char result[120];
            strcpy(result, "The race is still ongoing. Children still racing: ");
            for(int i = 0; i < 4; i++){
                int status;
                int cpid = waitpid(children[i], &status, WNOHANG);
                //printf("CHILD: %d, STATUS: %d, CPID: %d\n",children[i], status, cpid);
                if(cpid == 0){
                    char buffer[10];
                    race = true; //One or more still alive
                    sprintf(buffer, "%d", children[i]);
				    strcat(result, buffer);
				    strcat(result, " ");
                }
                else if(cpid != -1 && cpid != 0){
                    struct timespec childStop;
                    clock_gettime(CLOCK_REALTIME, &childStop);
                    double finishTime;
                    finishTime = getRaceTime(start, childStop);
                    printf("Child %d has crossed the finish line! It took %lf seconds.\n", children[i], finishTime);

                }

            }
            if(race){
                strcat(result, "\n");
                printf("%s", result); 
            }
        }



        clock_gettime(CLOCK_REALTIME, &stop);
        double raceTime;
        raceTime = getRaceTime(start, stop);
        printf("The race is over! It took %lf seconds!\n", raceTime);
    }

}

double getRaceTime(struct timespec start, struct timespec stop){
    double finish = (stop.tv_sec - start.tv_sec) + ((stop.tv_nsec - start.tv_nsec)/1000000000);
    return finish;
}

int getSlugArg(int pid, int children[]){
    for(int i = 0; i < 4; i++){
        if(children[i] == pid){
            return i+1;
        }
    }
    return 0;
}

int getRand(int low, int high){
    int random = (rand() % (high - low + 1)) + low;
    return random;
}

int getSeed(const char* file_name){

    FILE* file = fopen (file_name, "r");
    int i = 0;

    fscanf (file, "%d", &i);    

    printf("Read seed value: %d\n\n", i);

    fclose (file);
    return i;
}