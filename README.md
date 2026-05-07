# Basic-libft-tester

A comprehensive tester for the 42 libft project covering all three parts — Libc functions, additional functions, and linked list functions.

## Files

| File | Description |
|------|-------------|
| `test_libft.c` | Part 1 tester — Libc functions |
| `test_libft_part2.c` | Part 2 tester — additional functions |
| `test_libft_lst.c` | Part 3 tester — linked list functions |
| `stubs.c` | Placeholder functions for unimplemented functions |
| `run_test.sh` | Shell script for Part 1 |
| `run_test_part2.sh` | Shell script for Part 2 |
| `run_test_lst.sh` | Shell script for Part 3 |

## Setup

Clone this repo **inside** your libft folder:

```bash
cd your_libft/
git clone https://github.com/yourname/Basic-libft-tester.git
```

Your folder structure should look like this:

```
your_libft/
├── Makefile
├── libft.h
├── ft_*.c
└── Basic-libft-tester/
    ├── test_libft.c
    ├── test_libft_part2.c
    ├── test_libft_lst.c
    ├── stubs.c
    ├── run_test.sh
    ├── run_test_part2.sh
    ├── run_test_lst.sh
    └── README.md
```

## Usage

Run each tester from inside your libft folder — **not** from inside the tester folder:

```bash
# Part 1 — Libc functions
bash Basic-libft-tester/run_test.sh

# Part 2 — Additional functions
bash Basic-libft-tester/run_test_part2.sh

# Part 3 — Linked list functions
bash Basic-libft-tester/run_test_lst.sh
```

Each script will:
1. Build your `libft.a` with `make`
2. Compile and run the tester
3. Clean up with `make fclean`

## Working with unimplemented functions

If you haven't implemented all functions yet, open `stubs.c` and uncomment the stub for each missing function:

```c
// before — function is implemented, stub not needed
//int    ft_isalnum(int c) { (void)c; return (-1); }

// after — function is not yet implemented, stub active
int    ft_isalnum(int c) { (void)c; return (-1); }
```

Comment the stub back out once you implement the real function. Stubs are organized by part inside `stubs.c` for easy navigation.

## Output

```
== ft_isalpha ==
  [OK] lowercase 'a'
  [OK] uppercase 'Z'
  [KO] digit '5'  (expected: 0 | got: 1)
  ...

== SUMMARY ==
  Total:  42
  Passed: 41
  Failed: 1
```

Green `[OK]` means your function matches the expected result.
Red `[KO]` shows the expected vs actual value so you know exactly what went wrong.

## Functions tested

**Part 1 — Libc functions**
- `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- `ft_toupper`, `ft_tolower`
- `ft_strlen`
- `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`
- `ft_strchr`, `ft_strrchr`, `ft_strcpy`, `ft_strdup`
- `ft_strncmp`, `ft_strlcpy`, `ft_strlcat`, `ft_strnstr`
- `ft_atoi`, `ft_calloc`

**Part 2 — Additional functions**
- `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`
- `ft_itoa`, `ft_strmapi`, `ft_striteri`
- `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

**Part 3 — Linked list functions**
- `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`
- `ft_lstadd_back`, `ft_lstdelone`, `ft_lstclear`
- `ft_lstiter`, `ft_lstmap`

## Notes

- `ft_strnstr` is tested directly without a system reference since `strnstr` is BSD-only and not available on Linux
- The `put*_fd` functions write visually to stdout/stderr — verify their output by eye as automated checking of fd output is not possible
- All three testers share the same `stubs.c` file
