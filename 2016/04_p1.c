#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

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

/**
 * read doubles from a single string and return as an array
 */
double *readdoubles(char *str, int *numDoubles) {
    char *s1 = (char *) malloc(strlen(str) * sizeof(char));
    char *s2 = (char *) malloc(strlen(str) * sizeof(char));
    strcpy(s1, str);
    strcpy(s2, str);
    *numDoubles = 0;
    char *token = strtok(s1, " ");
    while (token != NULL) {
        (*numDoubles)++;
        token = strtok(NULL, " ");
    }
    double *doubles = (double *) malloc((*numDoubles) * sizeof(double));
    int i = 0;
    token = strtok(s2, " ");
    while (token != NULL) {
        doubles[i] = atof(token);
        i++;
        token = strtok(NULL, " ");
    }
    free(s1);
    free(s2);
    return doubles;
}

/**
 * read integers from a single string and return as an array
 */
int *readints(char *str, int *numInts) {
    double *doubles = readdoubles(str, numInts);
    int *ints = (int *) malloc((*numInts) * sizeof(int));
    for (int i = 0; i < *numInts; i++) {
        ints[i] = (int) doubles[i];
    }
    free(doubles);
    return ints;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv) {
  int sum = 0;
  char* filename = "e.txt";
  if(argc == 2) {
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
    int lineLength = strlen(line);
    int sid = atoi(line + lineLength - 10);
    char alpha[26] = {'\0'};
    int sorted[26];
    for (int j = 0; j < lineLength - 11; j++) {
      char c = line[j];
      int index = (int) c - 97;
      if(index >= 0 && index < 26) {
        alpha[index] += 1;
      }
    }
    memcpy(sorted, alpha, sizeof(sorted));
    qsort(sorted, 26, sizeof(int), cmpfunc);
    bool broken = false;
    for(int j = lineLength - 6; j < lineLength - 1; j++) {
      int rank = j - lineLength + 6;
      char c = line[j];
      int index = (int) c - 97;
      if(sorted[25 - rank] != alpha[index]) {
        broken = true;
        break;
      }
    }
    if(!broken) {
      sum += sid;
    }
  }
  printf("%d\n", sum);
  return 0;
}