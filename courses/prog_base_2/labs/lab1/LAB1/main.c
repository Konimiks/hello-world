#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "folder.h"

static void new_folder_files_zeroCount(void ** state)
{
    folder_t * myFolder = folder_new("MyFolder");
    assert_int_equal(folder_get_files_count(myFolder), 0);
    folder_free(myFolder);
}

static void folder_add_new_file_filesCount_oneCount(void **state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch!");
    assert_int_equal(folder_get_files_count(myFolder), 1);
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    assert_int_equal(folder_get_files_count(myFolder), 0);
    folder_free(myFolder);
}

static void folder_add_new_file_filesCount_threeCount(void **state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch!");
    file_t * SecondFile = folder_add_new_file(myFolder, "This file is empty bitch!");
    file_t * ThirdFile = folder_add_new_file(myFolder, "This file is empty bitch!");
    assert_int_equal(folder_get_files_count(myFolder), 3);
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    folder_process_and_remove_files(myFolder, SecondFile, dictionary);
    folder_process_and_remove_files(myFolder, ThirdFile, dictionary);
    assert_int_equal(folder_get_files_count(myFolder), 0);
    folder_free(myFolder);
}

static void new_dictionary_wordsCount_zerowords(void ** state)
{
    dic_t * dictionary = dic_new();
    assert_int_equal(dic_getwordscount(dictionary), 0);
    dic_free(dictionary);
}

static void process_and_remove_file_wordscount_in_dictionary_fivewords(void ** state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch!");
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    assert_int_equal(dic_getwordscount(dictionary), 5);
    dic_free(dictionary);
    folder_free(myFolder);
}

static void process_and_remove_file_filesCount_zeroCount(void ** state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch! a b c d e r t y u w v n m l p");
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    assert_int_equal(folder_get_files_count(myFolder), 0);
    dic_free(dictionary);
    folder_free(myFolder);
}

static void process_and_remove_file_wordscount_in_dictionary_twentywords(void ** state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch! a b c d e r t y u w v n m l p");
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    assert_int_equal(dic_getwordscount(dictionary), 20);
    dic_free(dictionary);
    folder_free(myFolder);
}

static void process_and_remove_file_wordscount_in_dictionary_fivewords_and_one_word_passing_two_times(void ** state)
{
    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("MyFolder");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file file is empty bitch!");
    folder_process_and_remove_files(myFolder, FirstFile, dictionary);
    assert_int_equal(dic_getwordcount(dictionary, "file"), 2);
    assert_int_equal(dic_getwordscount(dictionary), 5);
    dic_free(dictionary);
    folder_free(myFolder);
}



int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_folder_files_zeroCount),
        cmocka_unit_test(folder_add_new_file_filesCount_oneCount),
        cmocka_unit_test(folder_add_new_file_filesCount_threeCount),
        cmocka_unit_test(new_dictionary_wordsCount_zerowords),
        cmocka_unit_test(process_and_remove_file_wordscount_in_dictionary_fivewords),
        cmocka_unit_test(process_and_remove_file_wordscount_in_dictionary_fivewords_and_one_word_passing_two_times),
        cmocka_unit_test(process_and_remove_file_wordscount_in_dictionary_twentywords),
        cmocka_unit_test(process_and_remove_file_filesCount_zeroCount),
    };

    dic_t * dictionary = dic_new();
    folder_t * myFolder = folder_new("Go");
    file_t * FirstFile = folder_add_new_file(myFolder, "This file is empty bitch!");

    file_t * SecondFile = folder_add_new_file(myFolder, "This file is not empty , first file also is not empty, bitch!alliluya");

    folder_process_and_remove_files(myFolder, FirstFile, dictionary);

    folder_process_and_remove_files(myFolder, SecondFile, dictionary);
    printf("dictionary:::\n");
    printdic(dictionary);

    folder_free(myFolder);

    dic_free(dictionary);

    return cmocka_run_group_tests(tests, NULL, NULL);

}
