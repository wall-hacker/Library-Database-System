// Copyright 2022 Calin-Mihail Andrei
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/commands.h"
#include "/home/student/struct.h"
#include "/home/student/ll.h"
#include "/home/student/ht.h"

#define MAX_STRING_SIZE 256
#define HMAX 10

int main()
{
	hashtable_t *ht, *users;
	ht = ht_create(HMAX, hash_function_string, compare_function_strings);
	users = ht_create(HMAX, hash_function_string, compare_function_strings);

	while (1)
	{
		char command[MAX_STRING_SIZE];

		scanf("%s", command);
		if (strncmp(command, "ADD_BOOK", 8) == 0)
			ADD_BOOK(ht);

		if (strncmp(command, "GET_BOOK", 8) == 0)
			GET_BOOK(ht);

		if (strncmp(command, "RMV_BOOK", 8) == 0)
			RMV_BOOK(ht);

		if (strncmp(command, "ADD_DEF", 7) == 0)
			ADD_DEF(ht);

		if (strncmp(command, "GET_DEF", 7) == 0)
			GET_DEF(ht);

		if (strncmp(command, "RMV_DEF", 7) == 0)
			RMV_DEF(ht);

		if (strncmp(command, "ADD_USER", 8) == 0)
			ADD_USER(users);

		if (strncmp(command, "BORROW", 6) == 0)
			BORROW(ht, users);

		if (strncmp(command, "RETURN", 6) == 0)
			RETURN(ht, users);

		if (strncmp(command, "LOST", 4) == 0)
			LOST(ht, users);

		if (strncmp(command, "EXIT", 4) == 0)
		{
			EXIT(ht, users);
			break;
		}
	}

	return 0;
}
