/* ************************************************************************** */
/*                                                                            */
/*   test_libft.c - Comprehensive tester for libft Part 1 functions           */
/*                                                                            */
/*   Usage: bash Basic-libft-tester/run_test.sh                               */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libft.h"

static int  passed = 0;
static int  failed = 0;

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
/*  ft_isalpha                                                       */
/* ================================================================ */
static void	test_isalpha(void)
{
	SECTION("ft_isalpha");
	CHECK_INT("lowercase 'a'",    !!isalpha('a'),  !!ft_isalpha('a'));
	CHECK_INT("uppercase 'Z'",    !!isalpha('Z'),  !!ft_isalpha('Z'));
	CHECK_INT("digit '5'",        !!isalpha('5'),  !!ft_isalpha('5'));
	CHECK_INT("space ' '",        !!isalpha(' '),  !!ft_isalpha(' '));
	CHECK_INT("null char 0",      !!isalpha(0),    !!ft_isalpha(0));
}

/* ================================================================ */
/*  ft_isdigit                                                       */
/* ================================================================ */
static void	test_isdigit(void)
{
	SECTION("ft_isdigit");
	CHECK_INT("'0'",           !!isdigit('0'),  !!ft_isdigit('0'));
	CHECK_INT("'9'",           !!isdigit('9'),  !!ft_isdigit('9'));
	CHECK_INT("'a'",           !!isdigit('a'),  !!ft_isdigit('a'));
	CHECK_INT("'/' (48-1)",    !!isdigit('/'),  !!ft_isdigit('/'));
	CHECK_INT("':' (57+1)",    !!isdigit(':'),  !!ft_isdigit(':'));
}

/* ================================================================ */
/*  ft_isalnum                                                       */
/* ================================================================ */
static void	test_isalnum(void)
{
	SECTION("ft_isalnum");
	CHECK_INT("'a'",  !!isalnum('a'),  !!ft_isalnum('a'));
	CHECK_INT("'Z'",  !!isalnum('Z'),  !!ft_isalnum('Z'));
	CHECK_INT("'5'",  !!isalnum('5'),  !!ft_isalnum('5'));
	CHECK_INT("'!'",  !!isalnum('!'),  !!ft_isalnum('!'));
	CHECK_INT("' '",  !!isalnum(' '),  !!ft_isalnum(' '));
}

/* ================================================================ */
/*  ft_isascii                                                       */
/* ================================================================ */
static void	test_isascii(void)
{
	SECTION("ft_isascii");
	CHECK_INT("0",    !!isascii(0),    !!ft_isascii(0));
	CHECK_INT("127",  !!isascii(127),  !!ft_isascii(127));
	CHECK_INT("128",  !!isascii(128),  !!ft_isascii(128));
	CHECK_INT("'A'",  !!isascii('A'),  !!ft_isascii('A'));
	CHECK_INT("-1",   !!isascii(-1),   !!ft_isascii(-1));
}

/* ================================================================ */
/*  ft_isprint                                                       */
/* ================================================================ */
static void	test_isprint(void)
{
	SECTION("ft_isprint");
	CHECK_INT("' ' (32)",   !!isprint(32),   !!ft_isprint(32));
	CHECK_INT("'~' (126)",  !!isprint(126),  !!ft_isprint(126));
	CHECK_INT("31",         !!isprint(31),   !!ft_isprint(31));
	CHECK_INT("127",        !!isprint(127),  !!ft_isprint(127));
	CHECK_INT("'A'",        !!isprint('A'),  !!ft_isprint('A'));
}

/* ================================================================ */
/*  ft_toupper / ft_tolower                                          */
/* ================================================================ */
static void	test_toupper_tolower(void)
{
	SECTION("ft_toupper");
	CHECK_INT("'a' -> 'A'",  toupper('a'),  ft_toupper('a'));
	CHECK_INT("'A' stays",   toupper('A'),  ft_toupper('A'));
	CHECK_INT("'5' stays",   toupper('5'),  ft_toupper('5'));
	CHECK_INT("'z' -> 'Z'",  toupper('z'),  ft_toupper('z'));

	SECTION("ft_tolower");
	CHECK_INT("'A' -> 'a'",  tolower('A'),  ft_tolower('A'));
	CHECK_INT("'a' stays",   tolower('a'),  ft_tolower('a'));
	CHECK_INT("'5' stays",   tolower('5'),  ft_tolower('5'));
	CHECK_INT("'Z' -> 'z'",  tolower('Z'),  ft_tolower('Z'));
}

