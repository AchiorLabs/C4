#ifndef ACHIOR_LABS_UTILS_H
#define ACHIOR_LABS_UTILS_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "Types.h"

#include <stddef.h>
#include <stdarg.h>

#include <ctype.h>

#ifndef ACHIOR_LABS_TOUPPER
#define ACHIOR_LABS_TOUPPER toupper
#endif

#include <assert.h>

#ifndef ACHIOR_LABS_ASSERT
#define ACHIOR_LABS_ASSERT assert
#endif


#include <time.h>
#ifndef ACHIOR_LABS_TIME
#define ACHIOR_LABS_TIME time
#endif

#include <string.h>
#ifndef ACHIOR_LABS_STRNCPY
#define ACHIOR_LABS_STRNCPY strncpy
#endif

#ifndef ACHIOR_LABS_STRNCMP
#define ACHIOR_LABS_STRNCMP strncmp
#endif

#ifndef ACHIOR_LABS_STRCMP
#define ACHIOR_LABS_STRCMP strcmp
#endif

#ifndef ACHIOR_LABS_STRLEN
#define ACHIOR_LABS_STRLEN strlen
#endif


#ifndef ACHIOR_LABS_STRRCHR
#define ACHIOR_LABS_STRRCHR strrchr
#endif

#ifndef ACHIOR_LABS_MEMCPY
#define ACHIOR_LABS_MEMCPY memcpy
#endif

#ifndef ACHIOR_LABS_MEMCMP
#define ACHIOR_LABS_MEMCMP memcmp
#endif

#ifndef ACHIOR_LABS_STRERROR
#define ACHIOR_LABS_STRERROR strerror
#endif

#include <stdio.h>
#ifndef ACHIOR_LABS_PUTS
#define ACHIOR_LABS_PUTS puts
#endif

#ifndef ACHIOR_LABS_PRINTF
#define ACHIOR_LABS_PRINTF printf
#endif

#ifndef ACHIOR_LABS_FPRINTF
#define ACHIOR_LABS_FPRINTF fprintf
#endif

#ifndef ACHIOR_LABS_SNPRINTF
#define ACHIOR_LABS_SNPRINTF snprintf
#endif

#ifndef ACHIOR_LABS_FGETS
#define ACHIOR_LABS_FGETS fgets
#endif

#ifndef ACHIOR_LABS_SNPRINTF
#define ACHIOR_LABS_SNPRINTF snprintf
#endif



#ifndef ACHIOR_LABS_PRINT
#define ACHIOR_LABS_PRINT puts
#endif

#ifndef ACHIOR_LABS_FOPEN
#define ACHIOR_LABS_FOPEN fopen
#endif


#ifndef ACHIOR_LABS_FREAD
#define ACHIOR_LABS_FREAD fread
#endif



#ifndef ACHIOR_LABS_FWRITE
#define ACHIOR_LABS_FWRITE fwrite
#endif


#ifndef ACHIOR_LABS_FCLOSE
#define ACHIOR_LABS_FCLOSE fclose
#endif


#ifndef ACHIOR_LABS_FSEEK
#define ACHIOR_LABS_FSEEK fseek
#endif


#ifndef ACHIOR_LABS_FTELL
#define ACHIOR_LABS_FTELL ftell
#endif




#ifndef ACHIOR_LABS_MEMSET
#define ACHIOR_LABS_MEMSET memset
#endif

#include <stdlib.h>
#ifndef ACHIOR_LABS_MALLOC
#define ACHIOR_LABS_MALLOC malloc
#endif

#ifndef ACHIOR_LABS_ALLOC
#define ACHIOR_LABS_ALLOC ACHIOR_LABS_MALLOC
#endif

#ifndef ACHIOR_LABS_CALLOC
#define ACHIOR_LABS_CALLOC calloc
#endif

#ifndef ACHIOR_LABS_FREE
#define ACHIOR_LABS_FREE free
#endif

#ifndef ACHIOR_LABS_SYSTEM
#define ACHIOR_LABS_SYSTEM system
#endif

#include <stdbool.h>

#ifndef ACHIOR_LABS_QSORT 
#define ACHIOR_LABS_QSORT qsort
#endif

#define ACHIOR_LABS_RETURN_DEFER(label) goto label


#include <errno.h>

#ifndef ACHIOR_LABS_PERROR
#define ACHIOR_LABS_PERROR perror
#endif

#include <dirent.h>

#ifndef ACHIOR_LABS_OPENDIR
#define ACHIOR_LABS_OPENDIR opendir
#endif

#ifndef ACHIOR_LABS_READDIR
#define ACHIOR_LABS_READDIR readdir
#endif

#ifndef ACHIOR_LABS_CLOSEDIR
#define ACHIOR_LABS_CLOSEDIR closedir
#endif

#include <sys/stat.h>

#ifndef ACHIOR_LABS_LSTAT
#define ACHIOR_LABS_LSTAT lstat
#endif


#define ACHIOR_LABS_TRUE(val)                     (val)  == true
#define ACHIOR_LABS_FALSE(val)                    (val)  == false
#define ACHIOR_LABS_ZERO(val)                     (val)  == 0
#define ACHIOR_LABS_NOT_ZERO(val)                 (val)  != 0
#define ACHIOR_LABS_NULL(val)                     (val)  == NULL
#define ACHIOR_LABS_NOT_NULL(val)                 (val)  != NULL
#define ACHIOR_LABS_EQUAL(val1,val2)              (val1) == (val2)
#define ACHIOR_LABS_NOT_EQUAL(val1,val2)          (val1) != (val2)
#define ACHIOR_LABS_GREATER_EQUAL(val1,val2)      (val1) >= (val2)
#define ACHIOR_LABS_GREATER(val1,val2)            (val1) > (val2)
#define ACHIOR_LABS_LESS_EQUAL(val1,val2)         (val1) <= (val2)
#define ACHIOR_LABS_LESS(val1,val2)               (val1) < (val2)


#define ACHIOR_LABS_RESET_ERRNO(val)             errno = (val)





#define ACHIOR_LABS_ARRAY_LEN(array) sizeof((array))/sizeof((array)[0])
#define ACHIOR_LABS_SIZEOF(val) sizeof(val)




#endif
