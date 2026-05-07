/* ************************************************************************** */
/*                                                                            */
/*   test_libft_part2.c - Tester for libft Part 2 additional functions        */
/*                                                                            */
/*   Usage: bash Basic-libft-tester/run_test_part2.sh                         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

static int  passed = 0;
static int  failed = 0;

/* ---- helpers ---- */

static void ok(const char *test)
{
	printf("  \033[32m[OK]\033[0m %s\n", test);
	passed++;
}

static void ko(const char *test, const char *expected, const char *got)
{
	printf("  \033[31m[KO]\033[0m %s  (expected: %s | got: %s)\n", test, expected, got);
	failed++;
}

#define CHECK_INT(label, expected, got) \
	do { \
		char e[32], g[32]; \
		snprintf(e, sizeof(e), "%d", (int)(expected)); \
		snprintf(g, sizeof(g), "%d", (int)(got)); \
		if ((int)(expected) == (int)(got)) ok(label); \
		else ko(label, e, g); \
	} while (0)

#define CHECK_STR(label, expected, got) \
	do { \
		const char *e = (expected); \
		const char *g = (got); \
		if (e && g && strcmp(e, g) == 0) ok(label); \
		else if (!e && !g) ok(label); \
		else ko(label, e ? e : "(null)", g ? g : "(null)"); \
	} while (0)

#define CHECK_PTR(label, expected, got) \
	do { \
		if ((void *)(expected) == (void *)(got)) ok(label); \
		else { \
			char e[32], g[32]; \
			snprintf(e, sizeof(e), "%p", (void *)(expected)); \
			snprintf(g, sizeof(g), "%p", (void *)(got)); \
			ko(label, e, g); \
		} \
	} while (0)

#define SECTION(name) printf("\n\033[1;34m== %s ==\033[0m\n", name)

/* ================================================================ */
/*  ft_substr                                                        */
/* ================================================================ */
static void test_substr(void)
{
	SECTION("ft_substr");
	char	*res;

	res = ft_substr("hello world", 6, 5);
	CHECK_STR("basic substr",              "world",  res);
	free(res);

	res = ft_substr("hello", 0, 5);
	CHECK_STR("full string",               "hello",  res);
	free(res);

	res = ft_substr("hello", 0, 3);
	CHECK_STR("partial from start",        "hel",    res);
	free(res);

	res = ft_substr("hello", 2, 3);
	CHECK_STR("partial from middle",       "llo",    res);
	free(res);

	res = ft_substr("hello", 0, 100);
	CHECK_STR("len longer than string",    "hello",  res);
	free(res);

	res = ft_substr("hello", 10, 5);
	CHECK_STR("start beyond string",       "",       res);
	free(res);

	res = ft_substr("hello", 0, 0);
	CHECK_STR("len is 0",                  "",       res);
	free(res);

	res = ft_substr("", 0, 5);
	CHECK_STR("empty string",              "",       res);
	free(res);
}

/* ================================================================ */
/*  ft_strjoin                                                       */
/* ================================================================ */
static void test_strjoin(void)
{
	SECTION("ft_strjoin");
	char	*res;

	res = ft_strjoin("hello", " world");
	CHECK_STR("basic join",                "hello world",  res);
	free(res);

	res = ft_strjoin("", "world");
	CHECK_STR("empty s1",                  "world",        res);
	free(res);

	res = ft_strjoin("hello", "");
	CHECK_STR("empty s2",                  "hello",        res);
	free(res);

	res = ft_strjoin("", "");
	CHECK_STR("both empty",                "",             res);
	free(res);

	res = ft_strjoin("foo", "bar");
	CHECK_STR("no space join",             "foobar",       res);
	free(res);
}

