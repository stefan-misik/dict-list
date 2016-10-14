#ifndef _UNIT_TEST_MALLOC
#define _UNIT_TEST_MALLOC

#include <stdlib.h>


/**
 * @brief An array of pointers to be returned
 */
void ** unit_test_mallocs;

/**
 * @brief A pointer to array of sizes to be stored
 */
size_t * unit_test_malloc_sizes;

/**
 * @brief Pointer to array which is to obtain the memory to be fried
 */
void ** unit_test_frees;


/**
 * @brief Malloc function stub
 * 
 * @param sz Size of the memory to be allocated
 * @return Pointer to allocated memory
 */
void * uint_test_malloc(
    size_t sz
)
{
    void * ret = NULL;
    
    /* Try to store the size */
    if(NULL != unit_test_malloc_sizes)
    {
        if(NULL != * unit_test_malloc_sizes)
        {
            *(unit_test_malloc_sizes ++) = sz;
        }
    }
    
    /* Get the return value */
    if(NULL != unit_test_mallocs)
    {
        if(NULL != *unit_test_mallocs)
        {
            ret = *(unit_test_mallocs ++);
        }
    }
    
    return ret;
}

/**
 * @brief Free function stub
 * 
 * @param[in] mem Memory to be freed
 */
void unit_test_free(
    void * mem
)
{
    /* Try to store the pointer to the memory to be fried */
    if(NULL != unit_test_frees)
    {
        if(NULL != *unit_test_frees)
        {
            *(unit_test_frees ++) = mem;
        }
    }
}



#endif /* _UNIT_TEST_MALLOC */