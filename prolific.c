#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){

printf("I'm feeling prolific!\n");

int seed = getSeed("seed.txt");

srand(seed);

int random = getRand(8, 13);

printf("Read seed value (converted to integer): %d\n", seed);
printf("Random child Count: %d\n", random);

int randAr[random];

int parent = getpid();

for(int i = 0; i < random; i++){
    randAr[i] = rand();
}
for(int i = 0; i < random; i++){
    int child;

    child = fork();

    if (child == 0){
        int exitVal = (randAr[i] % 50) + 1;
        int waitTime = (randAr[i] % 3) + 1;
        printf("[Child, PID: %d]: I am the child and I will wait %d seconds and exit with code %d.\n", getpid(), waitTime, exitVal);
        sleep(waitTime);
        printf("[Child, PID: %d]: Now exiting...\n", getpid());
        exit(exitVal); 
    }
    printf("[Parent]: I am waiting for PID %d to finish.\n", child);
    int exitStatus;
    waitpid(child, &exitStatus, 0);
    printf("[Parent]: Child %d finished with status code %d. Onward!\n", child, WEXITSTATUS(exitStatus));
}
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