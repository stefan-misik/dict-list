#include "../unit_test.h"

UNIT_TEST_CASE(case1)
{
    unit_test_eq("First test", 1, 1);
    unit_test_eq("Second test", 2, 1);
}

UNIT_TEST_CASE(case2)
{
    unit_test_eq("First test", 1, 1);
    unit_test_neq("Second test", 2, 1);
}


unit_test_case_t * unit_test_case_list[] = 
{
    UNIT_TEST_CASE_ENTRY(case1),
    UNIT_TEST_CASE_ENTRY(case2),
    NULL
};