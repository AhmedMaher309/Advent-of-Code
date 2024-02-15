#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

void getNums(char *str) {
  regex_t redRegex, blueRegex, greenRegex, IDRegex;
  char redPattern[] = "\\d+\\sred";
  char bluePattern[] = "\\d+\\sblue";
  char greenPattern[] = "\\d+\\sgreen";
  regmatch_t redMatch[2];

  int retred = regcomp(&redRegex, redPattern, 0);
  int retblue = regcomp(&blueRegex, bluePattern, 0);
  int retgreen = regcomp(&greenRegex, greenPattern, 0);

  retred = regexec(&redRegex, str, 2, redMatch, 0);
  if (retred == 0) {
    char *substring = "";
    if (redMatch[1].rm_so != -1) {

      // Extract the matched substring
      int len = redMatch[1].rm_eo - redMatch[1].rm_so;
      substring = (char *)malloc(len + 1);
      strncpy(substring, str + redMatch[1].rm_so, len);
      substring[len] = '\0';
    }
    printf("Matched substring: %s\n", substring);
  } else if (retred == REG_NOMATCH)
    printf("No match found\n");
}
void extractNumbersWithRed(char *str) {
  regex_t regex;
  regmatch_t match[2]; // Array to store matched substring and its position
  int reti;

  // Compile the regular expression
  reti =
      regcomp(&regex, "\\b[0-9]+\\sred\\b",
              REG_EXTENDED); // Match numbers followed by space and then "red"
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return;
  }

  // Execute the regular expression
  while (regexec(&regex, str, 2, match, 0) == 0) {
    // Match found
    char *substring = NULL;
    if (match[0].rm_so != -1) {
      // Extract the matched substring
      int len = match[0].rm_eo - match[0].rm_so;
      substring = (char *)malloc(len + 1);
      if (substring == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
      }
      strncpy(substring, str + match[0].rm_so, len);
      substring[len] = '\0';
    }
    printf("Matched substring: %s\n", substring);
    // Move to the next character after the matched substring
    str += match[0].rm_eo;
    // Remember to free the allocated memory
    free(substring);
  }

  // Free the memory allocated for the compiled regular expression
  regfree(&regex);
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
    extractNumbersWithRed(str);
  }

  fclose(fp);
  return EXIT_SUCCESS;
}
