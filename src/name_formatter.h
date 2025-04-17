// correct_name_format.h
#ifndef NAME_FORMATTER_H
#define NAME_FORMATTER_H

void cut_extension_name_off(char extensionNameBuffer[], char srcString[]);
void cut_id_out(char idBuffer[], char srcString[]);
void separate_and_apply_case(char srcString[], char filenameBuffer[], char delimiter);
void glue_together(char outputBuffer[], char id[], char filenameBody[], char extensionName[], char delimiter);
void format_name(char outputBuffer[], char srcString[]);

#endif