#ifndef _ABSTRAX_STRING
#define _ABSTRAX_STRING 1
#include <abstrax/baseobject.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct string{
    char *native_value;
    size_t value_size;
};

#define STRING_ALL "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define STRING_ALPHABETS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define STRING_ALPHABETS_LOWER "abcdefghijklmnopqrstuvwxyz"
#define STRING_ALPHABETS_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define STRING_NUMERICS "0123456789"
#define STRING_PUNCTUATIONS "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"


struct ReturnValue string_init(char *initial);
void string_deinit(struct string *instance);

enum ErrorCode string_size(struct string* instance, size_t *output_ptr);
char *string_getvalue(struct string *instance);
enum ErrorCode string_setvalue(struct string* instance, char *another);
// string_tolower only modifies the existing string, whilst string_lowercase returns a new instance. Also applies to upper.

enum ErrorCode string_tolower(struct string *instance);
struct ReturnValue string_lowercase(struct string *instance);

enum ErrorCode string_toupper(struct string *instance);
struct ReturnValue string_uppercase(struct string *instance);

struct ReturnValue string_substr(struct string *instance, size_t from, size_t length);
int string_compare(struct string *compare1, struct string *compare2);
#endif