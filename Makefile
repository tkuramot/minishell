CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS =
LIBS    = libft/libft.a
INCLUDE = -I./include -I./libft/include
NAME    = minishell
SRCDIR  = src
SRCS    = main.c
OBJDIR  = obj
OBJS    = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPENDS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(LIBS):
	$(MAKE) -C libft

clean:
	make -C libft clean
	$(RM) -r $(OBJDIR)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all

-include $(DEPENDS)
