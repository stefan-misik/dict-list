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
static FILE * g_test_output;


/******************************************************************************/
void unit_test_result(
    unit_test_case_t * this_test_case,
    const char * test_name,
    int result
)
{
    int spaces;
    
    /* Print test name */
    fprintf(g_test_output, "%s", test_name);
    
    /* Print separators */
    spaces = UNIT_TEST_CONSOLE_WIDTH - UNIT_TEST_RESULT_LENGTH
            - strlen(test_name);
    for(; spaces > 0; spaces --)
    {
        putc(' ', g_test_output);
    }
    
    if(result)
    {
        fprintf(g_test_output, "%s\n", g_results[1]);
        this_test_case->tests_passed ++;
    }
    else
    {
        fprintf(g_test_output, "%s\n", g_results[0]);
        this_test_case->tests_failed ++;
    }        
}

/******************************************************************************/
int main(
    int argc, 
    char** argv
)
{
    unit_test_case_t ** test_case = unit_test_case_list;
    unsigned passed, failed;
    passed = 0;
    failed = 0;
    
    g_test_output = stdout;
    
    
    /* Iterate through all the tests */
    while(NULL != (*test_case))
    {
        /* Print separators and test case name */
        fprintf(g_test_output, "\n%s\n", g_separator);
        fprintf(g_test_output, "Test case: %s\n", (*test_case)->name);
        fprintf(g_test_output, "%s\n", g_separator);
        
        /* Zero the test counters */
        (*test_case)->tests_failed = 0;
        (*test_case)->tests_passed = 0;
        
        /* Perform test */
        (*test_case)->test_fcn(*test_case);
        
        /* Print test case results */
        fprintf(g_test_output, "%s\n", g_separator);
        fprintf(g_test_output, 
            "'%s' results: %i passed, %i failed\n", 
            (*test_case)->name, 
            (*test_case)->tests_passed, (*test_case)->tests_failed);
        //fprintf(g_test_output, "%s\n", g_separator);

        /* Count results */
        if(0 == (*test_case)->tests_failed)
            passed ++;
        else
            failed ++;        

        /* Move to another test case */
        test_case ++;
    }
    
    /* Print overall results */
    fprintf(g_test_output, "\n\n%s\n", g_separator);
    fprintf(g_test_output, 
        "Test finished. Results: %i case(s) passed, %i case(s) failed\n", 
        passed, failed);
    
        
    return 0;
}