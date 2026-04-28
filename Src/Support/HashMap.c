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



#include "Include/HashMap.h"


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

static u64 ReadU64(const void *ptr)
{
    u64 val = 0;
    ACHIOR_LABS_MEMCPY(&val, ptr, sizeof(val));
    return val;
}

static u32 ReadU32(const void *ptr)
{
    u32 val = 0;
    ACHIOR_LABS_MEMCPY(&val, ptr, sizeof(val));
    return val;
}

static u64 XXH64Round(u64 acc, u64 input)
{
    acc += input * XXH_PRIME64_2;
    acc = RotateLeft64(acc, 31);
    acc *= XXH_PRIME64_1;

    return acc;
}

static u64 XXH64(const void *input, u64 len, u64 seed)
{
    const u8 *p = (const u8 *)input;
    const u8 *end = p + len;
    u64 h64;

    if (len >= 32)
    {
        const u8 *limit = end - 32;

        u64 v1 = seed + XXH_PRIME64_1 + XXH_PRIME64_2;
        u64 v2 = seed + XXH_PRIME64_2;
        u64 v3 = seed + 0;
        u64 v4 = seed - XXH_PRIME64_1;

        do
        {
            v1 = XXH64Round(v1, ReadU64(p));
            p += 8;
            v2 = XXH64Round(v2, ReadU64(p));
            p += 8;
            v3 = XXH64Round(v3, ReadU64(p));
            p += 8;
            v4 = XXH64Round(v4, ReadU64(p));
            p += 8;
        } while (p <= limit);

        h64 =
            RotateLeft64(v1, 1) +
            RotateLeft64(v2, 7) +
            RotateLeft64(v3, 12) +
            RotateLeft64(v4, 18);

        h64 ^= XXH64Round(0, v1);
        h64 *= XXH_PRIME64_1;

        h64 ^= XXH64Round(0, v2);
        h64 *= XXH_PRIME64_1;

        h64 ^= XXH64Round(0, v3);
        h64 *= XXH_PRIME64_1;

        h64 ^= XXH64Round(0, v4);
        h64 *= XXH_PRIME64_1;
    }
    else
    {
        h64 = seed + XXH_PRIME64_5;
    }
    h64 *= len;

    while (p + 8 <= end)
    {
        u64 k1 = XXH64Round(0, ReadU64(p));
        h64 ^= k1;
        h64 = RotateLeft64(h64, 27) * XXH_PRIME64_1 + XXH_PRIME64_4;
        p += 8;
    }

    if (p + 4 <= end)
    {
        h64 ^= (u64)ReadU64(p) * XXH_PRIME64_1;
        h64 = RotateLeft64(h64, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
        p += 4;
    }
    while (p < end)
    {
        h64 ^= (*p) * XXH_PRIME64_5;
        h64 = RotateLeft64(h64, 11) * XXH_PRIME64_1;
        p++;
    }

    h64 ^= h64 >> 33;
    h64 *= XXH_PRIME64_2;
    h64 ^= h64 >> 29;
    h64 *= XXH_PRIME64_3;
    h64 ^= h64 >> 32;

    return h64;
}

/**
 * This function initializes the hashmap
 * It takes 3 parameters:
 * 
 * - self       -> the memory address of the hashmap
 * - bump       -> the bump allocator
 * - capacity   -> the number of buckets to be created
 * 
 * If the function always returns true
 */
bool HashMapNew(struct HashMap *self,u64 capacity,struct BumpAllocator *bump)
{
    self->capacity = capacity;
    self->seed     = 0;
    self->size     = 0;
    self->bump     = bump;
    self->buckets  = ACHIOR_LABS_ARENA_ALLOC(self->bump,struct HashNode *,capacity);

    return true;
}



/**
 * This function inserts a key and value to the hash map
 * It takes four parameters:
 * - sef    -> a pointer to the map that is being inserted to
 * - key    -> the key
 * - len    -> the length of the key, we require this for dynamic memory allocation
 * - value  -> This is the value of the item being saved in key
 * 
 * Notice that we use void for generics, 
 */
bool HashMapAdd(struct HashMap *self,const void *key,u64 len,void *value)
{
    u64 hash = XXH64(key,len,self->seed);
    u64 idx  = hash % self->capacity;

    struct HashNode *node = (struct HashNode *)ACHIOR_LABS_ARENA_ALLOC(self->bump,struct HashNode,1);

    if(ACHIOR_LABS_NULL(node))
    {
        return false;
    }

    node->hash = hash;
    node->key  = ACHIOR_LABS_ARENA_ALLOC(self->bump,char,len);

    if(ACHIOR_LABS_NULL(node->key))
    {
        return false;
    }

    node->keyLength = len;
    ACHIOR_LABS_MEMCPY(node->key, key, len);
    node->value        = value;

    node->next         = self->buckets[idx];
    self->buckets[idx] = node;
    self->size++;

    return true;
}


/**
 * This function returns the value of a given key.
 * It takes three parameters:
 * - self -> the map to search the key from
 * - key  -> the key to search for
 * - len  -> the length of the key
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
void *HashMapGet(struct HashMap *self,const void *key,u64 len)
{
    u64 hash = XXH64(key, len, self->seed);
    u64 idx = hash % self->capacity;

    for (struct HashNode *node = self->buckets[idx]; ACHIOR_LABS_NOT_NULL(node); node = node->next)
    {
        //DEBUG_PRINT("The key is: ", (char *)node->key);
        //DEBUG_PRINT("Being checked against key: ", (char *)key);
        //DEBUG_PRINT("The length of the key is: ",len);

        if (node->keyLength == len && memcmp(node->key, key, len) == 0)
        {
            return node->value;
        }
    }

    return NULL;
}


/**
 * This function returns a copy of a given hashmap.
 * It takes one parameter:
 * - self -> the map to search the key from
 * 
 * it perforns a deep copy of the self hashmap and return a 
 * copy of it.
 * This function does not perform a deep clean on node creation failure, beware 
 * 
 */
struct HashMap *HashMapCopy(struct HashMap *self)
{
    if(ACHIOR_LABS_NULL(self))
    {
        return NULL;
    }

    size_t sizeOfHashMap            = ACHIOR_LABS_SIZEOF(struct HashMap);
    struct HashMap hashMapCopy;     
    bool created                    = HashMapNew(&hashMapCopy, self->capacity,self->bump);


    if(! created)
    {
        return NULL;
    }



    for(u64 i = 0; i < self->capacity; i++) 
    {
        struct HashNode *node       = self->buckets[i];

        while(node)
        {
            bool nodeCopied         = HashMapAdd(&hashMapCopy,node->key,node->keyLength, node->value);

            if(! nodeCopied)
            {
                //should do a total clean up, 
                ACHIOR_LABS_FREE(&hashMapCopy);
            }
            node                    = node->next;
        }
    }


    return &hashMapCopy;
}
