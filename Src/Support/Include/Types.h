#ifndef ACHIOR_LABS_COMMON_TYPES_H
#define ACHIOR_LABS_COMMON_TYPES_H


#ifndef ACHIOR_LABS_TYPES_H


typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long      u64;


typedef signed char        i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long        i64;

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>

#else

#include <sys/types.h>
#include <stddef.h>



typedef u_int8_t 	   u8;
typedef u_int16_t 	   u16;
typedef u_int32_t 	   u32;
typedef u_int64_t 	   u64;


typedef int8_t		   i8;
typedef int16_t		   i16;
typedef int32_t 	   i32;
typedef int64_t 	   i64;

typedef size_t             usize;
typedef ssize_t            isize;

#endif


typedef float              f32;
typedef double             f64;

typedef u8 *   u8_ptr;
typedef u16 *  u16_ptr;
typedef u32 *  u32_ptr;
typedef u64 *  u64_ptr;


typedef i8 *   i8_ptr;
typedef i16 *  i16_ptr;
typedef i32 *  i32_ptr;
typedef i64 *  i64_ptr;


typedef f32 *  f32_ptr;
typedef f64 *  f64_ptr;

typedef void * void_ptr;



#ifndef ACHIOR_LABS_COMMON_TYPE_INIT
#define ACHIOR_LABS_COMMON_TYPE_INIT(type,ident,val) type ident = val 
#endif




#ifndef ACHIOR_LABS_VAR_INIT
#define ACHIOR_LABS_VAR_INIT(base,id) ACHIOR_LABS_COMMON_TYPE_INIT(base,id,0)
#endif


#ifndef ACHIOR_LABS_ARRAY_INIT
#define ACHIOR_LABS_ARRAY_INIT(base,id,size) base id[(size)] = {0}
#endif


#ifndef ACHIOR_LABS_STRUCT_INIT
#define ACHIOR_LABS_STRUCT_INIT(base,id) ACHIOR_LABS_COMMON_TYPE_INIT(base,id,(base){0})
#endif


#ifndef ACHIOR_LABS_PTR_INIT
#define ACHIOR_LABS_PTR_INIT(base,id) ACHIOR_LABS_COMMON_TYPE_INIT(base *,id,NULL)
#endif


#ifndef ACHIOR_LABS_READ_PTR
#define ACHIOR_LABS_READ_PTR(type,id) *((type)(id)) 
#endif


#ifndef ACHIOR_LABS_READ_STRUCT_PTR
#define ACHIOR_LABS_READ_STRUCT_PTR(id,member) (id)->member
#endif


#ifndef ACHIOR_LABS_READ_STRUCT
#define ACHIOR_LABS_READ_STRUCT(id,member) (id).member
#endif


#ifndef ACHIOR_LABS_WRITE_PTR
#define ACHIOR_LABS_WRITE_PTR(type,id,val) *((type)(id)) = (type)(val) 
#endif



#ifndef ACHIOR_LABS_WRITE_STRUCT_PTR
#define ACHIOR_LABS_WRITE_STRUCT_PTR(id,member,val) (id)->member = (val)
#endif


#ifndef ACHIOR_LABS_WRITE_STRUCT
#define ACHIOR_LABS_WRITE_STRUCT(id,member,val) (id).member = (val)
#endif


#endif

