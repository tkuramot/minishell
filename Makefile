CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L $(shell brew --prefix readline)/lib
LIBS    = libft/libft.a
INCLUDE = -I./include -I./libft/include -I$(shell brew --prefix readline)/include
NAME    = minishell
SRCDIR  = src
SRCS    = src/builtin/decompress.c src/builtin/env_lst_operations.c src/builtin/mini_cd.c src/builtin/mini_echo.c src/builtin/mini_env.c src/builtin/mini_exit.c src/builtin/mini_export.c src/builtin/mini_pwd.c src/builtin/mini_unset.c src/exec/execute.c src/exec/file_access_util.c src/exec/list_to_array.c src/exec/redirect/redirect.c src/exec/resolve_path.c src/exec/run_non_builtin.c src/exec/run_simple_cmd.c src/expander/expander.c src/expander/expander_handling.c src/expander/expander_utils.c src/expander/quote_handling.c src/lexer/lexer.c src/lexer/lexer_helper.c src/lexer/token.c src/main.c src/parser/ast.c src/parser/expect.c src/parser/heredoc.c src/parser/heredoc_helper.c src/parser/parser.c src/parser/redirect_parser.c src/utils/error.c src/utils/file.c src/utils/signal.c
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
