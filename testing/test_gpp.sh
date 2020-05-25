#!/bin/sh
test()
{
	
	if g++ $1 -I .. -Wall -Wextra -o $1.exe
	then
		GREEN='\033[0;32m'
		WHITE='\033[0m'
		printf "I ${GREEN}Success${WHITE}\n"
		return 0
	else
		RED='\033[0;31m'
		WHITE='\033[0m'
		printf "I ${RED}Fail${WHITE}\n"
		return 1
	fi
}

test ir_math_test.cpp			&& \
test ir_n2st_database_test.cpp	&& \
test ir_neuro_test.cpp			&& \
test ir_openmap_test.cpp		&& \
test ir_resource_test.cpp		&& \
test ir_s2st_database_test.cpp	&& \
test ir_utf_test.c				&& \
test ir_vector_test.cpp

rm *.exe -f
rm *.obj -f