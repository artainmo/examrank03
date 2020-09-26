all: run
re: fclean all

RM = rm -rf

run:
	@gcc -Wall -Wextra -Werror my/mini_paint.c -o my_mini_paint
	@gcc -Wall -Wextra -Werror mini_paint_tester/our_mini_paint.c -o our_mini_paint
	@python3 main.py

single:
	@gcc -Wall -Wextra -Werror my/mini_paint.c -o my_mini_paint
	@gcc -Wall -Wextra -Werror mini_paint_tester/our_mini_paint.c -o our_mini_paint
	@python3 single_test.py 1

set:
	pip3 install termcolor

clean:
	$(RM) __pycache__ utils/__pycache__

fclean:
	$(RM) my_mini_paint our_mini_paint
	$(RM) answers/correct_log.txt answers/errors_log.txt
	$(RM) __pycache__ mini_paint_tester/__pycache__ mini_paint_tester/examples/__pycache__
