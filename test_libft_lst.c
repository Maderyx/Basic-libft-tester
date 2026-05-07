/* ************************************************************************** */
/*                                                                            */
/*   test_libft_lst.c - Tester for libft Part 3 linked list functions         */
/*                                                                            */
/*   Usage: bash Basic-libft-tester/run_test_lst.sh                           */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define CHECK_STR(label, expected, got) \
	do { \
		const char *e = (expected); \
		const char *g = (got); \
		if (e && g && strcmp(e, g) == 0) ok(label); \
		else if (!e && !g) ok(label); \
		else ko(label, e ? e : "(null)", g ? g : "(null)"); \
	} while (0)

#define SECTION(name) printf("\n\033[1;34m== %s ==\033[0m\n", name)

/* ---- del function for tests ---- */

static void del_content(void *content)
{
	free(content);
}

/* ---- helper to make a node with a strdup'd string ---- */

static t_list	*make_node(const char *s)
{
	return (ft_lstnew(strdup(s)));
}

/* ---- helper to get node content as string ---- */

static char	*node_str(t_list *node)
{
	if (!node)
		return (NULL);
	return ((char *)node->content);
}

/* ================================================================ */
/*  ft_lstnew                                                        */
/* ================================================================ */
static void test_lstnew(void)
{
	SECTION("ft_lstnew");
	t_list	*node;

	node = ft_lstnew(strdup("hello"));
	CHECK_STR("content set correctly",     "hello",  node_str(node));
	CHECK_PTR("next is NULL",              NULL,      node->next);
	del_content(node->content);
	free(node);

	node = ft_lstnew(NULL);
	CHECK_PTR("NULL content",              NULL,      node->content);
	CHECK_PTR("next is NULL on NULL node", NULL,      node->next);
	free(node);
}

/* ================================================================ */
/*  ft_lstadd_front                                                  */
/* ================================================================ */
static void test_lstadd_front(void)
{
	SECTION("ft_lstadd_front");
	t_list	*lst;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	lst = make_node("first");
	node2 = make_node("second");
	ft_lstadd_front(&lst, node2);
	CHECK_STR("new head after add_front",       "second",  node_str(lst));
	CHECK_STR("old head is now second node",    "first",   node_str(lst->next));
	CHECK_PTR("third node is NULL",             NULL,      lst->next->next);

	node3 = make_node("third");
	ft_lstadd_front(&lst, node3);
	CHECK_STR("second add_front new head",      "third",   node_str(lst));
	CHECK_STR("second node still correct",      "second",  node_str(lst->next));

	node1 = lst;
	ft_lstadd_front(NULL, node1);
	CHECK_STR("NULL lst pointer no crash",      "third",   node_str(lst));

	/* cleanup */
	del_content(lst->content); free(lst->next->next->content);
	free(lst->next->next); free(lst->next); free(lst);
	/* node1 was freed as part of lst */
}

/* ================================================================ */
/*  ft_lstsize                                                       */
/* ================================================================ */
static void test_lstsize(void)
{
	SECTION("ft_lstsize");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	CHECK_INT("NULL list size is 0",    0,  ft_lstsize(NULL));

	lst = make_node("a");
	CHECK_INT("single node size is 1",  1,  ft_lstsize(lst));

	n2 = make_node("b");
	lst->next = n2;
	CHECK_INT("two nodes size is 2",    2,  ft_lstsize(lst));

	n3 = make_node("c");
	n2->next = n3;
	CHECK_INT("three nodes size is 3",  3,  ft_lstsize(lst));

	del_content(lst->content); free(lst);
	del_content(n2->content);  free(n2);
	del_content(n3->content);  free(n3);
}

/* ================================================================ */
/*  ft_lstlast                                                       */
/* ================================================================ */
static void test_lstlast(void)
{
	SECTION("ft_lstlast");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	CHECK_PTR("NULL list returns NULL",  NULL,  ft_lstlast(NULL));

	lst = make_node("only");
	CHECK_PTR("single node is last",     lst,   ft_lstlast(lst));

	n2 = make_node("second");
	lst->next = n2;
	CHECK_PTR("last of two nodes",       n2,    ft_lstlast(lst));

	n3 = make_node("third");
	n2->next = n3;
	CHECK_PTR("last of three nodes",     n3,    ft_lstlast(lst));
	CHECK_STR("last content correct",    "third", node_str(ft_lstlast(lst)));

	del_content(lst->content); free(lst);
	del_content(n2->content);  free(n2);
	del_content(n3->content);  free(n3);
}

/* ================================================================ */
/*  ft_lstadd_back                                                   */
/* ================================================================ */
static void test_lstadd_back(void)
{
	SECTION("ft_lstadd_back");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	lst = make_node("first");
	n2 = make_node("second");
	ft_lstadd_back(&lst, n2);
	CHECK_STR("head unchanged after add_back",  "first",   node_str(lst));
	CHECK_STR("new tail added correctly",        "second",  node_str(lst->next));
	CHECK_PTR("tail next is NULL",               NULL,      lst->next->next);

	n3 = make_node("third");
	ft_lstadd_back(&lst, n3);
	CHECK_STR("second add_back appended",        "third",   node_str(ft_lstlast(lst)));
	CHECK_INT("size is 3 after two add_backs",   3,         ft_lstsize(lst));

	/* add_back to empty list */
	t_list	*empty = NULL;
	t_list	*solo = make_node("solo");
	ft_lstadd_back(&empty, solo);
	CHECK_STR("add_back to NULL lst",            "solo",    node_str(empty));

	del_content(lst->content); free(lst);
	del_content(n2->content);  free(n2);
	del_content(n3->content);  free(n3);
	del_content(empty->content); free(empty);
}

