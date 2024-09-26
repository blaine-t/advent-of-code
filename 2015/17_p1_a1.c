#include <limits.h>
#include <openssl/evp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int value;
  struct node *next;
};

struct queue {
  struct node *head;
  struct node *tail;
  int size;
};

struct queue *createQueue() {
  struct queue *q = (struct queue *)malloc(sizeof(struct queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

int enqueue(struct queue *q, int value) {
  struct node *n = (struct node *)malloc(sizeof(struct node));
  if (n == NULL) return q->size;

  n->value = value;
  n->next = NULL;
  if (q->head == NULL) {
    q->head = n;
    q->tail = n;
    return q->size;
  }
  q->tail->next = n;
  q->tail = n;
  q->size += 1;
  return q->size;
}

int dequeue(struct queue *q) {
  struct node *tmp = q->head;
  int value = tmp->value;
  q->head = q->head->next;
  free(tmp);
  q->size -= 1;
  return value;
}

void freeQueue(struct queue *q) {
  if (q == NULL) return;

  while (q->head != NULL) {
    struct node *tmp = q->head;
    q->head = q->head->next;
    free(tmp);
  }

  free(q);
}

/**
 * read doubles from a single string and return as an array
 */
double *readdoubles(char *str, int *numDoubles) {
  char *s1 = (char *)malloc((strlen(str) + 1) * sizeof(char));
  char *s2 = (char *)malloc((strlen(str) + 1) * sizeof(char));
  strcpy(s1, str);
  strcpy(s2, str);
  *numDoubles = 0;
  char delim[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *token = strtok(s1, delim);
  while (token != NULL) {
    (*numDoubles)++;
    token = strtok(NULL, delim);
  }
  double *doubles = (double *)malloc((*numDoubles) * sizeof(double));
  int i = 0;
  token = strtok(s2, delim);
  while (token != NULL) {
    doubles[i] = atof(token);
    i++;
    token = strtok(NULL, delim);
  }
  free(s1);
  free(s2);
  return doubles;
}

int ten[10] = {1,      10,      100,      1000,      10000,
               100000, 1000000, 10000000, 100000000, 1000000000};

/**
 * read integers from a single string and return as an array
 */
int *readints(char *str, int *numInts, bool negative) {
  *numInts = 0;
  int strLen = strlen(str);
  int currNum = 0;
  int currNumLen = 0;
  bool prevNum = false;
  for (int i = 0; i < strLen; i++) {
    char c = str[i];
    int index = c - '0';
    if (index >= 0 && index <= 9) {
      if (!prevNum) {
        prevNum = true;
        (*numInts)++;
      }
    } else {
      prevNum = false;
    }
  }
  int *ints = (int *)malloc(*numInts * sizeof(int));
  int foundInts = 0;
  for (int i = strLen - 1; i >= 0; i--) {
    char c = str[i];
    int index = c - '0';
    if (index >= 0 && index <= 9) {
      currNum += index * ten[currNumLen++];
    } else if (negative && c == '-' && currNum > 0) {
      currNum *= -1;
    } else if (currNumLen != 0) {
      ints[*numInts - ++foundInts] = currNum;
      currNum = 0, currNumLen = 0;
    }
  }
  if (currNumLen != 0) {
    ints[0] = currNum;
  }
  return ints;
}

/**
 * print an array of integers
 */
void printArray(int *array, int size) {
  printf("{ ");
  for (int i = 0; i < size; i++) {
    printf("%d", array[i]);
    if (i < size - 1) printf(", ");
  }
  printf(" }\n");
}

/**
 * converts an integer to a string
 */
char *itoa(int value, char *result, int base) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result;
  char *ptr1 = result;
  char tmp_char;
  int tmp_value;
  bool is_negative = false;

  if (value < 0 && base == 10) {
    is_negative = true;
    value = -value;
  }

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[tmp_value % base];
  } while (value);

  if (is_negative) {
    *ptr++ = '-';
  }

  *ptr = '\0';

  // Reverse the string
  for (ptr--; ptr1 < ptr; ptr1++, ptr--) {
    tmp_char = *ptr;
    *ptr = *ptr1;
    *ptr1 = tmp_char;
  }

  return result;
}

/**
 * hashes a string to md5
 */
char *md5(char *string) {
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
  for (unsigned int i = 0; i < result_len; i++) {
    sprintf(hash + (i * 2), "%02x", result[i]);
  }

  return hash;
}

#define LINE_LENGTH 1000;

/**
 * gets all lines from a file and returns them as an array of strings
 */
char **getfilelines(char *filename, int *numLines) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  int n = LINE_LENGTH;  // max line length, increase this if it breaks
  char buffer[n];
  char *line = fgets(buffer, n, f);
  *numLines = 0;
  while (line != NULL) {
    (*numLines)++;
    line = fgets(buffer, n, f);
  }
  char **lines = (char **)malloc((*numLines) * sizeof(char *));
  rewind(f);
  line = fgets(buffer, n, f);
  int currentLine = 0;
  while (line != NULL) {
    int lineLen = strlen(line);
    lines[currentLine] = (char *)malloc(lineLen * sizeof(char) + 1);
    strcpy(lines[currentLine], line);
    // remove newline character at the end of each line
    if (lines[currentLine][lineLen - 1] == '\n') {
      lines[currentLine][lineLen - 1] = '\0';
    }
    currentLine++;
    line = fgets(buffer, n, f);
  }
  fclose(f);
  return lines;
}

#define NEGATIVES true;

int jugs[20] = {};
const int liters = 150;
int sum = 0;

int main(int argc, char **argv) {
  char *filename = "i.txt";
  if (argc == 2) {
    filename = argv[1];
  }
  int numLines;
  char **lines = getfilelines(filename, &numLines);
  if (lines == NULL) {
    printf("couldn't read the file\n");
    exit(1);
  }
  printf("SET TO: %s\n", filename);
  for (int i = 0; i < numLines; i++) {
    char *line = lines[i];
    int numChars = strlen(line);
    int numInts = 0;
    int *ints = readints(line, &numInts, true);
    jugs[i] = ints[0];
    free(line);
  }
  free(lines);
  printArray(jugs, 20);
for (int a = 0; a < 20; a++) {
printf("%d\n",a);    
sum += (int)(jugs[a] == liters);
    for (int b = a+1; b < 20; b++) {
      sum += (int)(jugs[a] + jugs[b] == liters);
      for (int c = a+2; c < 20; c++) {
        sum += (int)(jugs[a] + jugs[b] + jugs[c] == liters);
        for (int d = a+3; d < 20; d++) {
          sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] == liters);
          for (int e = a+4; e < 20; e++) {
            sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] == liters);
            for (int f = a+5; f < 20; f++) {
              sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] == liters);
              for (int g = a+6; g < 20; g++) {
                sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] == liters);
                for (int h = a+7; h < 20; h++) {
                  sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] == liters);
                  for (int i = a+8; i < 20; i++) {
                    sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] == liters);
                    for (int j = a+9; j < 20; j++) {
                      sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] == liters);
                      for (int k = a+10; k < 20; k++) {
                        sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] == liters);
                        for (int l = a+11; l < 20; l++) {
                          sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] == liters);
                          for (int m = a+12; m < 20; m++) {
                            sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] == liters);
                            for (int n = a+13; n < 20; n++) {
                              sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] == liters);
                              for (int o = a+14; o < 20; o++) {
                                sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] == liters);
                                for (int p = a+15; p < 20; p++) {
                                  sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] + jugs[p] == liters);
                                  for (int q = a+16; q < 20; q++) {
                                    sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] + jugs[p] + jugs[q] == liters);
                                    for (int r = a+17; r < 20; r++) {
                                      sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] + jugs[p] + jugs[q] + jugs[r] == liters);
                                      for (int s = a+18; s < 20; s++) {
                                        sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] + jugs[p] + jugs[q] + jugs[r] + jugs[s] == liters);
                                        for (int t = a+19; t < 20; t++) {
                                          sum += (int)(jugs[a] + jugs[b] + jugs[c] + jugs[d] + jugs[e] + jugs[f] + jugs[g] + jugs[h] + jugs[i] + jugs[j] + jugs[k] + jugs[l] + jugs[m] + jugs[n] + jugs[o] + jugs[p] + jugs[q] + jugs[r] + jugs[s] + jugs[t] == liters);
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}

// 7