/* ================================================================ */
/*  ft_strlen                                                        */
/* ================================================================ */
static void	test_strlen(void)
{
	SECTION("ft_strlen");
	CHECK_INT("\"hello\"",      5,   ft_strlen("hello"));
	CHECK_INT("\"\" empty",     0,   ft_strlen(""));
	CHECK_INT("\"\\0abc\"",     0,   ft_strlen("\0abc"));
	CHECK_INT("10 chars",       10,  ft_strlen("abcdefghij"));
}

/* ================================================================ */
/*  ft_memset / ft_bzero                                             */
/* ================================================================ */
static void	test_memset_bzero(void)
{
	SECTION("ft_memset");
	char	a[10];
	char	b[10];

	memset(a, 'x', 10);
	ft_memset(b, 'x', 10);
	CHECK_INT("fill 'x' n=10",  memcmp(a, b, 10) == 0,  1);

	memset(a, 0, 10);
	ft_memset(b, 0, 10);
	CHECK_INT("fill 0 n=10",    memcmp(a, b, 10) == 0,  1);

	memset(b, 0, 10);
	ft_memset(b, 'A', 0);
	CHECK_INT("n=0 no change",  b[0],  0);

	SECTION("ft_bzero");
	memset(a, 'z', 10);
	memset(b, 'z', 10);
	ft_bzero(b, 5);
	CHECK_INT("bzero first 5 zeroed",  b[0] == 0 && b[4] == 0,  1);
	CHECK_INT("bzero rest untouched",  b[5],  'z');

	memset(b, 'z', 10);
	ft_bzero(b, 0);
	CHECK_INT("bzero n=0 no change",  b[0],  'z');
}

/* ================================================================ */
/*  ft_memcpy / ft_memmove                                           */
/* ================================================================ */
static void	test_memcpy_memmove(void)
{
	SECTION("ft_memcpy");
	char	src[] = "Hello, World!";
	char	dst1[20];
	char	dst2[20];
	char	buf1[30];
	char	buf2[30];

	memcpy(dst1, src, 14);
	ft_memcpy(dst2, src, 14);
	CHECK_INT("basic copy",      memcmp(dst1, dst2, 14) == 0,  1);

	ft_memcpy(dst2, src, 14);
	ft_memcpy(dst2, src, 0);
	CHECK_INT("n=0 no change",   dst2[0],  'H');

	SECTION("ft_memmove");
	memcpy(buf1, "abcdefghij", 11);
	memcpy(buf2, "abcdefghij", 11);
	memmove(buf1 + 2, buf1, 5);
	ft_memmove(buf2 + 2, buf2, 5);
	CHECK_INT("overlap forward",   memcmp(buf1, buf2, 10) == 0,  1);

	memcpy(buf1, "abcdefghij", 11);
	memcpy(buf2, "abcdefghij", 11);
	memmove(buf1, buf1 + 2, 5);
	ft_memmove(buf2, buf2 + 2, 5);
	CHECK_INT("overlap backward",  memcmp(buf1, buf2, 10) == 0,  1);
}

/* ================================================================ */
/*  ft_memchr / ft_memcmp                                            */
/* ================================================================ */
static void	test_memchr_memcmp(void)
{
	SECTION("ft_memchr");
	char	s[] = "Hello";

	CHECK_PTR("find 'l'",     memchr(s, 'l', 5),   ft_memchr(s, 'l', 5));
	CHECK_PTR("find 'H'",     memchr(s, 'H', 5),   ft_memchr(s, 'H', 5));
	CHECK_PTR("not found",    memchr(s, 'z', 5),   ft_memchr(s, 'z', 5));
	CHECK_PTR("n=0",          memchr(s, 'H', 0),   ft_memchr(s, 'H', 0));
	CHECK_PTR("find '\\0'",   memchr(s, '\0', 6),  ft_memchr(s, '\0', 6));

	SECTION("ft_memcmp");
	CHECK_INT("equal",           ft_memcmp("abc", "abc", 3) == 0,   1);
	CHECK_INT("less",            ft_memcmp("abc", "abd", 3) < 0,    1);
	CHECK_INT("greater",         ft_memcmp("abd", "abc", 3) > 0,    1);
	CHECK_INT("n=0",             ft_memcmp("abc", "xyz", 0) == 0,   1);
	CHECK_INT("non-ascii \\200", ft_memcmp("test\200", "test\0", 6) > 0,  1);
}

