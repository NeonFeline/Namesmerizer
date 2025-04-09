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


int main(int argc, char *argv[]) {
  char name_out[256];

  anyascii_string("Żok", name_out);
    printf("%s", name_out);
}
