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
 * @param hash_table_length Length of the hash table. Returned hash has to be 
 *                          positive number less than this value
 * 
 * @return Value of the hash for passed key and length of the hash table
 */
static dict_list_hash_t dict_list_clalc_hash(
    const char * key,
    dict_list_hash_t hash_table_length
)
{
    return 0;
}

/**
 * @rief Initialize hash the table of the list
 *  
 * @param[in,out] list List whose hash table is to be initialized
 */
static void dict_list_init_hash_table(
    dict_list_t * list
)
{
    dict_list_hash_t i, hash_length;
    
    
    /* Clean the hash table */
    for(i = 0, hash_length = list->hash_table_length; i < hash_length; i ++)
    {
        list->hash_table[i] = (dict_list_item_t *)0;
    }
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

/**
 * @brief Locate the pointer pointing towards specified item
 * 
 * @param[in] list List object
 * @param[in] key  Key of the item to be located
 * 
 * @return Pointer to the pointer to the item or NULL pointer if such item does 
 *         not exist 
 */
static dict_list_item_t ** dict_list_locate_item(
    const dict_list_t * list,
    const char * key
)
{
    dict_list_hash_t hash;
    dict_list_item_t ** item, ** item_ret;
    
    /* Set the default return value */
    item_ret = (dict_list_item_t **)0;    
    
    /* First calculate hash of the key */
    hash = dict_list_clalc_hash(key, list->hash_table_length);
    
    /* Get the pointer of the pointer to the first item in specific hash 
     * entry */
    item = list->hash_table + hash;
    
    while((dict_list_item_t *)0 != (*item))
    {
        /* Check if item matches provided key */
        if(0 == strcmp(key, (*item)->key))
        {
            item_ret = item;
            break;
        }
        
        item = &((*item)->next_item);
    }
    
    return item_ret;
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
    list->hash_table_length = hash_table_length;
    
    /* Initialize the hash table */
    dict_list_init_hash_table(list);
    
    return DICT_LIST_OK;
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
    dict_list_hash_t i, hash_length; 
    
    
    /* Clean the hash table */
    for(i = 0, hash_length = list->hash_table_length; i < hash_length; i ++)
    {
        /* Remove all the items from the hash table entry */
        item = list->hash_table[i];
        while((dict_list_item_t *)0 != item)
        {
            item_tmp = item;
            item = item->next_item;
            dict_list_item_destroy(item_tmp);
        }
        
        list->hash_table[i] = (dict_list_item_t *)0;
    }
    
    return DICT_LIST_OK;
}