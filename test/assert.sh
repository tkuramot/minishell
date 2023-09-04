#!/bin/bash

readonly COLOR_RESET="\033[0m"
readonly COLOR_GREEN="\033[32m"
readonly COLOR_RED="\033[31m"

# assert {command}
assert() {
	# テストしようとしている内容をprint
	# printf '%-20s:' "\"$@\""
	printf '%-30s:' "'$*'"

	# bashの出力をcmpに保存
	echo -n -e "$*" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$*" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >/dev/null \
		&& printf "${COLOR_GREEN}  diff OK ${COLOR_RESET}" \
		|| printf "${COLOR_RED}  diff NG ${COLOR_RESET}"

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		printf "${COLOR_GREEN}  status OK ${COLOR_RESET}"
	else
		printf "${COLOR_RED}  status NG, expected $expected but got $actual ${COLOR_RESET}"
	fi
	echo
}
