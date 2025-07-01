// main.c

void tinysh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = tinysh_read_line();
    args = tinysh_spit_line(line);
    status = tinysh_execute(args);

    free(line);
    free(args);
  } 
  while (status);
}

int main(int argc, char **argv) {
  // config files
  
  // run command loop
  tinysh_loop();

  // perform shutdown/cleanup

  return EXIT_SUCCESS;
}

