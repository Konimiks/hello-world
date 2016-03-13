//Дико извиняюсь, что не залил вовремя, отсутствовал интернет в период с пятницы по воскресенье

#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "module.h"

//list_new
static void new_void_zeroCount(void **state)
{
    list_t * list = list_new();
    assert_int_equal(list_getCount(list), 0);
    list_free(list);
}

//list_add
static void add_oneValue_countOne(void **state)
{
    list_t * list = list_new();
    list_add(list, 5, -3);
    assert_int_equal(list_getCount(list), 0);
    list_add(list, 5, 4);
    assert_int_equal(list_getCount(list), 0);
    list_add(list, 5, 0);
    assert_int_equal(list_getCount(list), 1);
    list_free(list);
}

//list_add
static void add_twoValue_countTwo(void **state)
{
    list_t * list = list_new();
    list_add(list, 5, 0);
    assert_int_equal(list_getCount(list), 1);
    list_add(list, 5, 1);
    assert_int_equal(list_getCount(list), 2);
    list_free(list);
}

//list_delete
static void delete_oneValue_zeroCount(void **state)
{
    list_t * list = list_new();
    list_add(list, 5, 0);
    list_delete(list, 3);
    assert_int_equal(list_getCount(list), 1);
    list_delete(list, -5);
    assert_int_equal(list_getCount(list), 1);
    list_delete(list, 0);
    assert_int_equal(list_getCount(list), 0);
    list_free(list);
}

//list_get_count_positive
static void getCountPositive_onePositiveValue_countOne(void ** state)
{
    list_t * list = list_new();
    list_add(list, -5, 0);
    assert_int_equal(list_get_count_positive(list), 0);
    list_add(list, 45, 0);
    assert_int_equal(list_get_count_positive(list), 1);
    list_free(list);
}

//list_get_count_negative
static void getCountNegative_oneNegativeValue_countOne(void ** state)
{
    list_t * list = list_new();
    list_add(list, 5, 0);
    assert_int_equal(list_get_count_negative(list), 0);
    list_add(list, -45, 0);
    assert_int_equal(list_get_count_negative(list), 1);
    list_free(list);
}

//list_get_count_zero
static void getCountZero_oneZeroValue_countOne(void ** state)
{
    list_t * list = list_new();
    list_add(list, -5, 0);
    assert_int_equal(list_get_count_zero(list), 0);
    list_add(list, 0, 0);
    assert_int_equal(list_get_count_zero(list), 1);
    list_free(list);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_zeroCount),
        cmocka_unit_test(add_oneValue_countOne),
        cmocka_unit_test(add_twoValue_countTwo),
        cmocka_unit_test(delete_oneValue_zeroCount),
        cmocka_unit_test(getCountPositive_onePositiveValue_countOne),
        cmocka_unit_test(getCountNegative_oneNegativeValue_countOne),
        cmocka_unit_test(getCountZero_oneZeroValue_countOne),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
