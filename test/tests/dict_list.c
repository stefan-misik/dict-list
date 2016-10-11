#include "../unit_test.h"

UNIT_TEST_CASE(case1)
{
    unit_test_eq("First test", 1, 1);
    unit_test_eq("Second test", 2, 1);
}


unit_test_case_t * unit_test_case_list[] = 
{
    unit_test_case_case1,
    NULL
};