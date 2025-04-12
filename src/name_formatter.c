#include "name_formatter.h"
#include "letter_case.h"

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

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

void correct_by_pieces(char srcString[], char destString[], char delimiter){
    int ln = strlen(srcString);
    int currentWordLength = 0;
    char currentWordBuffer[ln];

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
                if (i == ln - 1){
                    currentWordLength -= 1; //to avoid including the delimiter in the following strncat call
                }
                strncat(destString, currentWordBuffer, currentWordLength+1);
                currentWordLength = 0;
            }
        }
    }
}
