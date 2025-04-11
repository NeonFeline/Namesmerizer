#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./src/anyascii.h"
#include "./src/utf8.h"

static void anyascii_string(const char *in, char *out) {
	uint32_t utf32;
	uint32_t state = 0;
	for (; *in; in++) {
		utf8_decode(&state, &utf32, (unsigned char) *in);
		switch (state) {
		case UTF8_ACCEPT:;
			const char *r;
			size_t rlen = anyascii(utf32, &r);
			memcpy(out, r, rlen);
			out += rlen;
			break;
		case UTF8_REJECT:
			state = UTF8_ACCEPT;
			break;
		}
	}
	*out = 0;
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

int main(int argc, char *argv[]) {
    char name_out[256];
    char name[] = "___++123--l.jfn.zip";
    char extensionNameBuffer[strlen(name)];
    cut_extension_name_off(extensionNameBuffer, name);
    correct_by_pieces(name, name_out, '_');
    puts(name_out);
}
