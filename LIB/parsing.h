#ifndef _PARSING_
#define _PARSING_

// Macros para parsing
#define LN "\r\n"
#define SPACE " "
#define COMMA ","
#define DOT "."
#define SQUO "'"
#define DQUO "\""
#define LLETTER "abcdefghijklmnopqrstuvwxyz"
#define ULETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LETTER LLETTER ULETTER
#define DIGIT "0123456789"
#define SIGN "-+"

// Macros para quantidade de alocação.
#define CHUNK 32

char *readUntil(char *stop, FILE *fp);

char *readSome(char *chars, FILE *fp);
#endif
