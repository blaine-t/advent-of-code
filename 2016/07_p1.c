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

bool abbaCheck(char *str)
{
  if (str[0] != str[1])
  {
    if (str[0] == str[3] && str[1] == str[2])
    {
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv)
{
  int sum = 0;
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
    bool inBracket = false;
    bool good = false;
    for (int j = 0; j < strlen(line) - 3; j++)
    {
      if (line[j + 3] == '[')
      {
        j += 3;
        inBracket = true;
        continue;
      }
      else if (line[j + 3] == ']')
      {
        j += 3;
        inBracket = false;
        continue;
      }
      char abba[4];
      strncpy(abba, line + j, 4);
      if (abbaCheck(abba))
      {
        if (!inBracket)
        {
          good = true;
        }
        else
        {
          good = false;
          break;
        }
      }
    }
    if (good)
    {
      sum++;
    }
  }
  printf("%d\n", sum);
  return 0;
}

// NOT 40
// 167 TOO HIGH
// 118 TOO HIGH