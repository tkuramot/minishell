#!/bin/bash

readonly COLOR_RESET="\033[0m"
readonly COLOR_GREEN="\033[32m"
readonly COLOR_RED="\033[31m"

# assert {command1} {command2}
assert() {
	# テストしようとしている内容をprint
	printf '%-30s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$2" | bash >out 2>&-
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
		printf "${COLOR_GREEN}  status NG, expected $expected but got $actual ${COLOR_RESET}"
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# assert_builtin {command} {args in a string}
assert_builtin() {
	assert "$1 $2" "./$1 $2"
}

# assert_echo {args in a string}
assert_echo() {
	assert_builtin "echo" "$1"
}

assert_pwd() {
	assert_builtin "pwd" "$1"
}
