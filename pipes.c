#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int child[2];
  int parent[2];
  pipe(child);
  pipe(parent);
  if (fork() == 0) {
    // Child process
    close(parent[WRITE]);
    close(child[READ]);
    int update;
    read(parent[READ], &update, sizeof(update));
    printf("child doing math on: %d\n", update);
    update = update/2 + 9;
    write(child[WRITE], &update, sizeof(update));
  } else {
    // Parent process
    close(child[WRITE]);
    close(parent[READ]);
    int value = 12;
    write(parent[WRITE], &value, sizeof(value));
    printf("parent sent: %d\n", value);
    read(child[READ], &value, sizeof(value));
    printf("parent received: %d\n", value);
  }
  return 0;
}
