#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(){


//gets seed from text file
int seed = getSeed("seed.txt");

srand(seed);

//gets random number between 5 and 12 inclusive
int random = getRand(5, 12);

printf("Read seed value (converted to integer): %d\n", seed);
printf("Random Descendant Count: %d\n", random);
printf("Time to meet the kids/grandkids/great grand kids/...\n");

//obtain parent process id
int parent = getpid();

//creates child processes based off random number of descendants
createChild(random);

}

//obtains random number between low and high inclusive
int getRand(int low, int high){
    int random = (rand() % (high - low + 1)) + low;
    return random;
}

//obtains seed from text file
int getSeed(const char* file_name){

    FILE* file = fopen (file_name, "r");
    int i = 0;

    fscanf (file, "%d", &i);    

    printf("Read seed value: %d\n\n", i);

    fclose (file);
    return i;
}

//recursive function that forks children based off number of descendants
void createChild(int descendants){
    int child;

    child = fork();

    //if child process
    if(child==0){
        printf("[Child, PID: %d]: I was called with descendant count=%d. I'll have %d descendant (s).\n", getpid(), descendants, descendants-1);

        descendants--;
        //if number of descendants is not 0, then call createChild recursively and fork again, otherwise exit with code 0
        if(descendants != 0){
            createChild(descendants);
        }
        else{
            exit(0);
        }
    }   
    //if parent, wait for child and then print childs exit code, and then exit with child's exit code +1
    printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n", getpid(), child);
    int exitStatus;
    waitpid(child, &exitStatus, 0);
    printf("[Parent, PID: %d]: Child %d finished with status code %d. It's now my turn to exit.\n", getpid(), child, WEXITSTATUS(exitStatus));
    exit(WEXITSTATUS(exitStatus) + 1);
}
