# libft tester

A simple tester for the 42 libft project. Tests all mandatory Part 1 functions with edge cases and compares results against the standard C library.

## Files

| File | Description |
|------|-------------|
| `test_libft.c` | Main test file |
| `stubs.c` | Placeholder functions for unimplemented functions |
| `run_test.sh` | Shell script to build and run the tester |

## Setup

Copy all three files into your libft folder — the one that contains your `Makefile` and `libft.h`.

```
your_libft/
├── Makefile
├── libft.h
├── ft_*.c
├── test_libft.c
├── stubs.c
└── run_test.sh
```

## Usage

Run the tester with:

```bash
bash run_test.sh
```

This will:
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

Comment the stub back out once you implement the real function.

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

- `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- `ft_toupper`, `ft_tolower`
- `ft_strlen`
- `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`
- `ft_strchr`, `ft_strrchr`, `ft_strcpy`, `ft_strdup`
- `ft_strncmp`, `ft_strlcpy`, `ft_strlcat`, `ft_strnstr`
- `ft_atoi`
- `ft_calloc`

## Notes

- `ft_strnstr` is tested directly without a system reference since `strnstr` is BSD-only and not available on Linux
- The tester does not cover Part 2 or bonus linked list functions
