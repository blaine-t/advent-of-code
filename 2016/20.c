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

long lows[1029] = {0};
long highs[1029] = {0};
int sum = 0;

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
    printf("couldn't read the file\n");
    exit(1);
  }
  printf("SET TO: %s\n", filename);
  for (int i = 0; i < numLines; i++)
  {
    char *line = lines[i];
    char *ptr;
    long low = strtol(line, &ptr, 10);
    lows[i] = low;
    ptr = strchr(line, '-');
    int secondIndex = (int)(ptr - line);
    long high = strtol(line + secondIndex + 1, &ptr, 10);
    highs[i] = high;
  }
  for (long i = 0; i <= 4294967295; i++)
  {
    long newI = -1;
    for (int j = 0; j < 1029; j++)
    {
      if (i >= lows[j] && i <= highs[j])
      {
        if (newI == -1 || newI > highs[j])
        {
          newI = highs[j];
        }
      }
    }
    if (newI == -1)
    {
      sum++;
    }
    else
    {
      i = newI;
    }
  }
  printf("%d\n", sum);
  return 0;
}