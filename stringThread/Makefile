CC := gcc

build: greetings string

greetings:
	@echo "Compilando..."

string: stringMutex.c
	$(CC) $^ -o $@ -pthread

clean: string
	@rm $^
