CC := gcc

build: greetings philosophers

greetings:
	@echo "Compilando..."

philosophers: philosophers.c
	$(CC) $^ -o $@.out -pthread

clean: philosophers
	@rm $^
