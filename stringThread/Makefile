CC := gcc

build: greetings string

greetings:
	@echo "Compilando..."

string: stringThread.c
	$(CC) $^ -o $@ -pthread

clean: string
	@rm $^