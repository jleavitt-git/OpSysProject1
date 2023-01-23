#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{

    
    //read seed from seed.txt
    int seed = getSeed("seed.txt");

    srand(seed);

    printf("Read seed value (converted to integer): %d\n", seed);
    printf("It's time to see the world/file system!\n");

    int parent = getpid();

    for (int i = 0; i < 5; i++)
    {
        printf("Selection #%d: ", i+1);
        int random = rand() % 6;
        switch(random){
            case 0 :
                printf("/home\n");
                chdir("/home");
                break;
            case 1 :
                printf("/proc\n");
                chdir("/proc");
                break;
            case 2 :
                printf("/proc/sys\n");
                chdir("/proc/sys");
                break;
            case 3 :
                printf("/usr\n");
                chdir("/usr");
                break;
            case 4 :
                printf("/usr/bin\n");
                chdir("/usr/bin");
                break;
            case 5 :
                printf("/bin\n");
                chdir("/bin");
                break;
        }

        checkd();
        
        int child;

            child = fork();

            if (child == 0)
            {
                char* argument_list[] = {"ls", "-tr", NULL};
                printf("[Child, PID: %d]: Executing 'ls -tr' command...\n", getpid());
                execvp("ls", argument_list);
                exit(0);
            }
            printf("[Parent]: I am waiting for PID %d to finish.\n", child);
            int exitStatus;
            waitpid(child, &exitStatus, 0);
            printf("[Parent]: Child %d finished with status code %d. Onward!\n", child, WEXITSTATUS(exitStatus));
    }
}

void checkd(){
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    printf("Current working directory is: %s\n", cwd);
}


int getSeed(const char* file_name){

    FILE* file = fopen (file_name, "r");
    int i = 0;

    fscanf (file, "%d", &i);    

    printf("Read seed value: %d\n\n", i);

    fclose (file);
    return i;
}

