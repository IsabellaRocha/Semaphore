#include "sem.h"

int shmd, semd,
union semun su;
struct sembuf sb;


int main(int argc, har *argv[]) {
    su.val = 1;sb.sem_num = 0;
    //sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    run();
    return 0;
}
int run() {
    char * args;
    fgets(args, 3, stdin);
    if(strcmp(args, "-c") == 0){
        semd = semget(KEY, 1, IPC_CREAT|0644);
        if(semd != 0) {
            printf("Error: %s", strerror(errno));
            return 1;
        }
        semctl(semd, 0, SETVAL, su); //Performing setval from su on the first semaphore in semd
        printf("semaphore created\n");
        shmd = shmget(KEY, sizeof(char *), IPC_CREAT|0644);
        if(shmd != 0) {
            printf("Error: %s", strerror(errno));
            return 1;
        }
        printf("shared memory created\n");
        int fd = open("tel.txt", O_CREAT|O_TRUNC|O_RDWR, 0744);
        if(fd != 0) {
            printf("Error: %s", strerror(errno));
            return 1;
        }
        close(fd);
        printf("file created");
    }
    if(strcmp(args, "-r") == 0) {

    }
    if(strcmp(args, "-v") == 0) {
        printf("The story so far: \n");
        int fd = open("tel.txt", O_RDONLY);
        char output[SEG_SIZE];
        read(fd, output, SEG_SIZE);
        printf("%s", output);
        close(fd);
    }
}
