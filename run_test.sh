#!/bin/bash
make && gcc Basic-libft-tester/test_libft.c Basic-libft-tester/stubs.c -L. -lft -o Basic-libft-tester/test_libft && ./Basic-libft-tester/test_libft
make fclean
