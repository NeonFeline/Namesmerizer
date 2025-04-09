#include "letter_case.h"

char convert_to_uppercase(char character){
  // If the current character is a lowercase alphabet
  if ((character >= 'a') && (character <= 'z'))
  {
    character = character - ('a' - 'A');
  }

   return character;
}

char convert_to_lowercase(char character){
  // If the current character is a uppercase alphabet
  if ((character >= 'A') && (character <= 'Z'))
  {
    character = character + ('a' - 'A');
  }

   return character;
}

void lowercase_letters_and_convert_first_one_to_uppercase_inplace(char *word){
  for(char * t = word; *t != '\0'; t++){
    *t = convert_to_lowercase(*t);
  }

  word[0] = convert_to_uppercase(word[0]);
}
