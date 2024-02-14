#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

char * allToDigits(char * str){
  char* digitMap[] = {
        "one", "1",
        "two", "2",
        "three", "3",
        "four", "4",
        "five", "5",
        "six", "6",
        "seven", "7",
        "eight", "8",
        "nine", "9"
    };
  int numMappings = sizeof(digitMap) / sizeof(*digitMap);
  size_t inputLength = strlen(str);
  char* result = (char*)malloc((inputLength + 1) * sizeof(char));
  if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
  }
  result[0] = '\0';
  char * ptr = str;

  while (*ptr != '\0') {
        int foundMapping = 0;
        for (int j = 0; j < numMappings; j += 2) {
            char* match = strstr(ptr, digitMap[j]);
            if (match == ptr) {
                strcat(result, digitMap[j + 1]);
                foundMapping = 1;
                ptr += strlen(digitMap[j]);
                break;
            }
        }
        if (!foundMapping) {
            strncat(result, ptr, 1);
            ptr++;
        }
    }
    return result;

} 

char* extractNums(char * str){
  size_t inputLength = strlen(str);
  char* result = (char*)malloc((inputLength + 1) * sizeof(char));
  for(int i = 0; i < strlen(str); i++){
    if(isdigit(str[i])){
      char temp[2];
      temp[0] = str[i];
      temp[1] = '\0';
      strcat(result, temp);
    }
  }
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
     char* str = line;
     char * string  = allToDigits(str);
     char * nums = extractNums(string);
     int smallSum = ((nums[0] - '0') * 10) + (nums[strlen(nums) - 1] - '0');
     totalSum += smallSum;
    }


  printf("Final sum is %d\n", totalSum);
  fclose(fp);
  return EXIT_SUCCESS;
}
