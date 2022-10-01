#include "../../inc/minishell.h"
#include "../Unity/src/unity.h"

extern **strp = {"A dog", "A cat", "A horse", NULL};

void setUp(void) {
}

void tearDown(void) {
}

test_ft_search_str_should_find();
{
	char *exp = "A dog"
	TEST_ASSERT_EQUAL_STRING(exp, ft_search_str(strp, exp));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ft_search_str_should_find);
	return UNITY_END();
}