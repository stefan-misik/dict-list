#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

#include <stddef.h>

/**
 * @brief Unit test information structure
 * 
 */
typedef struct unit_test_case
{
    const char * name;      /** < Name of the test */
    int tests_passed;       /** < Number of passed tests */
    int tests_failed;       /** < Number of failed test */
    void (*test_fcn)(struct unit_test_case *); /** < Test function */
} unit_test_case_t;

/**
 * @brief List of test cases
 * 
 */
extern unit_test_case_t * unit_test_case_list[];

/**
 * @brief Macro to create test function and its structure
 * 
 */
#define UNIT_TEST_CASE(name)                   \
    static void name ## _fcn(                  \
        unit_test_case_t * this_test_case      \
    );                                         \
    unit_test_case_t unit_test_case_ ## name = \
    {                                          \
        .name = #name,                         \
        .tests_passed = 0,                     \
        .tests_failed = 0,                     \
        .test_fcn = name ## _fcn               \
    };                                         \
    static void name ## _fcn(                  \
        testbench_test_t * this_test_case      \
    )                                               

/**
 * @brief Compare two numbers
 */
#define unit_test_eq(test_name, a, b)   \
    unit_test_result(                   \
        this_test_case,                 \
        (test_name),                    \
        (a) == (b))

/**
 * @brief Compare two numbers
 */
#define unit_test_neq(test_name, a, b)  \
    unit_test_result(                   \
        this_test_case,                 \
        (test_name),                    \
        (a) != (b))


/**
 * @brief write test result directly
 * 
 * @param[in] test_name String describing the test
 * @param[in] result    Result of the test 0 = failed, 1 = passed
 */
void unit_test_result(
    unit_test_case_t * this_test_case,
    const char * test_name,
    int result
);


#endif /* _UNIT_TEST_H */

