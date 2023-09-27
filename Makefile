CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L $(shell brew --prefix readline)/lib
LIBS    = libft/libft.a
INCLUDE = -I./include -I./libft/include -I$(shell brew --prefix readline)/include
NAME    = minishell
SRCDIR  = src
SRCS    = src/lexer/lexer_helper.c src/lexer/lexer.c src/lexer/token.c src/utils/error.c src/utils/signal.c src/heredoc/heredoc.c src/parser/ast.c src/parser/parser.c src/expander/expander.c src/main.c src/exec/file_access_util.c src/exec/list_to_array.c src/exec/resolve_path.c src/exec/execute.c src/exec/execute_cmd.c src/exec/run_simple_cmd.c src/builtin/env_lst_operations.c src/builtin/decompress.c src/builtin/mini_echo.c src/builtin/mini_cd.c src/builtin/mini_export.c src/builtin/mini_unset.c src/builtin/mini_env.c src/builtin/mini_pwd.c src/builtin/mini_exit.c
OBJDIR  = obj
OBJS    = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))
DEPENDS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS) $(LIBS)

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

test: all
	bash ./test/test.sh

cfile:
	find . -name "*.c" -not -path "./libft/*" | sed 's/\.\///g' | tr '\n' ' '

-include $(DEPENDS)

.PHONY: all clean fclean re test
