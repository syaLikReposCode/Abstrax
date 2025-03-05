#ifndef _ABSTRAX_BASEOBJECT
#define _ABSTRAX_BASEOBJECT 0
#include <stdlib.h>
#define ABSTRAX_META_VERSION "1.0" /* The overall version of the library */

#ifndef SIZE_VALUE_DESCRIPTION
#define SIZE_VALUE_DESCRIPTION 512 /* Value description size used in `ReturnValue::return_type` */
#endif

#define _IMPLEMENT(X) // attribute notation. Yes, it does nothing.

enum ErrorCode{
    Ok = 0,
    OutOfMemory,
    NullParameter,
    InvalidParameter,
    UnresolvedValue // only use this when one of the library's function used by another function returns unexpected value (like size returning 0, or null value)
};

struct ReturnValue{
    void *value;
    enum ErrorCode err;
    char return_type[SIZE_VALUE_DESCRIPTION];
};

// one of the common variants of return type, sets object (an instance of `ReturnValue`) `.return_type` child to `null`.
#define SET_RETURN_NULL(object) strncpy(object.return_type, "null", 4)
// one of the common variants of return type, sets object (an instance of `ReturnValue`) `.return_type` child to `ok`.
#define SET_RETURN_OK(object) strncpy(object.return_type, "ok", 2)


#endif