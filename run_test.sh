#!/bin/bash
make && gcc test_libft.c stubs.c -L. -lft -o test_libft && ./test_libft
make fclean