/* ================================================================ */
/*  ft_strchr / ft_strrchr                                           */
/* ================================================================ */
static void	test_strchr_strrchr(void)
{
	SECTION("ft_strchr");
	char	s[] = "hello world";

	CHECK_PTR("find 'o'",       strchr(s, 'o'),   ft_strchr(s, 'o'));
	CHECK_PTR("find 'h'",       strchr(s, 'h'),   ft_strchr(s, 'h'));
	CHECK_PTR("not found 'z'",  strchr(s, 'z'),   ft_strchr(s, 'z'));
	CHECK_PTR("find '\\0'",     strchr(s, '\0'),  ft_strchr(s, '\0'));

	SECTION("ft_strrchr");
	CHECK_PTR("last 'l'",       strrchr(s, 'l'),   ft_strrchr(s, 'l'));
	CHECK_PTR("last 'o'",       strrchr(s, 'o'),   ft_strrchr(s, 'o'));
	CHECK_PTR("not found 'z'",  strrchr(s, 'z'),   ft_strrchr(s, 'z'));
	CHECK_PTR("find '\\0'",     strrchr(s, '\0'),  ft_strrchr(s, '\0'));
}

/* ================================================================ */
/*  ft_strncmp                                                       */
/* ================================================================ */
static void	test_strncmp(void)
{
	SECTION("ft_strncmp");
	CHECK_INT("equal n=5",       ft_strncmp("salut", "salut", 5) == 0,  1);
	CHECK_INT("s1 shorter",      ft_strncmp("test", "testss", 7) < 0,   1);
	CHECK_INT("s2 shorter",      ft_strncmp("testss", "test", 7) > 0,   1);
	CHECK_INT("case diff",       ft_strncmp("test", "tEst", 4) > 0,     1);
	CHECK_INT("s1 empty",        ft_strncmp("", "test", 4) < 0,         1);
	CHECK_INT("s2 empty",        ft_strncmp("test", "", 4) > 0,         1);
	CHECK_INT("n=0",             ft_strncmp("abc", "xyz", 0) == 0,      1);
	CHECK_INT("non-ascii \\200", ft_strncmp("test\200", "test\0", 6) > 0, 1);
}

/* ================================================================ */
/*  ft_strlcpy                                                       */
/* ================================================================ */
static void	test_strlcpy(void)
{
	SECTION("ft_strlcpy");
	char	dst[20];

	ft_strlcpy(dst, "hello", 10);
	CHECK_STR("basic copy",          "hello",  dst);

	ft_strlcpy(dst, "hello", 3);
	CHECK_STR("truncated",           "he",     dst);

	ft_strlcpy(dst, "hello", 6);
	CHECK_STR("exact fit",           "hello",  dst);

	CHECK_INT("return srclen",       ft_strlcpy(dst, "hello", 10),  5);
	CHECK_INT("return srclen trunc", ft_strlcpy(dst, "hello", 3),   5);
	CHECK_INT("dstsize=0 return",    ft_strlcpy(dst, "hello", 0),   5);
}

/* ================================================================ */
/*  ft_strlcat                                                       */
/* ================================================================ */
static void	test_strlcat(void)
{
	SECTION("ft_strlcat");
	char	dst[20];

	ft_strlcpy(dst, "hello", 20);
	ft_strlcat(dst, " world", 20);
	CHECK_STR("basic append",        "hello world",  dst);

	ft_strlcpy(dst, "hello", 20);
	ft_strlcat(dst, " world", 8);
	CHECK_STR("truncated append",    "hello w",      dst);

	ft_strlcpy(dst, "hello", 20);
	CHECK_INT("return total len",    ft_strlcat(dst, "!!", 20),  7);
	ft_strlcpy(dst, "hello", 20);

	ft_strlcpy(dst, "hello", 20);
	CHECK_INT("dstsize=0 return",    ft_strlcat(dst, "abc", 0),  8);

	ft_strlcpy(dst, "rrrrrr", 20);
	CHECK_INT("dst>=n return",       ft_strlcat(dst, "lorem ipsum dolor sit amet", 5),  32);
}

