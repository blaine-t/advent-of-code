#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **getfilelines(char *filename, int *numLines) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  int n = 1000; // max line length, increase this if it breaks
  char buffer[n];
  char *line = fgets(buffer, n, f);
  *numLines = 0;
  while (line != NULL) {
    (*numLines)++;
    line = fgets(buffer, n, f);
  }
  char **lines = (char **) malloc((*numLines) * sizeof(char *));
  rewind(f);
  line = fgets(buffer, n, f);
  int currentLine = 0;
  while (line != NULL) {
    int lineLen = strlen(line);
    lines[currentLine] = (char *) malloc(lineLen * sizeof(char) + 1);
    strcpy(lines[currentLine], line);
    // remove newline character at the end of each line
    if (lines[currentLine][lineLen-1] == '\n') {
      lines[currentLine][lineLen-1] = '\0';
    }
    currentLine++;
    line = fgets(buffer, n, f);
  }
  return lines;
}

int main(int argc, char **argv) {
  char* filename = "e.txt";
  if(argc >= 2) {
    filename = argv[1];
  }
  int numLines;
  char **lines = getfilelines(filename, &numLines);
  if (lines == NULL) {
    printf("couldn't read the file dumbass\n");
    exit(1);
  }
  printf("SET TO: %s\n", filename);
  for (int i = 0; i < numLines; i++) {
    char* line = lines[i];
    for (int j = 0; j < strlen(line); j++) {
      char c = line[j];
      printf("%c\n", c);
    }
    printf("\n");
  }
  return 0;
}