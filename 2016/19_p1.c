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

const int elfCount = 3012210;
int elvesDown = 0;
int elves[3012210] = {1};

int main(int argc, char **argv)
{
  for (int i = 0; i < elfCount; i++)
  {
    elves[i] = 1;
  }
  while (true)
  {
    for (int i = 0; i < elfCount; i++)
    {
      int srcElf = elves[i];
      if (srcElf != 0)
      {
        int destElf = 0;
        int destElfIndex;
        int j = 0;
        while (destElf == 0)
        {
          destElfIndex = (i + j + 1) % elfCount;
          if (destElfIndex == i)
          {
            printf("ELF: %d\n", i + 1);
            exit(0);
          }
          destElf = elves[destElfIndex];
          j++;
        }
        srcElf += destElf;
        elves[destElfIndex] = 0;
        elvesDown++;
      }
    }
  }
  return 0;
}