/* ================================================================ */
/*  ft_strtrim                                                       */
/* ================================================================ */
static void test_strtrim(void)
{
	SECTION("ft_strtrim");
	char	*res;

	res = ft_strtrim("  hello  ", " ");
	CHECK_STR("trim spaces",               "hello",        res);
	free(res);

	res = ft_strtrim("xxhelloxx", "x");
	CHECK_STR("trim x chars",             "hello",         res);
	free(res);

	res = ft_strtrim("hello", " ");
	CHECK_STR("nothing to trim",           "hello",        res);
	free(res);

	res = ft_strtrim("   ", " ");
	CHECK_STR("all chars trimmed",         "",             res);
	free(res);

	res = ft_strtrim("", " ");
	CHECK_STR("empty string",             "",              res);
	free(res);

	res = ft_strtrim("abcba", "ab");
	CHECK_STR("trim multiple chars",       "c",            res);
	free(res);

	res = ft_strtrim("hello", "");
	CHECK_STR("empty set no trim",         "hello",        res);
	free(res);

	res = ft_strtrim("  hello world  ", " ");
	CHECK_STR("trim preserves middle spaces", "hello world", res);
	free(res);
}

/* ================================================================ */
/*  ft_split                                                         */
/* ================================================================ */
static void test_split(void)
{
	SECTION("ft_split");
	char	**res;
	int		i;

	res = ft_split("hello world foo", ' ');
	CHECK_STR("split[0]",                  "hello",  res[0]);
	CHECK_STR("split[1]",                  "world",  res[1]);
	CHECK_STR("split[2]",                  "foo",    res[2]);
	CHECK_PTR("split NULL terminated",     NULL,     res[3]);
	i = 0; while (res[i]) free(res[i++]); free(res);

	res = ft_split("  hello  world  ", ' ');
	CHECK_STR("multiple delimiters [0]",   "hello",  res[0]);
	CHECK_STR("multiple delimiters [1]",   "world",  res[1]);
	CHECK_PTR("NULL terminated",           NULL,     res[2]);
	i = 0; while (res[i]) free(res[i++]); free(res);

	res = ft_split("hello", ' ');
	CHECK_STR("no delimiter in string",    "hello",  res[0]);
	CHECK_PTR("NULL terminated",           NULL,     res[1]);
	i = 0; while (res[i]) free(res[i++]); free(res);

	res = ft_split("", ' ');
	CHECK_PTR("empty string returns NULL", NULL,     res[0]);
	free(res);

	res = ft_split("   ", ' ');
	CHECK_PTR("only delimiters",           NULL,     res[0]);
	free(res);

	res = ft_split("a,b,c,d", ',');
	CHECK_STR("comma delimiter [0]",       "a",      res[0]);
	CHECK_STR("comma delimiter [1]",       "b",      res[1]);
	CHECK_STR("comma delimiter [2]",       "c",      res[2]);
	CHECK_STR("comma delimiter [3]",       "d",      res[3]);
	CHECK_PTR("NULL terminated",           NULL,     res[4]);
	i = 0; while (res[i]) free(res[i++]); free(res);
}

/* ================================================================ */
/*  ft_itoa                                                          */
/* ================================================================ */
static void test_itoa(void)
{
	SECTION("ft_itoa");
	char	*res;

	res = ft_itoa(42);
	CHECK_STR("positive number",           "42",           res);
	free(res);

	res = ft_itoa(-42);
	CHECK_STR("negative number",           "-42",          res);
	free(res);

	res = ft_itoa(0);
	CHECK_STR("zero",                      "0",            res);
	free(res);

	res = ft_itoa(2147483647);
	CHECK_STR("INT_MAX",                   "2147483647",   res);
	free(res);

	res = ft_itoa(-2147483648);
	CHECK_STR("INT_MIN",                   "-2147483648",  res);
	free(res);

	res = ft_itoa(100);
	CHECK_STR("round number",             "100",           res);
	free(res);

	res = ft_itoa(-1);
	CHECK_STR("negative one",             "-1",            res);
	free(res);
}

/* ================================================================ */
/*  ft_strmapi                                                       */
/* ================================================================ */

static char	to_upper_indexed(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static char	alternate_case(unsigned int i, char c)
{
	if (i % 2 == 0)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
	}
	return (c);
}

static void test_strmapi(void)
{
	SECTION("ft_strmapi");
	char	*res;

	res = ft_strmapi("hello", to_upper_indexed);
	CHECK_STR("uppercase all",             "HELLO",  res);
	free(res);

	res = ft_strmapi("", to_upper_indexed);
	CHECK_STR("empty string",              "",       res);
	free(res);

	res = ft_strmapi("hello", alternate_case);
	CHECK_STR("alternate case",            "HeLlO",  res);
	free(res);

	res = ft_strmapi("12345", to_upper_indexed);
	CHECK_STR("digits unchanged",          "12345",  res);
	free(res);
}

