#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <algorithm>

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

using namespace std;

string pass = "fbgdceah";

void swapPos(int i1, int i2)
{
  char c1 = pass.at(i1);
  char c2 = pass.at(i2);
  pass[i1] = c2;
  pass[i2] = c1;
}

void swap(char c1, char c2)
{
  swapPos(pass.find(c1), pass.find(c2));
}

void reversePass(int start, int end)
{
  reverse(pass.begin() + start, pass.begin() + end + 1);
}

void rotate(bool right, int times)
{
  for (int i = 0; i < times; i++)
  {
    if (!right)
    {
      pass.insert(0, &pass.back());
      pass.pop_back();
    }
    else
    {
      pass.append(1, pass.at(0));
      pass.erase(0, 1);
    }
  }
}

void movePass(int i2, int i1)
{
  char c = pass.at(i1);
  pass.erase(i1, 1);
  pass.insert(i2, &c);
}

void rotatePos(char c1)
{
  int i = pass.find(c1);
  int rot = i / 2 + (i % 2 == 1 || i == 0 ? 1 : 5);
  rotate(true, rot);
}

int main(int argc, char **argv)
{
  cout << pass << endl;
  char *filename = "e.txt";
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
  for (int i = numLines - 1; i >= 0; i--)
  {
    char *line = lines[i];
    int lineLen = strlen(line);
    if (line[0] == 's')
    {
      if (line[5] == 'l')
      {
        swap(line[12], line[lineLen - 1]);
      }
      else
      {
        swapPos(atoi(line + 14), atoi(line + lineLen - 1));
      }
    }
    else if (line[2] == 't')
    {
      if (line[7] == 'b')
      {
        rotatePos(line[lineLen - 1]);
      }
      else
      {
        rotate((line[7] == 'r'), atoi(line + lineLen - 7));
      }
    }
    else if (line[0] == 'r')
    {
      reversePass(atoi(line + 18), atoi(line + lineLen - 1));
    }
    else
    {
      movePass(atoi(line + 14), atoi(line + lineLen - 1));
    }
    cout << pass << endl;
  }

  return 0;
}

// chbdgaef
// efghdabc