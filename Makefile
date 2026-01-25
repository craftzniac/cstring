CFLAGS = -Wall -Wextra -pedantic -pedantic-errors -Werror -Wvla

main: main.c CString.c
	$(CC) $(CFLAGS) CString.c main.c -o main

clean: 
	$(RM) main

