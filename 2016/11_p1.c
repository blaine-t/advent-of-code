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

// Generators 0-4
// Microchips 5-9
// Matching combo if M-G = 5

bool floors[4][10] = {{true, true, true, true, true, false, false, true, true, true}, {false, false, false, false, false, true, true, false, false, false}, {false}, {false}};
const bool success[10] = {true, true, true, true, true, true, true, true, true, true};
int currFloor = 1;
int hand1;
int hand2;
int steps = 0;

bool moveFloor(bool up)
{
  if (up)
  {
    currFloor++;
  }
  else
  {
    currFloor--;
  }
  if (currFloor == 0)
  {
    currFloor = 1;
    return false;
  }
  else if (currFloor == 5)
  {
    currFloor = 4;
    return false;
  }
  return true;
}

void placeFloor(int floorNum)
{
  bool *floor = floors[floorNum];
  if (hand1 != NULL)
  {
    floor[hand1] = true;
  }
  if (hand2 != NULL)
  {
    floor[hand2] = true;
  }
}

void resetFloor(int floorNum)
{
  bool *floor = floors[floorNum];
  if (hand1 != NULL)
  {
    floor[hand1] = false;
  }
  if (hand2 != NULL)
  {
    floor[hand2] = false;
  }
}

bool checkFloor(int floorNum)
{
  bool *floor = floors[floorNum];
  placeFloor(floorNum);
  for (int i = 5; i < 10; i++)
  {
    if (floor[i])
    {
      if (!floor[i - 5])
      {
        if (floor[0] || floor[1] || floor[2] || floor[3] || floor[4])
        {
          resetFloor(floorNum);
          return false;
        }
      }
    }
  }
  resetFloor(floorNum);
  return true;
}

void printFloors()
{
  for (int i = 0; i < 4; i++)
  {
    bool *floor = floors[i];
    for (int j = 0; j < 10; j++)
    {
      if (floor[j])
      {
        printf("X");
      }
      else
      {
        printf(" ");
      }
      printf(" ");
    }
    printf("\n");
  }
}

int main(int argc, char **argv)
{
  printFloors();
  while (floors[4] != success)
  {
    return 0;
  }
}