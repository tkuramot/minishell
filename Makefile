CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS =
LIBS    = libft/libft.a
INCLUDE = -I./include -I./libft/include
NAME    = minishell
SRCDIR  = src
SRCS    = src/main.c
OBJDIR  = obj
OBJS    = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))
DEPENDS = $(OBJS:.o=.d)

builtins = echo

ECHOSRCS = src/builtin/mini_echo.c
ECHOOBJS = $(subst $(SRCDIR), $(OBJDIR), $(ECHOSRCS:.c=.o))

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
	$(RM) $(NAME) $(builtins)

re: fclean all

echo: $(ECHOOBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

-include $(DEPENDS)
