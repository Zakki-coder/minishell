#include "../../inc/minishell.h"
#include "../Unity/src/unity.h"
#include "test.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_chop_args_without_quotes_one_argument()
{
	char *input = "Hello";
	char *exp[] = {"Hello", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * 2);
	ret[1] = NULL;
	chop_line(input, ret, 2);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, 2);
}

void test_chop_args_without_quotes_two_argument()
{
	int	size = 3;
	char *input = "Hello World";
	char *exp[] = {"Hello", "World", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_without_quotes_multiple_argument()
{
	int	size = 6;
	char *input = "a Hello World a bananas";
	char *exp[] = {"a", "Hello", "World", "a", "bananas", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_without_quotes_single_single()
{
	int	size = 2;
	char *input = "a";
	char *exp[] = {"a", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_weak_quotes_single_argument()
{
	int	size = 2;
	char *input = "\"a\"";
	char *exp[] = {"\"a\"", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_weak_quotes_touchin_quotes()
{
	int	size = 2;
	char *input = "\"a\"\"a\"";
	char *exp[] = {"\"a\"\"a\"", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_two_weak_quotes_seperated_by_space()
{
	int	size = 3;
	char *input = "\"a\" \"a\"";
	char *exp[] = {"\"a\"", "\"a\"", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_weak_quotes_mix()
{
	int	size = 2;
	char *input = "\"1\"\"1\"\"1\"\"1";
	char *exp[] = {"\"1\"\"1\"\"1\"\"1", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_mixed_quotes()
{
	int	size = 2;
	char *input = "\'1\'\"1\"\"1\'\'1";
	char *exp[] = {"\'1\'\"1\"\"1\'\'1", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_interesting_input()
{
	int	size = 2;
	char *input = "\'hi\'mom\"MOM\"";
	char *exp[] = {"\'hi\'mom\"MOM\"", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_interesting_input2()
{
	int	size = 2;
	char *input = "hi\' .    asf    \'mom";
	char *exp[] = {"hi\' .    asf    \'mom", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_interesting_input3()
{
	int	size = 3;
	char *input = "hi\' .    asf    \'mom Helloooo   ";
	char *exp[] = {"hi\' .    asf    \'mom", "Helloooo", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}

void test_chop_args_with_interesting_input4()
{
	int	size = 3;
	char *input = "hi\' .    asf    \'mom \"Helloooo   \"";
	char *exp[] = {"hi\' .    asf    \'mom", "\"Helloooo   \"", NULL};
	char **ret = (char **)malloc(sizeof(*ret) * size);
	ret[size - 1] = NULL;
	chop_line(input, ret, size);
	TEST_ASSERT_EQUAL_STRING_ARRAY (exp, ret, size);
}