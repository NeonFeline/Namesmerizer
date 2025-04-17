#include "name_formatter.h"
#include "letter_case.h"

#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h> //for debugging

void cut_extension_name_off(char extensionNameBuffer[], char srcString[]){
    int ln = strlen(srcString);
    for (int i=ln-1; i > 0; i--){
        if (srcString[i] == '.'){
            strncpy(extensionNameBuffer, srcString+i, ln-i+1); // +1 for null terminating char
            srcString[i] = '\0';
            break;
        }
    }
}

void cut_id_out(char idBuffer[], char srcString[]){
    int ln = strlen(srcString);
    char srcStringWithoutId[ln+1];
    int currentIdLength = 0;
    for (int i=0; i<ln; i++){
        if (isnumber(srcString[i])){
            idBuffer[currentIdLength] = srcString[i];
            currentIdLength++;
        } 
        else {
            srcStringWithoutId[i-currentIdLength] = srcString[i];
        }
    }
    idBuffer[currentIdLength] = '\0';
    srcStringWithoutId[ln-1-currentIdLength] = '\0';
    strcpy(srcString, srcStringWithoutId);
}

void separate_and_apply_case(char srcString[], char filenameBody[], char delimiter){
    int ln = strlen(srcString);
    char currentWordBuffer[ln+52];
    int currentWordLength = 0;
    filenameBody[0] = '\0'; //because we use strncat further on, we ensure here that the buffer is empty

    for (int i=0; i < ln; i++){
        char c = srcString[i];
        char cNext = srcString[i+1]; // relies on srcString being null-terminated,
                                    // which is enforced by cut_extension_name_off
        if (isalnum(c)) { 
            currentWordBuffer[currentWordLength] = c;
            currentWordLength++;

            bool currentLetterIsLowercase = 96 < c && c < 123;
            bool nextLetterIsUppercase = 64 < cNext && cNext < 91;
            bool charIntoNumber = (isalpha(c)) && (47 < cNext && cNext < 58);
            bool numberIntoChar = (47 < c && c < 58) && (isalpha(cNext)); 
            bool endOfCurrentWord = (
                !isalnum(cNext) ||
                (currentLetterIsLowercase && nextLetterIsUppercase) ||
                charIntoNumber || numberIntoChar
            );

            if (endOfCurrentWord){
                lowercase_letters_and_convert_first_one_to_uppercase_inplace(currentWordBuffer);
                currentWordBuffer[currentWordLength] = delimiter;
                strncat(filenameBody, currentWordBuffer, currentWordLength+1);
                currentWordLength = 0;
            }
        }
    }
    filenameBody[strlen(filenameBody)-1] = '\0'; //removes the delimiter at the end
}

void glue_together(char outputBuffer[], char id[], char filenameBody[], char extensionName[], char delimiter){
    strcpy(outputBuffer, id);
    outputBuffer[strlen(outputBuffer)] = delimiter;
    strcat(outputBuffer, filenameBody);
    strcat(outputBuffer, extensionName);
}

void format_name(char outputBuffer[], char srcString[]){
    int ln = strlen(srcString);
    char extensionNameBuffer[ln+1];
    char filenameBody[ln*2];
    char idBuffer[ln+1];
    char delimiter = '_';
    cut_extension_name_off(extensionNameBuffer, srcString);
    cut_id_out(idBuffer, srcString);
    separate_and_apply_case(srcString, filenameBody, delimiter);
    glue_together(outputBuffer, idBuffer, filenameBody, extensionNameBuffer, delimiter);
}