#!/bin/bash
make && gcc Basic-libft-tester/test_libft_part2.c Basic-libft-tester/stubs.c -I. -L. -lft -o Basic-libft-tester/test_libft_part2 && ./Basic-libft-tester/test_libft_part2
make fclean
