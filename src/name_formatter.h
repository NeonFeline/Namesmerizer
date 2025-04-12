// correct_name_format.h
#ifndef NAME_FORMATTER_H
#define NAME_FORMATTER_H

void cut_extension_name_off(char extensionNameBuffer[], char srcString[]);
void correct_by_pieces(char srcString[], char destString[], char delimiter);

#endif