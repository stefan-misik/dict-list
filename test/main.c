#include "../src/dict_list.h"

/******************************************************************************/
int main(
    int argc, 
    char** argv
)
{
    dict_list_t list;
    
    
    dict_list_init(&list, 6);
    
    dict_list_deinit(&list);
    
    return 0;
}