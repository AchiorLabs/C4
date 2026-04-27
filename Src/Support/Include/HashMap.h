/****************************************************************************************************\
 * FILE: hashmap.h                                                                                  *
 * AUTHOR: Michael Kamau                                                                            *
 *                                                                                                  *
 * PURPOSE: The program is an implementation of a hash map that stores data in key value pairs,     *
 *          the program uses xxh64 algorithm for hashing and foward chaining for collision          *
 *          handling                                                                                *
 *                                                                                                  *
 *  USAGE: To instantiate the program :                                                             *
 *                `struct HashMap *self = create_hashmap(capacity)`                                         *
 *                 capacity is the number of buckets to create                                      *
 *                                                                                                  *
 *                  The more the capacity the less the chances of collisions                        *
 *                                                                                                  *
 *                 inserting and reading values from the map:                                       *
 *                    -inserting:                                                                   *
 *                               HashMapAdd(map, key, len ,value)                            *
 *                    -reading:                                                                     *
 *                              get_hasmap_value(map, key, len)                                     *
 *                                                                                                  *
 \***************************************************************************************************/


#ifndef C4C_HASHMAP
#define C4C_HASHMAP


#include "Utils.h"
#include "BumpAllocator.h"

/**
 * The constants below are a set of carefully chosed prime numbers
 * by the designers of the xxh64 algorithm.
 * 
 * I have not memorized them and refered directly from its documentation
 */
#define XXH_PRIME64_1 11400714785074694791ULL
#define XXH_PRIME64_2 14029467366897019727ULL
#define XXH_PRIME64_3 1609587929392839161ULL
#define XXH_PRIME64_4 9650029242287828579ULL
#define XXH_PRIME64_5 2870177450012600261ULL

#define RotateLeft64(x, r) (((x) << (r)) | ((x) >> (64 - (r))))

struct HashNode
{
    void *key;
    u64 keyLength;
    void *value;
    u64 hash;
    struct HashNode *next; /* For forward chaining */
};


struct HashMap
{
    struct HashNode **buckets; /* array of bucket heads */
    u64 capacity;
    u64 size;
    u64 seed;
    struct BumpAllocator *bump;
};


/**
 This implementation follows the canonical XXH64 design. The goal is not
cryptographic security, but extremely fast, well-distributed hashing for
hash tables, interners, and systems code.

High-level structure:

  helpers -> bulk processing -> tail processing -> final avalanche

Key ideas to keep in mind when reading or modifying this code:

1) Safe raw memory access
   ----------------------
   All reads use ACHIOR_LABS_MEMCPY-based helpers (ReadU64/ReadU64) instead of casts.
   This avoids undefined behavior from unaligned access and strict aliasing,
   while still compiling to optimal machine code.

2) Bit rotation
   ------------
   Rotations are used instead of shifts to preserve information while moving
   entropy across bit positions. This is essential for avalanche behavior.

3) Core mixing primitive (XXH64Round)
   -----------------------------------
   This is the atomic mixing step:
     - multiply input by a large prime
     - add to accumulator
     - rotate
     - multiply again
   It is reused conceptually throughout the algorithm.

4) Parallel accumulation (v1..v4)
   -------------------------------
   Large inputs are processed using four independent 64-bit accumulators.
   This enables instruction-level parallelism, hides multiplication latency,
   and improves early diffusion. Input is consumed in 32-byte stripes
   (4 × 64-bit words) for cache-friendly, branch-free processing.

5) Accumulator merge
   ------------------
   After bulk processing, the four lanes are rotated differently, combined,
   and re-mixed into a single hash value. This step collapses parallel state
   while preserving entropy from each lane.

6) Small-input path
----------------
For inputs smaller than 32 bytes, no parallel lanes are used. The hash
starts from a seed + prime base to ensure reasonable diffusion without
   unnecessary overhead.

7) Length mixing
   --------------
   The total input length is always added to the hash. This prevents prefix
   collisions and ensures that size is part of the hash identity.

8) Tail processing
   ---------------
   Remaining bytes are processed in descending order of size:
     - 8-byte chunks
     - 4-byte chunk
     - individual bytes
   Each step uses appropriate mixing to ensure every byte influences the
   final hash. Many hash bugs occur in this phase if done incorrectly.

9) Final avalanche
   ----------------
   A sequence of XOR-shifts and multiplications destroys any remaining
   structure and guarantees strong diffusion. Even low-entropy or patterned
   inputs should produce well-distributed output.
 */

static inline u64 ReadU64(const void *ptr);

static inline u32 ReadU32(const void *ptr);

static inline u64 XXH64Round(u64 acc, u64 input);

static inline u64 XXH64(const void *input, u64 len, u64 seed);

/**
 * This function initializes the hashmap
 * It takes one parametere:
 * 
 * - capacity -> the number of buckets to be created
 * 
 * Notice that we use calloc, because we want the bucket to be zerod out
 * so that setting a key at an index found by the hashing algo works well
 * 
 */
bool HashMapNew(struct HashMap *self,u64 capacity,struct BumpAllocator *bump);

/**
 * This function inserts a key and value to the hash map
 * It takes four parameters:
 * - map -> a pointer to the map that is being inserted to
 * - key -> the key
 * - len -> the length of the key, we require this for dynamic memory allocation
 * - value -> This is the value of the item being saved in key
 * 
 * Notice that we use void for generics, 
 */
bool HashMapAdd(struct HashMap *self,const void *key,u64 len,void *value);


/**
 * This function returns the value of a given key.
 * It takes three parameters:
 * - map -> the map to search the key from
 * - key -> the key to search for
 * - len -> the length of the key
 * 
 * we need the length of the key to check against the length store in the 
 * node i.e node->len,
 * why? We just want to be super sure that everything about the key matches with
 * what we stored in the hashmap
 * 
 * Notice that we use void, for generic, this means when using this function
 * it is the responsibility of the caller to cast the data to the appropriate 
 * type. Failure to this will result to unwanted results
 */
void *HashMapGet(struct HashMap *self,const void *key,u64 len);



#endif // C4C_HASHMAP
