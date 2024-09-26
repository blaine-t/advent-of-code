#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "md5.h"

char **getfilelines(char *filename, int *numLines) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }
  int n = 1000; // max line length, increase this if it breaks
  char buffer[n];
  char *line = fgets(buffer, n, f);
  *numLines = 0;
  while (line != NULL) {
    (*numLines)++;
    line = fgets(buffer, n, f);
  }
  char **lines = (char **) malloc((*numLines) * sizeof(char *));
  rewind(f);
  line = fgets(buffer, n, f);
  int currentLine = 0;
  while (line != NULL) {
    int lineLen = strlen(line);
    lines[currentLine] = (char *) malloc(lineLen * sizeof(char) + 1);
    strcpy(lines[currentLine], line);
    // remove newline character at the end of each line
    if (lines[currentLine][lineLen-1] == '\n') {
      lines[currentLine][lineLen-1] = '\0';
    }
    currentLine++;
    line = fgets(buffer, n, f);
  }
  return lines;
}

/**
 * read doubles from a single string and return as an array
 */
double *readdoubles(char *str, int *numDoubles) {
    char *s1 = (char *) malloc((strlen(str)+1) * sizeof(char));
    char *s2 = (char *) malloc((strlen(str)+1) * sizeof(char));
    strcpy(s1, str);
    strcpy(s2, str);
    *numDoubles = 0;
    char *token = strtok(s1, " ");
    while (token != NULL) {
        (*numDoubles)++;
        token = strtok(NULL, " ");
    }
    double *doubles = (double *) malloc((*numDoubles) * sizeof(double));
    int i = 0;
    token = strtok(s2, " ");
    while (token != NULL) {
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
int *readints(char *str, int *numInts) {
    double *doubles = readdoubles(str, numInts);
    int *ints = (int *) malloc((*numInts) * sizeof(int));
    for (int i = 0; i < *numInts; i++) {
        ints[i] = (int) doubles[i];
    }
    free(doubles);
    return ints;
}

/**
 * print an array of integers
 */
void printArray(int *array, int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size-1) printf(", ");
    }
    printf(" }\n");
}

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    // Reverse the string
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int main(int argc, char **argv) {
    char input[] = "abc";
    char finalStr[] = "        ";
    int currNum = -1;
    int count = 0;
    while (count < 8) {
        currNum++;
        char result[100];
        itoa(currNum, result, 10);
        char final[100];
        strcpy(final, input);
        strcat(final, result);
        unsigned char finalResult[100];
        md5String(final, finalResult);
        char data[9];
        sprintf(data, "%02x%02x%02x%02x", finalResult[0], finalResult[1], finalResult[2], finalResult[3]);
        int dataLength = strlen(data);
        int passIndex = data[dataLength-3] - 48;
        char passSpot = data[dataLength-2];
        char original[9];
        strcpy(original, data);
        data[dataLength-1] = '\0';
        data[dataLength-2] = '0';
        data[dataLength-3] = '0';
        if(strcmp(data, "0000000") == 0 && passIndex < 8 && passIndex >= 0 && finalStr[passIndex] == ' ') {
            finalStr[passIndex] = passSpot;
            printf(original);
            printf("\n");
            count++;
        }
    }
    printf(finalStr);
    return 0;
}