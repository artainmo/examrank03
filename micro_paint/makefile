all: run
re: fclean all

RM = rm -rf

run:
	python3 main.py

clean:
	$(RM) __pycache__ utils/__pycache__

fclean:
	$(RM) test/test/a.out
	$(RM) __pycache__ utils/__pycache__
