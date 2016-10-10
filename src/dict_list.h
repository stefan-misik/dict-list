#ifndef _DICT_LIST_H
#define _DICT_LIST_H


/**
 * @brief Return value of dict_list functions
 */
typedef enum dict_list_ret 
{
    DICT_LIST_OK = 0,       /** < Return ok */
    DICT_LIST_NO_MEMORY,    /** < Insufficeint memory to complete the
                             *    operation */
    DICT_LIST_EXISTS,       /** < Requested key already exists */
    DICT_LIST_NOT_FOUND     /** < Requested key does not exist */
} dict_list_ret_t;


/**
 * @brief Type of a hash
 * 
 */
typedef int dict_list_hash_t;

/**
 * @brief Dictionary list item
 * 
 */
typedef struct dict_list_item
{
    char * key;                         /** < Key of the item */
    void * data;                        /** < Data associated with the item */
    struct dict_list_item * next_item;  /** < Next item in the list */
} dict_list_item_t;

/**
 * @brief Dictionary list item
 */
typedef struct dict_list
{
    dict_list_hash_t hash_table_length; /** < Length of a hash table */
    dict_list_item_t ** hash_table;     /** < Pointer to the hash table */
} dict_list_t;


/**
 * @brief Initialize the dictionary list
 * 
 * @param[out] list Pointer to a list object to be initialized
 * 
 * @return DICT_LIST_OK or DICT_LIST_NO_MEMORY
 */
dict_list_ret_t dict_list_init(
    dict_list_t * list,
    int hash_table_length
);

/**
 * @brief Destroy the list object and free its memory 
 * 
 * @param[in,out] list Pointer to the list object to be destroyed
 * 
 * @return Always DICT_LIST_OK
 */
dict_list_ret_t dict_list_deinit(
    dict_list_t * list
);

/**
 * @brief Empty the dictionary list
 * 
 * @param[in,out] list List object to be emptied
 * 
 * @return Always DICT_LIST_OK
 */
dict_list_ret_t dict_list_empty(
    dict_list_t * list
);

/**
 * @brief Add an item into the list
 * 
 * @param[in,out]  list     Pointer to a list object
 * @param[in]      key      Key of the new list item. This string is copied
 *                          into the list item
 * @param[in]      data     Data of the new list item. Only pointer is stored
 *                          in list item
 * @param[out]     old_data Pointer to memory which shall obtain old data
 *                          listed under provided key, if any. Can be a NULL
 *                          pointer. If provided key is not yet in the list,
 *                          this parameter is used to initialize old_data 
 *                          pointer with NULL
 * 
 * @return DICT_LIST_OK, DICT_LIST_NO_MEMORY or DICT_LIST_EXISTS when provided 
 *         key already exists and old_data pointer was not provided
 */
dict_list_ret_t dict_list_add(
    dict_list_t * list,
    const char * key,
    void * data,
    void ** old_data
);

/**
 * @brief Try to find the provided key in the list and remove it from the list
 * 
 * @param[in,out] list     Pointer to a dictionary list object
 * @param[in]     key      Key of the item to remove from the list
 * @param[out]    old_data Pointer to memory which shall obtain data listed
 *                         under provided key
 * 
 * @return DICT_LIST_OK or DICT_LIST_NOT_FOUND if key is not found in the list
 */
dict_list_ret_t dict_list_remove(
    dict_list_t * list,
    const char * key,
    void ** old_data
);
        


#endif /* _DICT_LIST_H */

