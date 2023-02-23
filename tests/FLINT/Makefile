CC=gcc
NAME=flint
CFLAGS= -g -O2 -lflint -lgmp -lm -lpthread
INCLUDE=include
SRC_DIR=bench
OBJ_DIR=obj
SOURCES=time_utils.c

SRC=$(addprefix $(SRC_DIR)/,$(SOURCES))
$(info $$SRC is [${SRC}])
OBJS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
$(info $$OBJS is [${OBJS}])

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE)/time_utils.h
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDE)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re