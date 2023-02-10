CC			= g++

NAME		= ntl.a

CFLAGS		= -g -O2 -std=c++11 -pthread -lntl -lgmp -lm

INCLUDE		= include

SRC_DIR		= bench

OBJ_DIR		= obj

RM			= rm -f

SOURCES =	time.cpp	\


SRC	=	$(addprefix $(SRC_DIR)/,$(SOURCES))
$(info $$SRC is [${SRC}])
OBJS =	$(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))
$(info $$SRC is [${OBJS}])

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE)/time.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re