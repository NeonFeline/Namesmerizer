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


int main(int argc, char *argv[]) {
	char name_out[256] = "sHEsXsW";
	lowercase_letters_and_convert_first_one_to_uppercase_inplace(name_out);
	printf("%c\n", convert_to_lowercase('a'));
	printf("%s\n", name_out);

  	anyascii_string("Żok", name_out);
  	printf("%s\n", name_out);

	char name_out2[256];
	char name[] = "___[[++]]fiodorKurmanov1..23]--l.jfn.zip";
	char extensionNameBuffer[strlen(name)];
	cut_extension_name_off(extensionNameBuffer, name);
	correct_by_pieces(name, name_out2, '_');
	strcat(name_out2, extensionNameBuffer); // is this line okay?
	puts(name_out2);
}
