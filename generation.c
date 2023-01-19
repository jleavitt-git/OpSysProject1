#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){



int seed = getSeed("seed.txt");

srand(seed);

int random = getRand(5, 12);

printf("Read seed value (converted to integer): %d\n", seed);
printf("Random Descendant Count: %d\n", random);
printf("Time to meet the kids/grandkids/great grand kids/...\n");

int parent = getpid();

createChild(random);

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

void createChild(int descendants){
    int child;

    child = fork();

    if(child==0){
        printf("[Child, PID: %d]: I was called with descendant count=%d. I'll have %d descendant (s).\n", getpid(), descendants, descendants-1);

        descendants--;
        if(descendants != 0){
            createChild(descendants);
        }
        else{
            exit(0);
        }
    }   
    printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n", getpid(), child);
    int exitStatus;
    waitpid(child, &exitStatus, 0);
    printf("[Parent, PID: %d]: Child %d finished with status code %d. It's now my turn to exit.\n", getpid(), child, WEXITSTATUS(exitStatus));
    exit(WEXITSTATUS(exitStatus) + 1);
}
