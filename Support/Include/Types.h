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




#ifndef ACHIOR_LABS_U8_INIT
#define ACHIOR_LABS_U8_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u8,id,0)
#endif


#ifndef ACHIOR_LABS_U16_INIT
#define ACHIOR_LABS_U16_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u16,id,0)
#endif


#ifndef ACHIOR_LABS_U32_INIT
#define ACHIOR_LABS_U32_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u32,id,0)
#endif


#ifndef ACHIOR_LABS_U64_INIT
#define ACHIOR_LABS_U64_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u64,id,0)
#endif











#ifndef ACHIOR_LABS_I8_INIT
#define ACHIOR_LABS_I8_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i8,id,0)
#endif


#ifndef ACHIOR_LABS_I16_INIT
#define ACHIOR_LABS_I16_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i16,id,0)
#endif


#ifndef ACHIOR_LABS_I32_INIT
#define ACHIOR_LABS_I32_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i32,id,0)
#endif


#ifndef ACHIOR_LABS_I64_INIT
#define ACHIOR_LABS_I64_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i64,id,0)
#endif





#ifndef ACHIOR_LABS_F32_INIT
#define ACHIOR_LABS_F32_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(f32,id,0)
#endif


#ifndef ACHIOR_LABS_F64_INIT
#define ACHIOR_LABS_F64_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(f64,id,0)
#endif




#ifndef ACHIOR_LABS_U8_PTR_INIT
#define ACHIOR_LABS_U8_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u8_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_U16_PTR_INIT
#define ACHIOR_LABS_U16_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u16_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_U32_PTR_INIT
#define ACHIOR_LABS_U32_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u32_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_U64_PTR_INIT
#define ACHIOR_LABS_U64_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(u64_ptr,id,NULL)
#endif









#ifndef ACHIOR_LABS_I8_PTR_INIT
#define ACHIOR_LABS_I8_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i8_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_I16_PTR_INIT
#define ACHIOR_LABS_I16_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i16_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_I32_PTR_INIT
#define ACHIOR_LABS_I32_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i32_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_I64_PTR_INIT
#define ACHIOR_LABS_I64_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(i64_ptr,id,NULL)
#endif




#ifndef ACHIOR_LABS_F32_PTR_INIT
#define ACHIOR_LABS_F32_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(f32_ptr,id,NULL)
#endif


#ifndef ACHIOR_LABS_F64_PTR_INIT
#define ACHIOR_LABS_F64_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(f64_ptr,id,NULL)
#endif





#ifndef ACHIOR_LABS_VOID_PTR_INIT
#define ACHIOR_LABS_VOID_PTR_INIT(id) ACHIOR_LABS_COMMON_TYPE_INIT(void_ptr,id,NULL)
#endif










#ifndef ACHIOR_LABS_READ_PTR
#define ACHIOR_LABS_READ_PTR(type,id) *((type)(id)) 
#endif





#ifndef ACHIOR_LABS_READ_U8_PTR
#define ACHIOR_LABS_READ_U8_PTR(var) ACHIOR_LABS_READ_PTR(u8_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_U16_PTR
#define ACHIOR_LABS_READ_U16_PTR(var) ACHIOR_LABS_READ_PTR(u16_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_U32_PTR
#define ACHIOR_LABS_READ_U32_PTR(var) ACHIOR_LABS_READ_PTR(u32_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_U64_PTR
#define ACHIOR_LABS_READ_U64_PTR(var) ACHIOR_LABS_READ_PTR(u64_ptr,var)
#endif









#ifndef ACHIOR_LABS_READ_S8_PTR
#define ACHIOR_LABS_READ_S8_PTR(var) ACHIOR_LABS_READ_PTR(u8_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_S16_PTR
#define ACHIOR_LABS_READ_S16_PTR(var) ACHIOR_LABS_READ_PTR(u16_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_S32_PTR
#define ACHIOR_LABS_READ_S32_PTR(var) ACHIOR_LABS_READ_PTR(u32_ptr,var)
#endif

#ifndef ACHIOR_LABS_READ_S64_PTR
#define ACHIOR_LABS_READ_S64_PTR(var) ACHIOR_LABS_READ_PTR(u64_ptr,var)
#endif





#ifndef ACHIOR_LABS_WRITE_PTR
#define ACHIOR_LABS_WRITE_PTR(type,id,val) *((type)(id)) = (type)(val) 
#endif


#ifndef ACHIOR_LABS_WRITE_I8_PTR
#define ACHIOR_LABS_WRITE_I8_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u8_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_I16_PTR
#define ACHIOR_LABS_WRITE_I16_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u16_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_I32_PTR
#define ACHIOR_LABS_WRITE_I32_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u32_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_I64_PTR
#define ACHIOR_LABS_WRITE_I64_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u64_ptr,id,(val))
#endif








#ifndef ACHIOR_LABS_WRITE_U8_PTR
#define ACHIOR_LABS_WRITE_U8_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u8_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_U16_PTR
#define ACHIOR_LABS_WRITE_U16_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u16_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_U32_PTR
#define ACHIOR_LABS_WRITE_U32_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u32_ptr,id,(val))
#endif

#ifndef ACHIOR_LABS_WRITE_U64_PTR
#define ACHIOR_LABS_WRITE_U64_PTR(id,val) ACHIOR_LABS_WRITE_PTR(u64_ptr,id,(val))
#endif




#endif

