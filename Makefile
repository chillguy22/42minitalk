CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Original source files
SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER = server
CLIENT = client

# Bonus source files
SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_SRC = client_bonus.c
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

all: $(SERVER) $(CLIENT) clean

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_BONUS_OBJ): $(SERVER_BONUS_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_BONUS_OBJ): $(CLIENT_BONUS_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all clean

.PHONY: all clean fclean re bonus
