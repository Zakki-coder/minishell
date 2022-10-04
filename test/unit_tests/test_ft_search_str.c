#include "../../inc/minishell.h"
#include "../Unity/src/unity.h"
#include "test.h"

char *strp[] = {"A dog", "A cat", "A horse", NULL};

void test_ft_search_str_should_find(void)
{
	char *exp = "A dog";
	TEST_ASSERT_EQUAL_STRING(exp, ft_search_str(strp, exp));
}

void test_ft_search_str_should_NOT_find(void)
{
	char *exp = "A batman";
	TEST_ASSERT_EQUAL_STRING(NULL, ft_search_str(strp, exp));
}

void test_ft_search_str_test_NULL(void)
{
	char *exp = NULL;
	TEST_ASSERT_EQUAL_STRING(NULL, ft_search_str(NULL, "A dawg"));
}

int main(void) {
	UNITY_BEGIN();
//	RUN_TEST(test_ft_search_str_should_find);
//	RUN_TEST(test_ft_search_str_should_NOT_find);
//	RUN_TEST(test_ft_search_str_test_NULL);
	/*chop_args*/
	RUN_TEST(test_chop_args_without_quotes_one_argument);
	RUN_TEST(test_chop_args_without_quotes_two_argument);
	RUN_TEST(test_chop_args_without_quotes_multiple_argument);
	RUN_TEST(test_chop_args_without_quotes_single_single);
	RUN_TEST(test_chop_args_with_weak_quotes_single_argument);
	RUN_TEST(test_chop_args_with_weak_quotes_touchin_quotes);
	RUN_TEST(test_chop_args_with_two_weak_quotes_seperated_by_space);
	RUN_TEST(test_chop_args_with_weak_quotes_mix);
	RUN_TEST(test_chop_args_with_mixed_quotes);
	RUN_TEST(test_chop_args_with_interesting_input);
	RUN_TEST(test_chop_args_with_interesting_input2);
	RUN_TEST(test_chop_args_with_interesting_input3);
	RUN_TEST(test_chop_args_with_interesting_input4);
	return UNITY_END();
}