#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <openssl/evp.h>

struct node
{
  int value;
  struct node *next;
};

struct queue
{
  struct node *head;
  struct node *tail;
  int size;
};

struct queue *createQueue()
{
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

int enqueue(struct queue *q, int value)
{
  struct node *n = (struct node *)malloc(sizeof(struct node));
  if (n == NULL)
    return q->size;

  n->value = value;
  n->next = NULL;
  if (q->head == NULL)
  {
    q->head = n;
    q->tail = n;
    return q->size;
  }
  q->tail->next = n;
  q->tail = n;
  q->size += 1;
  return q->size;
}

int dequeue(struct queue *q)
{
  struct node *tmp = q->head;
  int value = tmp->value;
  q->head = q->head->next;
  free(tmp);
  q->size -= 1;
  return value;
}

void freeQueue(struct queue *q)
{
  if (q == NULL)
    return;

  while (q->head != NULL)
  {
    struct node *tmp = q->head;
    q->head = q->head->next;
    free(tmp);
  }

  free(q);
}

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
  fclose(f);
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

int registers[4] = {0, 0, 0, 0};
int lastOutput = -1;
int count = 0;

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
  for (int j = 0; j < 881; j++)
  {
    registers[0] = j;
    lastOutput = -1;
    for (int i = 0; i < numLines; i++)
    {
      // usleep(100000);
      // printf("LINE: %d\n", i);
      // printf("REGISTERS: %d, %d, %d, %d\n", registers[0], registers[1], registers[2], registers[3]);
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
      else if (c == 'o')
      {
        int checkIndex = line[lineLen - 1] - 97;
        if (lastOutput == -1 && (registers[checkIndex] == 1 || registers[checkIndex] == 0))
        {
          lastOutput = registers[checkIndex];
        }
        else if (lastOutput != registers[checkIndex] && (registers[checkIndex] == 1 || registers[checkIndex] == 0))
        {
          lastOutput = registers[checkIndex];
          count++;
          if (count > 5)
          {
            printf("%d HAD COUNT: %d\n", j, count);
          }
        }
        else
        {
          count = 0;
          break;
        }
      }
    }
  }
  return 0;
}

// 881 TOO HIGH
// 400 TOO HIGH