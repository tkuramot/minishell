CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS =  -lreadline -lhistory -L $(shell brew --prefix readline)/lib
LIBS    = libft/libft.a
INCLUDE = -I./include -I./libft/include -I $(brew --prefix readline)/include
NAME    = minishell
SRCDIR  = src
SRCS    = src/builtin/mini_echo.c src/builtin/mini_pwd.c src/builtin/mini_exit.c src/builtin/mini_cd.c src/builtin/mini_env.c src/builtin/mini_export.c src/builtin/mini_unset.c src/builtin/mini_handle_command.c src/builtin/env_lst_operations.c src/builtin/decompress.c \
			src/lexer/lexer.c src/lexer/lexer_helper.c src/main.c src/utils/error.c \
			src/exec/test_exec.c src/exec/env_list_to_array.c
OBJDIR  = obj
OBJS    = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))
DEPENDS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(LIBS):
	$(MAKE) -C ./libft

clean:
	make -C ./libft clean
	$(RM) -r $(OBJDIR)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re: fclean all

test:
	bash ./test/test.sh

fname:
	find . -name "*.c" -not -path "./libft/*" | sed 's/\.\///g' | tr '\n' ' '

-include $(DEPENDS)

.PHONY: all clean fclean re test
