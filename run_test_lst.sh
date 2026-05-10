#!/bin/bash
make && gcc Basic-libft-tester/test_libft_lst.c -I. -L. -lft -o Basic-libft-tester/test_libft_lst && ./Basic-libft-tester/test_libft_lst
make fclean
