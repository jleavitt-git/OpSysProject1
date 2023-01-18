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
        char program[80], *args[3];
        strcpy(program, "slug");
        args[0] = "slug";
        args[1] = numChild;
        args[2] = NULL;
        printf("[Child, PID: %d] Executing './slug %d' command...\n", getpid(), args[1]);
        execvp(program, args);
    }

    bool race = true;
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);

    if(getpid() == parent){
        while(race){
            usleep(3300000);
            race = false;
            char result[120];
            strcpy(result, "The race is still ongoing. Children still racing: ");
            for(int i = 0; i < 4; i++){
                int status;
                int cpid = waitpid(children[i], &status, WNOHANG);
                printf("CHILD: %d, STATUS: %d, CPID: %d\n",children[i], status, cpid);
                if(status >= 0){
                    char buffer[10];
                    race = true; //One or more still alive
                    sprintf(buffer, "%d", children[i]);
				    strcat(result, buffer);
				    strcat(result, " ");
                }
                else if(cpid == -100){
                    struct timespec childStop;
                    clock_gettime(CLOCK_REALTIME, &childStop);
                    double finishTime;
                    finishTime = getRaceTime(start, childStop);
                    printf("Child %d has crossed the finish line! It took %lf seconds.\n", cpid, finishTime);

                }

            }
            strcat(result, "\n");
            printf("%s", result);
        }



        clock_gettime(CLOCK_REALTIME, &stop);
        double raceTime;
        raceTime = getRaceTime(start, stop);
    }

}

double getRaceTime(struct timespec start, struct timespec stop){
    double finish = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1000000000;
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