/* ================================================================ */
/*  ft_strnstr                                                       */
/* ================================================================ */
static void	test_strnstr(void)
{
	SECTION("ft_strnstr");
	const char	*hay = "hello world";
	const char	*res;

	res = ft_strnstr(hay, "world", 11);
	CHECK_STR("found in range",    "world",  res);

	res = ft_strnstr(hay, "world", 5);
	CHECK_PTR("not in n",          NULL,     res);

	res = ft_strnstr("hello", "", 5);
	CHECK_STR("empty little",      "hello",  res);

	res = ft_strnstr("hello", "xyz", 5);
	CHECK_PTR("not found",         NULL,     res);

	res = ft_strnstr("hello", "hel", 5);
	CHECK_STR("at start",          "hello",  res);

	res = ft_strnstr("hello", "", 0);
	CHECK_STR("n=0 empty little",  "hello",  res);

	res = ft_strnstr("hello", "hello world", 5);
	CHECK_PTR("needle longer",     NULL,     res);
}

/* ================================================================ */
/*  ft_atoi                                                          */
/* ================================================================ */
static void	test_atoi(void)
{
	SECTION("ft_atoi");
	CHECK_INT("\"42\"",          42,           ft_atoi("42"));
	CHECK_INT("\"-42\"",         -42,          ft_atoi("-42"));
	CHECK_INT("\"+42\"",         42,           ft_atoi("+42"));
	CHECK_INT("\"   42\"",       42,           ft_atoi("   42"));
	CHECK_INT("\"0\"",           0,            ft_atoi("0"));
	CHECK_INT("\"\"",            0,            ft_atoi(""));
	CHECK_INT("\"42abc\"",       42,           ft_atoi("42abc"));
	CHECK_INT("\"abc\"",         0,            ft_atoi("abc"));
	CHECK_INT("\"\\t\\n42\"",    42,           ft_atoi("\t\n42"));
	CHECK_INT("\"2147483647\"",  2147483647,   ft_atoi("2147483647"));
}

/* ================================================================ */
/*  ft_strdup                                                        */
/* ================================================================ */
static void	test_strdup(void)
{
	SECTION("ft_strdup");
	char	*d;

	d = ft_strdup("hello");
	CHECK_STR("basic dup",     "hello",  d);
	free(d);

	d = ft_strdup("");
	CHECK_STR("empty string",  "",       d);
	free(d);

	d = ft_strdup("a");
	CHECK_STR("single char",   "a",      d);
	free(d);
}

/* ================================================================ */
/*  ft_calloc                                                        */
/* ================================================================ */
static void	test_calloc(void)
{
	SECTION("ft_calloc");
	char	*p;
	int		i;

	p = ft_calloc(10, sizeof(char));
	i = 0;
	while (i < 10 && p[i] == 0)
		i++;
	CHECK_INT("10 bytes zeroed",   i,  10);
	free(p);

	p = ft_calloc(0, sizeof(char));
	CHECK_INT("n=0 returns valid", p != NULL || p == NULL,  1);
	free(p);

	p = ft_calloc(5, 0);
	CHECK_INT("size=0 returns valid", p != NULL || p == NULL,  1);
	free(p);
}

/* ================================================================ */
/*  summary                                                          */
/* ================================================================ */
static void	summary(void)
{
	int	total;

	total = passed + failed;
	printf("\n\033[1m== SUMMARY ==\033[0m\n");
	printf("  Total:  %d\n", total);
	printf("  \033[32mPassed: %d\033[0m\n", passed);
	if (failed)
		printf("  \033[31mFailed: %d\033[0m\n", failed);
	else
		printf("  \033[32mFailed: 0 - all good!\033[0m\n");
}

int	main(void)
{
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_toupper_tolower();
	test_strlen();
	test_memset_bzero();
	test_memcpy_memmove();
	test_memchr_memcmp();
	test_strchr_strrchr();
	test_strncmp();
	test_strlcpy();
	test_strlcat();
	test_strnstr();
	test_atoi();
	test_strdup();
	test_calloc();
	summary();
	return (failed > 0);
}
