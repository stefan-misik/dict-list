#include "dict_list.h"
#include <stdlib.h>
#include <string.h>

#define dict_list_malloc(size) malloc(size)
#define dict_list_free(ptr) free(ptr)

/******************************************************************************/
/*                               Private                                      */
/******************************************************************************/

/**
 * @brief Calculate hash for specified key
 * 
 * @param key Key string to hash
 * @param hash_table_length Length of the hash table
 * 
 * @return Value of the hash 
 */
static hash_t dict_list_clalc_hash(
    const char * key,
    hash_t hash_table_length
)
{
    return 0;
}

/**
 * @brief Create an list item with specified key
 * 
 * @param[in] key Key to be copied into dictionary list item
 * 
 * @return Pointer to new dictionary list item, NULL pointer on failure 
 */
static dict_list_item_t * dict_list_item_create(
    const char * key
)
{
    dict_list_item_t * new_item;
    size_t key_buffer_length;
    
    key_buffer_length = strlen(key) + 1;
    
    /* Allocate new dictionary list item */
    new_item = (dict_list_item_t *)dict_list_malloc(sizeof(dict_list_item_t) +
            (key_buffer_length * sizeof(char)));
    if((dict_list_item_t *)0 == new_item)
        return new_item;
    
    /* Set key pointer */
    new_item->key = ((char *)new_item) + sizeof(dict_list_item_t);
    
    /* Copy the key value */
    memcpy(new_item->key, key, key_buffer_length);
        
    return new_item;
}

/**
 * @brief Free passed dictionary list item
 *  
 * @param[in,out] item Dictionary list item to be destroyed
 */
static void dict_list_item_destroy(
    dict_list_item_t * item
)
{
    dict_list_free(item);
}

/******************************************************************************/
/*                                Public                                      */
/******************************************************************************/

/******************************************************************************/
dict_list_ret_t dict_list_init(
    dict_list_t * list,
    int hash_table_length
)
{
    /* Allocate hash table */
    list->hash_table = (dict_list_item_t **)dict_list_malloc(
        sizeof(dict_list_item_t *) * hash_table_length);
    
    /* Check allocated memory */
    if((dict_list_item_t **)0 == list->hash_table)
        return DICT_LIST_NO_MEMORY;
    
    /* Initialize list object fields with their respective values */
    list->first_item = (dict_list_item_t *)0;
    list->hash_table_length = hash_table_length;
    
    /* Call empty list function to initialize the hash table */
    return dict_list_empty(list);
}

/******************************************************************************/
dict_list_ret_t dict_list_deinit(
    dict_list_t * list
)
{
    dict_list_ret_t ret;
    
    /* Empty the list */
    ret = dict_list_empty(list);
    if(DICT_LIST_OK != ret)
    {
        return ret;
    }
    
    /* Free hash table */
    dict_list_free(list->hash_table);
    list->hash_table = (dict_list_item_t **)0;
    
    return DICT_LIST_OK;
}

/******************************************************************************/
dict_list_ret_t dict_list_empty(
    dict_list_t * list
)
{
    dict_list_item_t * item, * item_tmp;
    hash_t i, hash_length;
    
    /* Remove all the items from the list */
    item = list->first_item;
    list->first_item = (dict_list_item_t *)0;    
    while((dict_list_item_t *)0 != item)
    {
        item_tmp = item;
        item = item->next_item;
        dict_list_item_destroy(item_tmp);
    }
    
    /* Clean the hash table */
    for(i = 0, hash_length = list->hash_table_length; i < hash_length; i ++)
    {
        list->hash_table[i] = (dict_list_item_t *)0;
    }
    
    return DICT_LIST_OK;
}