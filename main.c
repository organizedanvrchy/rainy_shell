// main.c
#include <stdio.h>

void rsh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = rsh_read_line();
    args = rsh_spit_line(line);
    status = rsh_execute(args);

    free(line);
    free(args);
  } 
  while (status);
}

int main(int argc, char **argv) {
  // config files
  
  // run command loop
  rsh_loop();

  // perform shutdown/cleanup

  return EXIT_SUCCESS;
}

