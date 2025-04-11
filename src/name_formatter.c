#include "name_formatter.h"

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
        if (isalnum(c)){
            currentWordBuffer[currentWordLength] = c;
            currentWordLength++;
        }
        else if (currentWordLength > 0){
            // function(currentWordBuffer);
            currentWordBuffer[currentWordLength] = delimiter;
            strncat(destString, currentWordBuffer, currentWordLength+1);
            currentWordLength = 0;
        }
    }
    strncat(destString, currentWordBuffer, currentWordLength);
}