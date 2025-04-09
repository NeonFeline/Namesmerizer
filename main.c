#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void cut_extension_name_off(char buffer[], char string[]){
    int ln = strlen(string);
    for (int i=ln-1; i > 0; i--){
        if (string[i] == '.'){
            strncpy(buffer, string+i, ln-i);
            string[i] = '\0';
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    char name_out[256];
    printf("%s\n", name_out); 
    char name[] = "adsjfn.zip";
    char extensionBuffer[strlen(name)];
    cut_extension_name_off(extensionBuffer, name);
    printf("%s\n", extensionBuffer);
    printf("%s\n", name);
}
