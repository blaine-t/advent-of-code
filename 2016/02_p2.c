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
  int sizeX = 5;
  int sizeY = 5;
  char keypad[5][5] = {{'\0','\0','5','\0','\0'},{'\0','2','6','A','\0'},{'1','3','7','B','D'},{'\0','4','8','C','\0'},{'\0','\0','9','\0','\0'}};
  int currX = 0;
  int currY = 2;
  char filename[] = "e.txt";
  int numLines;
  char **lines = getfilelines(filename, &numLines);
  for (int i = 0; i < numLines; i++) {
    char* line = lines[i];
    for (int j = 0; j < strlen(line); j++) {
      int oldX = currX;
      int oldY = currY;
      char c = line[j];
      if(c == 'D') {
        if(currY < sizeY - 1) {
          currY++;
        }
      } else if (c == 'R') {
        if(currX < sizeX - 1) {
          currX++;
        }
      } else if (c == 'U') {
        if(currY > 0) {
          currY--;
        }
      } else if (c == 'L') {
        if(currX > 0) {
          currX--;
        }
      }
      if(keypad[currX][currY] == '\0') {
        currX = oldX;
        currY = oldY;
      }
    }
    printf("%c", keypad[currX][currY]);
  }
  printf("\n");
  return 0;
} 