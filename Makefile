.PHONY: run

charcount: my_mastermind
	gcc -Wall -Wextra -Werror -o my_mastermind my_mastermind.c
	


run: my_mastermind
	./my_mastermind 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET) my_mastermind
