#include "../../inc/minishell.h"
#include "../Unity/src/unity.h"

char *strp[] = {"A dog", "A cat", "A horse", NULL};

void setUp(void) {
}

void tearDown(void) {
}

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

void test_ft_search_str_test_valid_array_first_element_NULL(void)
{
	char *exp = "A kitty";
	char **array = {NULL, exp};
	TEST_ASSERT_EQUAL_STRING(NULL, ft_search_str(array, exp));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ft_search_str_should_find);
	RUN_TEST(test_ft_search_str_should_NOT_find);
	RUN_TEST(test_ft_search_str_test_NULL);
	RUN_TEST(test_ft_search_str_test_valid_array_first_element_NULL);
	return UNITY_END();
}