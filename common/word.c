/*
 * word.c
 *
 * Chahak Goyal, Spring 2021
 */

#include <string.h>
#include <ctype.h>

/****** normalizeWord *******/
/* takes string as parameter
 * converts the words to lowercase letters
 * returns lower case string
 */
char* normalizeWord(char* word) {  
  for (int i = 0; i < strlen(word); i++) {
    word[i] = (char)(tolower((int)word[i]));
  }
  return word;
}
