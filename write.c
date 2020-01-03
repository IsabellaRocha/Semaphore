#include "sem.h"

int shmd, semd;
struct sembuf sb;

int main() {
  sb.sem_num = 0;
  //sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  my_write();
  return 0;
}

int my_write() {
    printf("trying to get in\n");
    semd = semget(KEY, 1, 0);
    if (semd < 0) {
        printf("Error: %s", strerror(errno));
        return 1;
    }
    semop(semd, &sb, 1);
    shmd = shmget(KEY, sizeof(char*), 0);
    if (shmd < 0) {
        printf("Error: %s", strerror(errno));
        return 1;
    }
    int fd = open("tel.txt", O_WRONLY|O_APPEND);
    char *line = shmat(shmd, 0, 0);
    printf("Last addition: %s\n\n", line);
    char input[SEG_SIZE];
    printf("Your addition: ");
    fgets(input, SEG_SIZE, stdin);
    write(fd, input, strlen(input));
    shmdt(input);
    close(fd);
    strcpy(line, input);
    sb.sem_op = 1;
    semop(semd, &sb, 1);
    return 0;
}
