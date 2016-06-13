/*
Функція, що приймає строку (що означає текст) і підстроку і визначає,
чи міститься строка у підстроці. Якщо шукане слово переноситься у тексті
з одного рядка на інший - також вважати це входженням
*/
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

#include "func.h"

static void test_true_strInStrAtBegin(void **state)
{
    assert_int_equal(mystrstr("main", "mainf we"), 0);
}

static void test_true_strDelimeteredByNewLine(void **state){
    assert_int_equal(mystrstr("main", "ma\ninf we"), 0);
}

static void test_true_strInStrAtEnd(void **state){
    assert_int_equal(mystrstr("main", "3gewrg ergewr emain"), 0);
}

static void test_false_strInStrNotFound(void **state){
    assert_int_equal(mystrstr("main", "3gewr emaiwen"), -1);
}

static void test_true_spacetest(void **state){
    assert_int_equal(mystrstr(" ", "3gewr emaiwen"), 0);
}

int main(void){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_true_strInStrAtBegin),
        cmocka_unit_test(test_true_strDelimeteredByNewLine),
        cmocka_unit_test(test_true_strInStrAtEnd),
        cmocka_unit_test(test_false_strInStrNotFound),
        cmocka_unit_test(test_true_spacetest),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);

    return 0;
}
