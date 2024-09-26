#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <openssl/evp.h>

/**
 * gets all lines from a file and returns them as an array of strings
 */
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
  char delim[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ=;,.";
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

/**
 * converts an integer to a string
 */
char *itoa(int value, char *result, int base)
{
  if (base < 2 || base > 36)
  {
    *result = '\0';
    return result;
  }

  char *ptr = result;
  char *ptr1 = result;
  char tmp_char;
  int tmp_value;
  bool is_negative = false;

  if (value < 0 && base == 10)
  {
    is_negative = true;
    value = -value;
  }

  do
  {
    tmp_value = value;
    value /= base;
    *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[tmp_value % base];
  } while (value);

  if (is_negative)
  {
    *ptr++ = '-';
  }

  *ptr = '\0';

  // Reverse the string
  for (ptr--; ptr1 < ptr; ptr1++, ptr--)
  {
    tmp_char = *ptr;
    *ptr = *ptr1;
    *ptr1 = tmp_char;
  }

  return result;
}

/**
 * hashes a string to md5
 */
char *md5(char *string)
{
  EVP_MD_CTX *mdctx;
  unsigned char result[EVP_MAX_MD_SIZE];
  unsigned int result_len = EVP_MAX_MD_SIZE;

  mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
  EVP_DigestUpdate(mdctx, string, strlen(string));
  EVP_DigestFinal_ex(mdctx, result, &result_len);
  EVP_MD_CTX_free(mdctx);

  char *hash = (char *)malloc((result_len * 2) + 1);
  hash[result_len * 2] = '\0';
  for (unsigned int i = 0; i < result_len; i++)
  {
    sprintf(hash + (i * 2), "%02x", result[i]);
  }

  return hash;
}

// char *filename = "e.txt";
// bool map[3][9] = {{false}};
// int locs[5][2] = {{0}};
// int dist[5][5] = {{0}};
// const int rows = 3;
// const int cols = 9;
// const int locLen = 5;

char *filename = "i.txt";
bool map[39][183] = {{false}};
int locs[8][2] = {{0}};
int dist[8][8] = {{0}};
const int rows = 39;
const int cols = 183;
const int locLen = 8;

int findShortestPath(int *remainingInts, int currentSteps, int lastLocation)
{
  bool touched = false;
  int lowestSteps = INT_MAX;
  int previousSteps[8] = {0};
  for (int i = 0; i < 8; i++)
  {
    if (remainingInts[i] != 0)
    {
      touched = true;
      int remainingIntsMinusOne[8] = {0};
      memcpy(remainingIntsMinusOne, remainingInts, sizeof(int) * 8);
      remainingIntsMinusOne[i] = 0;
      previousSteps[i] = findShortestPath(remainingIntsMinusOne, currentSteps + dist[lastLocation][remainingInts[i]], remainingInts[i]);
    }
  }
  if (!touched)
  {
    return currentSteps + dist[lastLocation][0];
  }
  for (int i = 0; i < 8; i++)
  {
    if (previousSteps[i] < lowestSteps && previousSteps[i] != 0)
    {
      lowestSteps = previousSteps[i];
    }
  }
  return lowestSteps;
}

int main(int argc, char **argv)
{
  if (argc == 2)
  {
    filename = argv[1];
  }
  int numLines;
  char **lines = getfilelines(filename, &numLines);
  if (lines == NULL)
  {
    printf("couldn't read the file\n");
    exit(1);
  }
  printf("SET TO: %s\n", filename);
  for (int i = 0; i < numLines - 2; i++)
  {
    char *line = lines[i + 1];
    int numChars = strlen(line);
    for (int j = 0; j < numChars - 2; j++)
    {
      char c = line[j + 1];
      if (c == '#')
      {
        map[i][j] = false;
      }
      else
      {
        map[i][j] = true;
        if (c != '.')
        {
          int l = c - '0';
          locs[l][0] = i;
          locs[l][1] = j;
        }
      }
    }
  }
  for (int i = 0; i < locLen - 1; i++)
  {
    for (int j = i + 1; j < locLen; j++)
    {
      int startX = locs[i][0];
      int startY = locs[i][1];
      int endX = locs[j][0];
      int endY = locs[j][1];
      int pathCount = 1;
      int steps = 0;
      int(*paths)[2] = (int(*)[2])malloc(sizeof(int[pathCount][2]));
      int(*oldPaths)[2] = (int(*)[2])malloc(sizeof(int[pathCount][2]));
      bool used[39][183] = {{false}};
      bool completed = false;
      paths[0][0] = startX;
      paths[0][1] = startY;
      used[startX][startY] = true;
      while (completed == false)
      {
        free(oldPaths);
        oldPaths = paths;
        paths = (int(*)[2])malloc(sizeof(int[pathCount * 4][2]));
        int oldPathCount = pathCount;
        pathCount = 0;
        steps++;
        for (int k = 0; k < oldPathCount; k++)
        {
          if (completed == true)
          {
            break;
          }
          int initX = oldPaths[k][0];
          int initY = oldPaths[k][1];
          for (int m = 0; m < 4; m++)
          {
            int newX = initX + (m - 1) % 2;
            int newY = initY + (m - 2) % -2;
            if (newX < 0 || newY < 0 || newX >= rows || newY >= cols)
            {
              continue;
            }
            if (map[newX][newY] && !used[newX][newY])
            {
              paths[pathCount][0] = newX;
              paths[pathCount++][1] = newY;
              used[newX][newY] = true;
            }
            if (newX == endX && newY == endY)
            {
              completed = true;
              dist[i][j] = steps;
              dist[j][i] = steps;
              printf("%d TO %d IS %d STEPS\n", i, j, steps);
              break;
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < locLen; i++)
  {
    printArray(dist[i], 8);
  }
  int remainingInts[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  printf("%d\n", findShortestPath(remainingInts, 0, 0));
  return 0;
}

// 588 TOO LOW
// 1304 TOO HIGH