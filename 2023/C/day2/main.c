#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

void getNums(char* str){
}

int main(void) {
  char *filename = "input.txt";
  FILE *fp = fopen(filename, "r");

  char line[MAX_LINE_LENGTH];

  if (fp == NULL) {
    printf("Error: could not open input file\n");
    return EXIT_FAILURE;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    char *str = line;
    getNums(str);
  }

  fclose(fp);
  return EXIT_SUCCESS;
}
