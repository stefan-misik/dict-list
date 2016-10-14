#include "../unit_test.h"
#include "../../src/dict_list.h"
#include <stdlib.h>


/*
 * Dictionary list initialization test case
 */
UNIT_TEST_CASE(dict_list_init)
{
    do
    {
        dict_list_t list;
        dict_list_hash_t hash_table_length, i;
        int hash_table_not_null;
        
        /* Prepare test */
        hash_table_length = 10;
        list.hash_table = NULL;
        list.hash_table_length = ~hash_table_length;
        hash_table_not_null = 0;
        
        /* Call the tested function */
        dict_list_init(&list, hash_table_length);
        
        /* Post process */
        for(i = 0; i < hash_table_length; i ++)
            if(NULL != list.hash_table[i])
                hash_table_not_null ++;
        
        /* Print results */
        unit_test_eq("Hash table length", list.hash_table_length, 
                hash_table_length);
        unit_test_neq("Hash table pointer allocation",
                NULL, list.hash_table);
        unit_test_eq("Hash table empty", 
                0, hash_table_not_null);
        
        /* Clean up */
        free(list.hash_table);
        
    }while(0);
}

/*
 * Dictionary list de-initialization test case
 */
UNIT_TEST_CASE(dict_list_deinit)
{
    do
    {
        dict_list_t list;
        dict_list_hash_t hash_table_length, i;
        
        /* Prepare test */
        hash_table_length = 10;
        list.hash_table = malloc(sizeof(dict_list_hash_t) * 
                hash_table_length);
        list.hash_table_length = hash_table_length;
        for(i = 0; i < hash_table_length; i ++)
            list.hash_table[i] = NULL;
        
        /* Call the tested function */
        dict_list_deinit(&list);
        
        /* Print results */        
        unit_test_eq("Hash table pointer freed",
                NULL, list.hash_table);
        
    }while(0);
}

/*
 * Dictionary list empty test case
 */
UNIT_TEST_CASE(dict_list_empty)
{
    do
    {
        dict_list_t list;
        dict_list_hash_t hash_table_length, i;
        int hash_table_not_null;
        
        /* Prepare test */
        hash_table_length = 10;
        hash_table_not_null = 0;
        dict_list_init(&list, hash_table_length);
        for(i = 0; i < hash_table_length; i ++)
        {
            list.hash_table[i] = malloc(sizeof(dict_list_item_t));
            list.hash_table[i]->next_item = NULL;
            list.hash_table[i]->key = NULL;
        }
        
        /* Call the tested function */
        dict_list_empty(&list);
        
        /* Post process */
        for(i = 0; i < hash_table_length; i ++)
            if(NULL != list.hash_table[i])
                hash_table_not_null ++;
        
        /* Print results */
        unit_test_eq("Hash table empty", 
                0, hash_table_not_null);
        
        /* Clean up */
        dict_list_deinit(&list);
        
    }while(0);
}

/******************************************************************************/

/*
 * List of test cases 
 */
unit_test_case_t * unit_test_case_list[] = 
{
    UNIT_TEST_CASE_ENTRY(dict_list_init),
    UNIT_TEST_CASE_ENTRY(dict_list_deinit),
    UNIT_TEST_CASE_ENTRY(dict_list_empty),
    NULL
};