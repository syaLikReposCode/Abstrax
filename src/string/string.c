#include <abstrax/string/string.h>

struct ReturnValue string_init(char *initial){
    struct ReturnValue ret;
    size_t str_size = strlen(initial);
    ret.value = malloc(sizeof(struct string));
    struct string *ref_value = (struct string *)ret.value;
    ret.err = Ok;
    if(ref_value == NULL){
        ret.err = OutOfMemory;
        SET_RETURN_NULL(ret);
        ret.value = NULL;
        return ret;
    }
    ref_value->native_value = calloc(str_size, sizeof(char));
    if(ref_value->native_value == NULL){
        ret.err = OutOfMemory;
        SET_RETURN_NULL(ret);
        free(ref_value);
        ret.value = NULL;
        return ret;
    }
    strncpy(ref_value->native_value, initial, str_size);
    strncpy(ret.return_type, "object->string", 14);
    ref_value->value_size = str_size;
    ret.value = (void*)ref_value;
    return ret;
}

void string_deinit(struct string *instance){
    if(instance == NULL)
        return;
    free(instance->native_value);
    instance->value_size = 0;
    free(instance);
    instance = NULL; // avoid dangling pointer
}

enum ErrorCode string_size(struct string *instance, size_t *output_ptr){
    if(output_ptr == NULL || instance == NULL)
        return NullParameter;
    *output_ptr = instance->value_size;
    return Ok;
}

char *string_getvalue(struct string *instance){
    if(instance == NULL)
        return NULL;
    return instance->native_value;
}

enum ErrorCode string_setvalue(struct string* instance, char *another){
    if(string_getvalue(instance) != NULL){
        size_t size_new = strlen(another);
        char *get_pointer = string_getvalue(instance);
        get_pointer = realloc(get_pointer, sizeof(char) * size_new);
        if(get_pointer == NULL)
            return OutOfMemory;
        strcpy(get_pointer, another);
        instance->value_size = size_new;
        return Ok;
    }
    return UnresolvedValue;
}

enum ErrorCode string_tolower(struct string *instance){
    size_t instance_size;
    (void)string_size(instance, &instance_size);
    if(instance_size == 0)
        return UnresolvedValue;
    char *chunks = string_getvalue(instance);
    for(size_t i = 0; i < instance_size; i++)
        chunks[i] = tolower(chunks[i]);
    return Ok;
}

struct ReturnValue string_lowercase(struct string *instance){
    struct ReturnValue retval;
    SET_RETURN_OK(retval);
    if(instance == NULL){
        retval.err = NullParameter;
        retval.value = NULL;
        return retval;
    }
    strncpy(retval.return_type, "object->string", 14);
    retval.err = string_tolower(instance);
    retval.value = instance;
    return retval;
}

enum ErrorCode string_toupper(struct string *instance){
    size_t instance_size;
    (void)string_size(instance, &instance_size);
    if(instance_size == 0)
        return UnresolvedValue;
    char *chunks = string_getvalue(instance);
    for(size_t i = 0; i < instance_size; i++)
        chunks[i] = toupper(chunks[i]);
    return Ok;
}

struct ReturnValue string_uppercase(struct string *instance){
    struct ReturnValue retval;
    SET_RETURN_OK(retval);
    if(instance == NULL){
        retval.err = NullParameter;
        retval.value = NULL;
        return retval;
    }
    strncpy(retval.return_type, "object->string", 14);
    retval.err = string_toupper(instance);
    retval.value = instance;
    return retval;
}

struct ReturnValue string_substr(struct string *instance, size_t from, size_t length){
    struct ReturnValue retval;
    SET_RETURN_OK(retval);
    retval.err = Ok;

    size_t current_size = 0;
    (void)string_size(instance, &current_size);

    if(current_size < from){
        retval.err = InvalidParameter;
        retval.value = NULL;
        SET_RETURN_NULL(retval);
        return retval;
    }
    const int NullTerminateSize = 1;
    char *setup_str = calloc(length+NullTerminateSize, sizeof(char));
    if(setup_str == NULL){
        retval.err = OutOfMemory;
        retval.value = NULL;
        SET_RETURN_NULL(retval);
        return retval;
    }
    char *value_pointer = string_getvalue(instance);
    for(size_t i = 0; i < length; i++)
        setup_str[i] = value_pointer[from+i];
    setup_str[length] = '\0';
    (void)string_setvalue(instance, setup_str);
    free(setup_str);
    retval.value = instance;
    strncpy(retval.return_type, "object->string", 14);
    return retval;
}

int string_compare(struct string *compare1, struct string *compare2){
    return strcmp(string_getvalue(compare1), string_getvalue(compare2));
}