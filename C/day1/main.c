#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main(void) {
  int totalSum = 0;
  char *filename = "input.txt";
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Error: could not open input file\n");
    return EXIT_FAILURE;
  }
  printf("Reading the file...\n");
  char ch;
  int lineNumber = 0;
  int sum;
  char *digits[] = {"one", "two",   "three", "four", "five",
                    "six", "seven", "eight", "nine"};
  while ((ch = fgetc(fp)) != EOF) {
    int count = 0;
    char lastNum = '\0';
    while (ch != '\n') {
      if (isdigit(ch)) {
        if (count == 0) {
          sum = ch - '0';
        }
        count++;
        lastNum = ch;
      }
      ch = fgetc(fp);
    }
    if (count > 0) {
      sum = sum * 10 + (lastNum - '0');
      totalSum += sum;
      lineNumber++;
      printf("%d and line is %d\n", sum, lineNumber);
      ch = fgetc(fp);
    }
  }

  printf("Final sum is %d\n", totalSum);
  fclose(fp);
  return EXIT_SUCCESS;
}
