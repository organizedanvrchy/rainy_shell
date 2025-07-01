// main.c

// Reading Line
#define RSH_RL_BUFSIZE 1024
char *rsh_read_line(void) {
  int bufsize = RSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int char;

  if(!buffer) {
    fprintf(stderr, "rsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    // Read character
    char = getchar();

    // If at EOF, replaces with null char and return.
    if(char == EOF || char == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = char;
    }
    position++;

    // If buffer was exceeded, reallocate.
    if(position >= bufsize) {
      bufsize += RSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if(!buffer) {
        fprintf(stderr, "rsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

// Basic shell loop 
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
  while(status);
}

int main(int argc, char **argv) {
  // config files
  
  // run command loop
  rsh_loop();

  // perform shutdown/cleanup

  return EXIT_SUCCESS;
}