/* ================================================================ */
/*  ft_lstdelone                                                     */
/* ================================================================ */
static void test_lstdelone(void)
{
	SECTION("ft_lstdelone");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	lst = make_node("a");
	n2  = make_node("b");
	n3  = make_node("c");
	lst->next = n2;
	n2->next  = n3;

	/* delete middle node */
	lst->next = n3;
	ft_lstdelone(n2, del_content);
	CHECK_STR("head intact after delone",        "a",  node_str(lst));
	CHECK_STR("list jumps over deleted node",    "c",  node_str(lst->next));
	CHECK_PTR("tail next still NULL",            NULL, lst->next->next);

	/* delete head manually */
	t_list *old_head = lst;
	lst = lst->next;
	ft_lstdelone(old_head, del_content);
	CHECK_STR("new head after delone of head",   "c",  node_str(lst));

	ft_lstdelone(lst, del_content);
}

/* ================================================================ */
/*  ft_lstclear                                                      */
/* ================================================================ */
static void test_lstclear(void)
{
	SECTION("ft_lstclear");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	lst = make_node("x");
	n2  = make_node("y");
	n3  = make_node("z");
	lst->next = n2;
	n2->next  = n3;

	ft_lstclear(&lst, del_content);
	CHECK_PTR("lst is NULL after lstclear",      NULL,  lst);

	/* clear already NULL list — should not crash */
	ft_lstclear(&lst, del_content);
	CHECK_PTR("double clear no crash",           NULL,  lst);

	/* single node */
	t_list *solo = make_node("solo");
	ft_lstclear(&solo, del_content);
	CHECK_PTR("single node cleared to NULL",     NULL,  solo);
}

/* ================================================================ */
/*  ft_lstiter                                                       */
/* ================================================================ */

static int iter_count = 0;

static void count_iter(void *content)
{
	(void)content;
	iter_count++;
}

static void append_x(void *content)
{
	char	*s = (char *)content;
	size_t	len = strlen(s);
	s[len - 1] = 'X'; /* modifies last char in place */
}

static void test_lstiter(void)
{
	SECTION("ft_lstiter");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;

	/* count iterations */
	lst = make_node("a");
	n2  = make_node("b");
	n3  = make_node("c");
	lst->next = n2;
	n2->next  = n3;

	iter_count = 0;
	ft_lstiter(lst, count_iter);
	CHECK_INT("iterates over all 3 nodes",       3,  iter_count);

	/* NULL list — should not crash */
	iter_count = 0;
	ft_lstiter(NULL, count_iter);
	CHECK_INT("NULL list no iterations",         0,  iter_count);

	/* function actually modifies content */
	t_list *mod = make_node("helloA");
	ft_lstiter(mod, append_x);
	CHECK_STR("function applied to content",     "hellXX",  node_str(mod));

	ft_lstclear(&lst, del_content);
	del_content(mod->content);
	free(mod);
}

/* ================================================================ */
/*  ft_lstmap                                                        */
/* ================================================================ */

static void *dup_upper(void *content)
{
	char	*s = (char *)content;
	char	*res = strdup(s);
	size_t	i = 0;
	while (res[i])
	{
		if (res[i] >= 'a' && res[i] <= 'z')
			res[i] -= 32;
		i++;
	}
	return (res);
}

static void test_lstmap(void)
{
	SECTION("ft_lstmap");
	t_list	*lst;
	t_list	*n2;
	t_list	*n3;
	t_list	*mapped;

	lst = make_node("hello");
	n2  = make_node("world");
	n3  = make_node("test");
	lst->next = n2;
	n2->next  = n3;

	mapped = ft_lstmap(lst, dup_upper, del_content);

	CHECK_STR("first mapped node",              "HELLO",  node_str(mapped));
	CHECK_STR("second mapped node",             "WORLD",  node_str(mapped->next));
	CHECK_STR("third mapped node",              "TEST",   node_str(mapped->next->next));
	CHECK_PTR("mapped tail next is NULL",       NULL,     mapped->next->next->next);
	CHECK_INT("mapped list size is 3",          3,        ft_lstsize(mapped));

	/* original list unchanged */
	CHECK_STR("original list unchanged",        "hello",  node_str(lst));

	/* NULL list */
	t_list *null_mapped = ft_lstmap(NULL, dup_upper, del_content);
	CHECK_PTR("NULL list maps to NULL",         NULL,     null_mapped);

	ft_lstclear(&lst, del_content);
	ft_lstclear(&mapped, del_content);
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
	test_lstnew();
	test_lstadd_front();
	test_lstsize();
	test_lstlast();
	test_lstadd_back();
	test_lstdelone();
	test_lstclear();
	test_lstiter();
	test_lstmap();
	summary();
	return (failed > 0);
}
