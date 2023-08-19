CFLAGS  = -g -MMD -MP -Wall -Wextra -Werror
LDFLAGS =
LIBS    =
INCLUDE = -I./include
NAME    = minishell
SRCDIR  = ./src
SRCS    = main.c
OBJDIR  = ./obj
OBJS    = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPENDS = $(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: fclean $(NAME)

clean:
	-$(RM) -r $(OBJDIR)

fclean: clean
	-$(RM) $(NAME)

-include $(DEPENDS)
