#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

char **getfilelines(char *filename, int *numLines)
{
  FILE *f = fopen(filename, "r");
  if (f == NULL)
  {
    return NULL;
  }
  int n = 1000; // max line length, increase this if it breaks
  char buffer[n];
  char *line = fgets(buffer, n, f);
  *numLines = 0;
  while (line != NULL)
  {
    (*numLines)++;
    line = fgets(buffer, n, f);
  }
  char **lines = (char **)malloc((*numLines) * sizeof(char *));
  rewind(f);
  line = fgets(buffer, n, f);
  int currentLine = 0;
  while (line != NULL)
  {
    int lineLen = strlen(line);
    lines[currentLine] = (char *)malloc(lineLen * sizeof(char) + 1);
    strcpy(lines[currentLine], line);
    // remove newline character at the end of each line
    if (lines[currentLine][lineLen - 1] == '\n')
    {
      lines[currentLine][lineLen - 1] = '\0';
    }
    currentLine++;
    line = fgets(buffer, n, f);
  }
  return lines;
}

/**
 * read doubles from a single string and return as an array
 */
double *readdoubles(char *str, int *numDoubles)
{
  char *s1 = (char *)malloc((strlen(str) + 1) * sizeof(char));
  char *s2 = (char *)malloc((strlen(str) + 1) * sizeof(char));
  strcpy(s1, str);
  strcpy(s2, str);
  *numDoubles = 0;
  char *token = strtok(s1, " ");
  while (token != NULL)
  {
    (*numDoubles)++;
    token = strtok(NULL, " ");
  }
  double *doubles = (double *)malloc((*numDoubles) * sizeof(double));
  int i = 0;
  token = strtok(s2, " ");
  while (token != NULL)
  {
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
int *readints(char *str, int *numInts)
{
  double *doubles = readdoubles(str, numInts);
  int *ints = (int *)malloc((*numInts) * sizeof(int));
  for (int i = 0; i < *numInts; i++)
  {
    ints[i] = (int)doubles[i];
  }
  free(doubles);
  return ints;
}

/**
 * print an array of integers
 */
void printArray(int *array, int size)
{
  printf("{ ");
  for (int i = 0; i < size; i++)
  {
    printf("%d", array[i]);
    if (i < size - 1)
      printf(", ");
  }
  printf(" }\n");
}

int main(int argc, char **argv)
{
  int sum = 0;
  int height = 6;
  int width = 50;
  bool screen[6][50] = {{false}};
  char *filename = "e.txt";
  if (argc == 2)
  {
    filename = argv[1];
  }
  int numLines;
  char **lines = getfilelines(filename, &numLines);
  if (lines == NULL)
  {
    printf("couldn't read the file dumbass\n");
    exit(1);
  }
  printf("SET TO: %s\n", filename);
  for (int i = 0; i < numLines; i++)
  {
    char *line = lines[i];
    int lineLen = strlen(line);
    if (line[1] == 'e')
    {
      // rect
      for (int row = 0; row < atoi(line + (lineLen - 1)); row++)
      {
        for (int col = 0; col < atoi(line + (lineLen - 4)); col++)
        {
          screen[row][col] = true;
        }
      }
    }
    else if (line[7] == 'r')
    {
      for (int j = 0; j < atoi(line + (lineLen - 2)); j++)
      {
        int row = atoi(line + 13);
        bool *screenRow = screen[row];
        bool prevState = false;
        bool temp = false;
        prevState = screenRow[0];
        for (int col = 1; col < width; col++)
        {
          temp = screenRow[col];
          screenRow[col] = prevState;
          prevState = temp;
        }
        screenRow[0] = prevState;
      }
    }
    else
    {
      for (int j = 0; j < atoi(line + (lineLen - 2)); j++)
      {
        int col = atoi(line + 16);
        bool prevState = screen[0][col];
        bool temp = false;
        for (int row = 1; row < height; row++)
        {
          temp = screen[row][col];
          screen[row][col] = prevState;
          prevState = temp;
        }
        screen[0][col] = prevState;
      }
    }
  }
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      if (screen[row][col])
      {
        sum++;
        printf("#");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("%d\n", sum);
  return 0;
}

// 50
// 35
// 70