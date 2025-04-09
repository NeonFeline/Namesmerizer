#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/anyascii.h"
#include "./src/utf8.h"
#include "./src/letter_case.h"
#include <assert.h>

void test___convert_to_uppercase(){
  assert(convert_to_uppercase('a') == 'A');
  assert(convert_to_uppercase('b') == 'B');
  assert(convert_to_uppercase('c') == 'C');
  assert(convert_to_uppercase('k') == 'K');
  assert(convert_to_uppercase('f') == 'F');
  assert(convert_to_uppercase('z') == 'Z');

  printf("Convert to uppercase tests passed!\n");
}

void test___convert_to_lowercase(){
  assert(convert_to_lowercase('A') == 'a');
  assert(convert_to_lowercase('B') == 'b');
  assert(convert_to_lowercase('C') == 'c');
  assert(convert_to_lowercase('K') == 'k');
  assert(convert_to_lowercase('P') == 'p');
  assert(convert_to_lowercase('Z') == 'z');

  printf("Convert to lowercase tests passed!\n");
}

void test___lowercase_letters_and_convert_first_one_to_uppercase_inplace(){
  char buffer1[256] = "ILoveFerrets";
  lowercase_letters_and_convert_first_one_to_uppercase_inplace(buffer1);
  assert(strcmp(buffer1, "Iloveferrets") == 0);

  char buffer2[256] = "taijfdsnASDERsjdaswSFEEW";
  lowercase_letters_and_convert_first_one_to_uppercase_inplace(buffer2);
  assert(strcmp(buffer2, "Taijfdsnasdersjdaswsfeew") == 0);

  char buffer3[256] = "I AM32 ON3 TOP4 OF 23THE WORLD!!!@$#!$!";
  lowercase_letters_and_convert_first_one_to_uppercase_inplace(buffer3);
  assert(strcmp(buffer3, "I am32 on3 top4 of 23the world!!!@$#!$!") == 0);


  char buffer4[256] = "I AM32 ON3 TOP4 OF 23THE WORLD!!!@$#!$!";
  lowercase_letters_and_convert_first_one_to_uppercase_inplace(buffer4);
  assert(strcmp(buffer4, "I am32 on3 top4 of 23tHe world!!!@$#!$!") != 0);

  printf("Convert to lowercase letters and convert first one to uppercase inplace tests passed!\n");
}


int main(){
  test___convert_to_uppercase();
  test___convert_to_lowercase();
  test___lowercase_letters_and_convert_first_one_to_uppercase_inplace();
}
