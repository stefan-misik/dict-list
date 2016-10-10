#include "../src/dict_list.h"

/******************************************************************************/
int main(
    int argc, 
    char** argv
)
{
    dict_list_t list;
    void * data;
    
    
    dict_list_init(&list, 6);
    
    dict_list_set(&list, "test2", (void *)1, &data);
    
    dict_list_set(&list, "test", (void *)2, &data);
    
    dict_list_set(&list, "test", (void *)3, &data);
    
    dict_list_get(&list, "test", &data);
    
    dict_list_get(&list, "test3", &data);
    
    dict_list_get(&list, "test2", &data);
    
    dict_list_unset(&list, "test3", &data);
    
    dict_list_unset(&list, "test2", &data);
    
    dict_list_unset(&list, "test", &data);
    
    dict_list_deinit(&list);
    
    return 0;
}