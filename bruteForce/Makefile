CC := gcc

build: greetings bruteforce

greetings:
	@echo "Compilando..."

bruteforce: bruteForce.c
	$(CC) $^ -o $@ -pthread

clean: bruteforce
	@rm $^
