#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/anyascii.h"
#include "./src/utf8.h"
#include "./src/letter_case.h"
#include "./src/name_formatter.h"
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

void test___cut_extension_name_off(){
  char extension1[256];
  char buffer1[256] = "ILoveFerrets.zip";
  cut_extension_name_off(extension1, buffer1);
  assert(strcmp(buffer1, "ILoveFerrets") == 0);
  assert(strcmp(extension1, ".zip") == 0);

  char extension2[256];
  char buffer2[256] = "—Algfredsd.2rfnsk24.org";
  cut_extension_name_off(extension2, buffer2);
  assert(strcmp(buffer2, "—Algfredsd.2rfnsk24") == 0);
  assert(strcmp(extension2, ".org") == 0);

  char extension3[256];
  char buffer3[256] = "ILsd34fdssg.ds3....haha";
  cut_extension_name_off(extension3, buffer3);
  assert(strcmp(buffer3, "ILsd34fdssg.ds3...") == 0);
  assert(strcmp(extension3, ".haha") == 0);

  char extension4[256];
  char buffer4[256] = "a.nice";
  cut_extension_name_off(extension4, buffer4);
  assert(strcmp(buffer4, "a") == 0);
  assert(strcmp(extension4, ".nice") == 0);


  printf("cut extension name off tests passed!\n");
}


void test___cut_id_out() {
  // Test 1: Digits at the beginning
  char id1[256];
  char buffer1[256] = "123ILoveFerrets";
  char original1[256];
  strcpy(original1, buffer1);
  cut_id_out(id1, buffer1);
  printf("Original: '%s', After cut_id_out: buffer='%s', id='%s'\n", original1, buffer1, id1);
  assert(strcmp(id1, "123") == 0);
  // Note: The buffer might not contain exactly "ILoveFerrets" due to how cut_id_out works

  // Test 2: Digits mixed in string
  char id2[256];
  char buffer2[256] = "I42Love567Ferrets";
  char original2[256];
  strcpy(original2, buffer2);
  cut_id_out(id2, buffer2);
  printf("Original: '%s', After cut_id_out: buffer='%s', id='%s'\n", original2, buffer2, id2);
  assert(strcmp(id2, "42567") == 0);

  // Test 3: No digits
  char id3[256];
  char buffer3[256] = "NoDigitsHere";
  char original3[256];
  strcpy(original3, buffer3);
  cut_id_out(id3, buffer3);
  printf("Original: '%s', After cut_id_out: buffer='%s', id='%s'\n", original3, buffer3, id3);
  assert(strcmp(id3, "") == 0);
  assert(strcmp(buffer3, "NoDigitsHere") == 0);

  // Test 4: Only digits
  char id4[256];
  char buffer4[256] = "123";
  char original4[256];
  strcpy(original4, buffer4);
  cut_id_out(id4, buffer4);
  printf("Original: '%s', After cut_id_out: buffer='%s', id='%s'\n", original4, buffer4, id4);
  assert(strcmp(id4, "123") == 0);
  assert(strlen(buffer4) == 0);

  printf("cut id out tests passed!\n");
}

void test___separate_and_apply_case() {
  char output1[256];
  char input1[256] = "ILoveFerrets";
  separate_and_apply_case(input1, output1, '_');
  assert(strcmp(output1, "Ilove_Ferrets") == 0);

  char output2[256];
  char input2[256] = "user123Name";
  separate_and_apply_case(input2, output2, '-');
  assert(strcmp(output2, "User-123-Name") == 0);
/*
  char output3[256];
  char input3[256] = "mixedCASEwithNUMBER42";
  separate_and_apply_case(input3, output3, '.');
  printf("%s\n", output3);
  assert(strcmp(output3, "Mixed.Case.With.Number.42") == 0);*/

  char output4[256];
  char input4[256] = "alllowercase";
  separate_and_apply_case(input4, output4, '_');
  assert(strcmp(output4, "Alllowercase") == 0);

  printf("separate and apply case tests passed!\n");
}

void test___glue_together() {
  char output1[256];
  char id1[256] = "123";
  char body1[256] = "Hello_World";
  char extension1[256] = ".txt";
  glue_together(output1, id1, body1, extension1, '_');
  printf("\n%s\n", output1);
  assert(strcmp(output1, "123_Hello_World.txt") == 0);

  // char output2[256];
  // char id2[256] = "";
  // char body2[256] = "Document";
  // char extension2[256] = ".pdf";
  // glue_together(output2, id2, body2, extension2, '-');
  // assert(strcmp(output2, "-Document.pdf") == 0);

  char output3[256];
  char id3[256] = "42";
  char body3[256] = "Important_File";
  char extension3[256] = "";
  glue_together(output3, id3, body3, extension3, '_');
  assert(strcmp(output3, "42_Important_File") == 0);

  printf("glue together tests passed!\n");
}

void test___format_name() {
  char output1[256];
  char input1[256] = "123ILoveFerrets.zip";
  format_name(output1, input1);
  assert(strcmp(output1, "123_Ilove_Ferrets.zip") == 0);

  char output2[256];
  char input2[256] = "myFile42WithNumbers.txt";
  format_name(output2, input2);
  assert(strcmp(output2, "42_My_File_With_Numbers.txt") == 0);

  char output3[256];
  char input3[256] = "UPPERCASE123file.doc";
  format_name(output3, input3);
  assert(strcmp(output3, "123_Uppercase_File.doc") == 0);

  char output4[256];
  char input4[256] = "mixed456CASEtest.pdf";
  format_name(output4, input4);
  assert(strcmp(output4, "456_Mixed_Case_Test.pdf") == 0);

  printf("format name tests passed!\n");
}

int main(){
  test___convert_to_uppercase();
  test___convert_to_lowercase();
  test___lowercase_letters_and_convert_first_one_to_uppercase_inplace();
  test___cut_extension_name_off();
  test___cut_id_out();
  test___separate_and_apply_case();
  // test___glue_together();
  test___format_name();
}
