#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

int bots[210][2] = {{0}};
int outputs[21] = {0};
int lowValue = 17;
int highValue = 61;

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

void giveBot(int bot, int value)
{
  if (bots[bot][0] != 0)
  {
    if (bots[bot][0] > value)
    {
      bots[bot][1] = bots[bot][0];
      bots[bot][0] = value;
    }
    else
    {
      bots[bot][1] = value;
    }
  }
  else
  {
    bots[bot][0] = value;
  }
}

void checkBot(int bot)
{
  if (bots[bot][0] == lowValue && bots[bot][1] == highValue)
  {
    printf("BOT: %d\n", bot);
    exit(0);
  }
}

void checkOutputs()
{
  if (outputs[0] != 0 && outputs[1] != 0 && outputs[2] != 0)
  {
    printf("VALUE: %d\n", outputs[0] * outputs[1] * outputs[2]);
    exit(0);
  }
}

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
  // MY CODE

  for (int i = 0; i < numLines; i++)
  {
    char *line = lines[i];
    char c = line[0];
    if (c == 'v')
    {
      int numInts = 0;
      int *ints = readints(line, &numInts);
      int value = ints[0];
      int bot = ints[1];
      giveBot(bot, value);
    }
  }
  const char delim[] = " ";
  while (true)
  {
    for (int i = 0; i < numLines; i++)
    {
      char *line = lines[i];
      char *lineCopy = (char *)malloc((strlen(line) + 1) * sizeof(char));
      strcpy(lineCopy, line);
      char c = line[0];
      if (c == 'b')
      {
        int numInts = 0;
        int *ints = readints(line, &numInts);
        int srcBot = ints[0];
        if (bots[srcBot][0] == 0 || bots[srcBot][1] == 0)
        {
          continue;
        }
        char destination;
        strtok(lineCopy, delim);
        strtok(NULL, delim);
        strtok(NULL, delim);
        strtok(NULL, delim);
        strtok(NULL, delim);
        destination = strtok(NULL, delim)[0];
        int value = bots[srcBot][0];
        if (destination == 'b')
        {
          int lowDestBot = ints[1];
          giveBot(lowDestBot, value);
        }
        else
        {
          int output = ints[1];
          outputs[output] = value;
          checkOutputs();
        }
        bots[srcBot][0] = 0;
        strtok(NULL, delim);
        strtok(NULL, delim);
        strtok(NULL, delim);
        strtok(NULL, delim);
        destination = strtok(NULL, delim)[0];
        value = bots[srcBot][1];
        if (destination == 'b')
        {
          int highDestBot = ints[2];
          giveBot(highDestBot, value);
        }
        else
        {
          int output = ints[2];
          outputs[output] = value;
          checkOutputs();
        }
        bots[srcBot][1] = 0;
      }
    }
  }
  return 0;
}