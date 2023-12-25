#include <stdio.h>
#include <stdlib.h>
// #include <errno.h>
#include <unistd.h>
// #include <sys/types.h>
#include <sys/wait.h>

int f1(void) {
  return 0;
}

int main(void)
{
  pid_t child;

  if ((child = fork()) == 0) {
    printf(" CHILD: This is the child process!\n");
    printf(" CHILD: My PID is %d\n", getpid());
    printf(" CHILD: My parent's PID is %d\n", getppid());
    f1();
  }
  else if (child != -1) {
    printf("PARENT: This is the parent process!\n");
    printf("PARENT: My PID is %d\n", getpid());
    printf("PARENT: My child's PID is %d\n", child);
    f1();
    waitpid(child, NULL, 0);
  }

  return 0;
}