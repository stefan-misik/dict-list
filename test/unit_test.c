#include "unit_test.h"
#include <string.h>
#include <stdio.h>

#define UNIT_TEST_RESULT_LENGTH 4

#define UNIT_TEST_CONSOLE_WIDTH 80

/**
 * @brief String representation of test result
 * 
 */
static const char * g_results[] = {"FAIL", "PASS"};

/**
 * @brief Separator string
 * 
 */
static const char * g_separator = "********************************************"
    "************************************";

/**
 * @brief Output stream
 * 
 */
static FILE * test_output;


/******************************************************************************/
void unit_test_result(
    unit_test_case_t * this_test_case,
    const char * test_name,
    int result
)
{
    int spaces;
    
    /* Print test name */
    fprintf(test_output, "%s", test_name);
    
    /* Print separators */
    spaces = UNIT_TEST_CONSOLE_WIDTH - UNIT_TEST_RESULT_LENGTH
            - strlen(test_name);
    for(; spaces > 0; spaces --)
    {
        putc(' ', test_output);
    }
    
    if(result)
    {
        fprintf(test_output, "%s", g_results[1]);
        this_test_case->tests_passed ++;
    }
    else
    {
        fprintf(test_output, "%s", g_results[0]);
        this_test_case->tests_failed ++;
    }        
}

/******************************************************************************/
int main(
    int argc, 
    char** argv
)
{
    unit_test_case_t ** pos = unit_test_case_list;
    unsigned passed, failed;
    passed = 0;
    failed = 0;
    
    test_output = stdout;
    
    
    /* Iterate through all the tests */
    while(NULL != (*pos))
    {
        /* Perform test */
        (*pos)->test_fcn(*pos);              

        /* Count results */
        passed += (*pos)->tests_passed;
        failed += (*pos)->tests_failed;        

        /* Move to another test */
        pos ++;
    }    
        
    return 0;
}