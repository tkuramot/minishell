#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *line = readline("$ ");
	printf("%s\n", line);
	add_history(line);
	rl_replace_line("", 0);
}