/* ================================================================ */
/*  ft_striteri                                                      */
/* ================================================================ */

static void to_upper_inplace(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

static void alternate_inplace(unsigned int i, char *c)
{
	if (i % 2 != 0)
		if (*c >= 'a' && *c <= 'z')
			*c -= 32;
}

static void test_striteri(void)
{
	SECTION("ft_striteri");
	char	s1[] = "hello";
	char	s2[] = "hello";
	char	s3[] = "";

	ft_striteri(s1, to_upper_inplace);
	CHECK_STR("uppercase in place",        "HELLO",  s1);

	ft_striteri(s2, alternate_inplace);
	CHECK_STR("alternate case in place",   "hElLo",  s2);

	ft_striteri(s3, to_upper_inplace);
	CHECK_STR("empty string no crash",     "",       s3);
}

/* ================================================================ */
/*  ft_putchar_fd                                                    */
/* ================================================================ */
static void test_putchar_fd(void)
{
	SECTION("ft_putchar_fd");
	/* write to stderr (fd 2) so we can at least confirm no crash */
	printf("  (writing 'A' to stderr via ft_putchar_fd): ");
	fflush(stdout);
	ft_putchar_fd('A', 2);
	fprintf(stderr, "\n");
	ok("ft_putchar_fd no crash on fd=2");

	ft_putchar_fd('Z', 1);
	write(1, "\n", 1);
	ok("ft_putchar_fd writes to stdout");
}

/* ================================================================ */
/*  ft_putstr_fd                                                     */
/* ================================================================ */
static void test_putstr_fd(void)
{
	SECTION("ft_putstr_fd");
	printf("  (writing 'hello' to stderr via ft_putstr_fd): ");
	fflush(stdout);
	ft_putstr_fd("hello", 2);
	fprintf(stderr, "\n");
	ok("ft_putstr_fd no crash on fd=2");

	ft_putstr_fd("world", 1);
	write(1, "\n", 1);
	ok("ft_putstr_fd writes to stdout");
}

/* ================================================================ */
/*  ft_putendl_fd                                                    */
/* ================================================================ */
static void test_putendl_fd(void)
{
	SECTION("ft_putendl_fd");
	printf("  (writing 'hello\\n' to stderr via ft_putendl_fd): ");
	fflush(stdout);
	ft_putendl_fd("hello", 2);
	ok("ft_putendl_fd no crash on fd=2");

	ft_putendl_fd("world", 1);
	ok("ft_putendl_fd writes to stdout with newline");
}

/* ================================================================ */
/*  ft_putnbr_fd                                                     */
/* ================================================================ */
static void test_putnbr_fd(void)
{
	SECTION("ft_putnbr_fd");
	printf("  (writing numbers to stderr): ");
	fflush(stdout);
	ft_putnbr_fd(42, 2);
	fprintf(stderr, " ");
	ft_putnbr_fd(-42, 2);
	fprintf(stderr, " ");
	ft_putnbr_fd(0, 2);
	fprintf(stderr, " ");
	ft_putnbr_fd(-2147483648, 2);
	fprintf(stderr, "\n");
	ok("ft_putnbr_fd positive, negative, zero, INT_MIN no crash");

	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);
	ok("ft_putnbr_fd INT_MAX to stdout");
}

/* ================================================================ */
/*  summary                                                          */
/* ================================================================ */
static void summary(void)
{
	int total = passed + failed;
	printf("\n\033[1m== SUMMARY ==\033[0m\n");
	printf("  Total:  %d\n", total);
	printf("  \033[32mPassed: %d\033[0m\n", passed);
	if (failed)
		printf("  \033[31mFailed: %d\033[0m\n", failed);
	else
		printf("  \033[32mFailed: 0 — all good!\033[0m\n");
}

int	main(void)
{
	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_itoa();
	test_strmapi();
	test_striteri();
	test_putchar_fd();
	test_putstr_fd();
	test_putendl_fd();
	test_putnbr_fd();
	summary();
	return (failed > 0);
}
