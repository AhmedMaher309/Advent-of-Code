#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

char *twodigits(char *str) {
  char *ptr = str;
  char firstdigit = '\0';
  char lastdigit = '\0';
  int count = 0;
  char *digitMap[] = {"one",   "1", "two",   "2", "three", "3",
                      "four",  "4", "five",  "5", "six",   "6",
                      "seven", "7", "eight", "8", "nine",  "9"};

  while (*ptr != '\0') {
    if (isdigit(*ptr) && count == 0) {
      firstdigit = *ptr;
      lastdigit = firstdigit;
      count++;
    } else if (isdigit(*ptr) && count != 0) {
      lastdigit = *ptr;
    } else {
      for (int i = 0; i < 18; i += 2) {
        char *match = strstr(ptr, digitMap[i]);
        if (match == ptr) {
          if (count == 0) {
            firstdigit = *digitMap[i + 1];
            lastdigit = *digitMap[i + 1];
            count++;
          } else {
            lastdigit = *digitMap[i + 1];
          }
        }
      }
    }
    ptr++;
  }
  char *result = (char *)malloc(2 * sizeof(char));
  result[0] = firstdigit;
  result[1] = lastdigit;

  return result;
}

int main(void) {
  int totalSum = 0;
  char *filename = "input.txt";
  FILE *fp = fopen(filename, "r");

  char line[MAX_LINE_LENGTH];

  if (fp == NULL) {
    printf("Error: could not open input file\n");
    return EXIT_FAILURE;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    char *str = line;
    char *result = twodigits(str);
    int sum = ((result[0] -'0') * 10) + (result[1] - '0');
    totalSum += sum;
  }

  printf("Final sum is %d\n", totalSum);
  fclose(fp);
  return EXIT_SUCCESS;
}
