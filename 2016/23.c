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
  char delim[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *token = strtok(s1, delim);
  while (token != NULL)
  {
    (*numDoubles)++;
    token = strtok(NULL, delim);
  }
  double *doubles = (double *)malloc((*numDoubles) * sizeof(double));
  int i = 0;
  token = strtok(s2, delim);
  while (token != NULL)
  {
    doubles[i] = atof(token);
    i++;
    token = strtok(NULL, delim);
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

int registers[4] = {5, 0, 0, 0};

int main(int argc, char **argv)
{
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
  int numInts;
  for (int i = 0; i < numLines; i++)
  {
    char *line = lines[i];
    int lineLen = strlen(line);
    char c = line[0];
    if (c == 'c')
    {
      int outIndex = line[lineLen - 1] - 97;
      int *value = readints(line, &numInts);
      if (numInts == 1)
      {
        registers[outIndex] = value[0];
        free(value);
      }
      else
      {
        int srcIndex = line[lineLen - 3] - 97;
        registers[outIndex] = registers[srcIndex];
      }
    }
    else if (c == 'i')
    {
      int outIndex = line[lineLen - 1] - 97;
      registers[outIndex]++;
    }
    else if (c == 'd')
    {
      int outIndex = line[lineLen - 1] - 97;
      registers[outIndex]--;
    }
    else if (c == 'j')
    {
      int *value = readints(line, &numInts);
      if (numInts == 2)
      {
        if (value[0] != 0)
        {
          i += value[1] - 1;
        }
      }
      else
      {
        if (line[4] != 'a' && line[4] != 'b' && line[4] != 'c' && line[4] != 'd')
        {
          int checkIndex = line[lineLen - 1] - 97;
          if (value[0] != 0)
          {
            i += registers[checkIndex] - 1;
          }
        }
        else
        {
          int checkIndex = line[4] - 97;
          if (registers[checkIndex] != 0)
          {
            i += value[0] - 1;
          }
        }
      }
      free(value);
    }
    else if (c == 't')
    {
      int amt;
      if (line[4] == 'a')
      {
        amt = registers[0];
      }
      else if (line[4] == 'b')
      {
        amt = registers[1];
      }
      else if (line[4] == 'c')
      {
        amt = registers[2];
      }
      else if (line[4] == 'd')
      {
        amt = registers[3];
      }
      else
      {
        amt = atoi(line + 4);
      }
      if (i + amt < numLines)
      {
        char *tLine = lines[i + amt];
        char tc = tLine[0];
        if (tc == 'i')
        {
          tLine[0] = 'd';
          tLine[1] = 'e';
          tLine[2] = 'c';
        }
        else if (tc == 'd' || tc == 't')
        {
          tLine[0] = 'i';
          tLine[1] = 'n';
          tLine[2] = 'c';
        }
        else if (tc == 'j')
        {
          tLine[0] = 'c';
          tLine[1] = 'p';
          tLine[2] = 'y';
        }
        else
        {
          tLine[0] = 'j';
          tLine[1] = 'n';
          tLine[2] = 'z';
        }
      }
    }
  }
  printf("%d\n", registers[0]);
  return 0;
}

// 9227663 HIGH