// main.c

// Shell start process
int rsh_launch(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if(pid==0) {
    // Child process
    if(execvp(args[0], args) == -1) {
      perror("rsh");
    }
    exit(EXIT_FAILURE);
  } else if(pid < 0) {
    // Error forking
    perror("rsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

// Reading Line with getline() function
char *rsh_read_line(void) {
  char *line = NULL;
  ssize_t bufsize = 0; // getline allocates buffer instead

  if(getline(&line, &bufsize, stdin) == -1) {
    if(feof(stdin)) {
      exit(EXIT_SUCCESS); // EOF received
    } else {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }
  return line;
}

// Reading Line without getline() function
/*
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
*/

// Parsing Line
#define RSH_TOK_BUFSIZE 64
#define RSH_TOK_DELIM " \t\r\n\a"
char **rsh_spit_line(char *line) {
  int bufsize = RSH_TOK_BUFSIZE; 
  int position = 0;
  char **tokens = malloc(sizeof(char*) * bufsize);
  char *token;

  if(!tokens) {
    fprintf(stderr, "rsh: allocation error");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, RSH_TOK_DELIM);  // Tokenizing
  while(token != NULL) {
    tokens[position] = token;
    position++;

    if(position >= bufsize) {
      bufsize += RSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if(!tokens) {
        fprintf(stderr, "rsh: allocation error");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, RSH_TOK_DELIM);
  }
  tokens[position] = NULL; // NULL terminated array of pointers
  return tokens;
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

