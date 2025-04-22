#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig) {
  printf("Help! I've been shot!\n");
  fflush(stdout);
  exit(0);
}

int main()
{
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    printf("Error call to signal, SIGINT\n");
    exit(1);
  }

  while(1) {
    pause();
  }
  return 0;
}
