CC := gcc

build: greetings upeNoMundo

greetings:
	@echo "Compilando..."

upeNoMundo: upeNoMundo.c
	$(CC) $^ -o $@ -pthread

clean: upeNoMundo
	@rm $^
