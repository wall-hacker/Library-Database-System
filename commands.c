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

/*
 * A function that checks the if the given hashtable is too "crowded".
 */
int check_resize(hashtable_t *ht)
{
	float entries = ht->size;
	float load_factor = entries / ht->hmax;
	if (load_factor > 1)
		return 1;
	return 0;
}

/*
 * A function that reads the name of a book, the number of definitions found
 * inside and then the pair of definitions(key-value). This book is stored in
 * a hashtable along with other important information about the book which
 * gets initialised.
 */
void ADD_BOOK(hashtable_t *ht)
{
	int def_number = 0;
	char book_name[40], def_key[20], def_value[20], temp[10];
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]\" %s", book_name, temp);
	def_number = atoi(temp);
	book_t book;
	book.book_purchases = 0;
	book.book_rating = 0;
	book.is_borrowed = 0;
	memcpy(book.book_name, book_name, strlen(book_name) + 1);
	book.ht = ht_create(HMAX, hash_function_string, compare_function_strings);
	int count = 0;
	for (int i = 0; i < def_number; i++)
	{
		scanf("%s %s", def_key, def_value);
		if (ht_has_key(book.ht, def_key))
			ht_remove_def(book.ht, def_key);
		int key_len = strlen(def_key) + 1, val_len = strlen(def_value) + 1;
		ht_put(book.ht, def_key, key_len, &def_value, val_len);
		count++;
	}
	if (ht_has_key(ht, book_name))
		ht_remove_book(ht, book_name);
	ht_put(ht, book_name, strlen(book_name) + 1, &book, sizeof(book));
}

/*
 * A function that prints information about a given book by
 * accessing the larger hashtable using the book name as a key.
 */
void GET_BOOK(hashtable_t *ht)
{
	float rating = 0;
	char book_name[40], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]", book_name);
	if (ht_has_key(ht, book_name))
	{
		book_t *temp = (book_t *)ht_get(ht, book_name);
		rating = 0;
		printf("Name:%s ", book_name);
		if (temp->book_purchases != 0)
			rating = temp->book_rating / temp->book_purchases;
		printf("Rating:%.3f Purchases:%d\n", rating, temp->book_purchases);
	}
	else
	{
		printf("The book is not in the library.\n");
	}
}

/*
 * A function that removes a book type entry the larger hashtable using
 * the book name as a key.
 */
void RMV_BOOK(hashtable_t *ht)
{
	char book_name[40], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]", book_name);
	if (ht_has_key(ht, book_name))
	{
		ht_remove_book(ht, book_name);
	}
	else
	{
		printf("The book is not in the library.\n");
	}
}

/*
 * A function that first accesses a specified book(if it exists) found
 * in the larger hashtable and then it adds a definition type entry.
 */
void ADD_DEF(hashtable_t *ht)
{
	char book_name[40], def_key[20], def_value[20], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]\" %s %s", book_name, def_key, def_value);
	if (ht_has_key(ht, book_name))
	{
		book_t *temp = (book_t *)ht_get(ht, book_name);
		if (ht_has_key(temp->ht, def_key))
		{
			ht_remove_def(temp->ht, def_key);
		}
		int key_len = strlen(def_key) + 1, val_len = strlen(def_value) + 1;
		ht_put(temp->ht, def_key, key_len, &def_value, val_len);
	}
	else
	{
		printf("The book is not in the library.\n");
	}
}

/*
 * A function that first accesses a specified book(if it exists) found
 * in the larger  hashtable and then it prints the value corresponding
 * to the definiton key.
 */
void GET_DEF(hashtable_t *ht)
{
	char book_name[40], def_key[20], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]\" %s", book_name, def_key);
	if (ht_has_key(ht, book_name))
	{
		book_t *temp = (book_t *)ht_get(ht, book_name);
		if (ht_has_key(temp->ht, def_key))
		{
			char *defo = (char *)ht_get(temp->ht, def_key);
			printf("%s\n", defo);
		}
		else
		{
			printf("The definition is not in the book.\n");
		}
	}
	else
	{
		printf("The book is not in the library.\n");
	}
}

/*
 * A function that first accesses a specified book(if it exists) found
 * in the larger hashtable and then it removes definition type entry.
 */
void RMV_DEF(hashtable_t *ht)
{
	char book_name[40], def_key[20], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line + 2, "%[^\"]\" %s", book_name, def_key);
	if (ht_has_key(ht, book_name))
	{
		book_t *temp = (book_t *)ht_get(ht, book_name);
		if (ht_has_key(temp->ht, def_key))
		{
			ht_remove_def(temp->ht, def_key);
		}
		else
		{
			printf("The definition is not in the book.\n");
		}
	}
	else
	{
		printf("The book is not in the library.\n");
	}
}

/*
 * A function that adds a user entry to the user hashtable.
 * This entry contains information about the user and the book
 * currently borrowed.
 */
void ADD_USER(hashtable_t *users)
{
	char usr_name[20], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line, "%s", usr_name);
	user_t user;
	user.days = 0;
	user.has_borrowed = 0;
	user.is_banned = 0;
	user.usr_points = 100;
	memcpy(user.usr_name, usr_name, strlen(usr_name) + 1);
	memcpy(user.book_name, "\0", 1);
	if (ht_has_key(users, usr_name))
	{
		printf("User is already registered.\n");
	}
	else
	{
		ht_put(users, usr_name, strlen(usr_name) + 1, &user, sizeof(user));
	}
}

/*
 * A function that modifies information in both the big hashtable and also
 * the user hashtable in such a way that it denotes the borrowing of a book,
 * but only after all the proper checks are passed(the user exists, the user
 * isnt banned...).
 */
void BORROW(hashtable_t *ht, hashtable_t *users)
{
	int ok = 1, days;
	char usr_name[20], book_name[40], temp[10], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line, "%s \"%[^\"]\" %s", usr_name, book_name, temp);
	days = atoi(temp);
	if (!ht_has_key(users, usr_name))
	{
		printf("You are not registered yet.\n");
		ok = 0;
	}
	if (ok)
	{
		user_t *user_data = (user_t *)ht_get(users, usr_name);
		if (user_data->is_banned)
		{
			printf("You are banned from this library.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		user_t *user_data = (user_t *)ht_get(users, usr_name);
		if (user_data->has_borrowed)
		{
			printf("You have already borrowed a book.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		if (!ht_has_key(ht, book_name))
		{
			printf("The book is not in the library.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		book_t *book_data = (book_t *)ht_get(ht, book_name);
		if (book_data->is_borrowed)
		{
			printf("The book is borrowed.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		book_t *book_data = (book_t *)ht_get(ht, book_name);
		book_data->is_borrowed = 1;
		user_t *user_data = (user_t *)ht_get(users, usr_name);
		user_data->days = days;
		user_data->has_borrowed = 1;
		memcpy(user_data->book_name, book_name, strlen(book_name) + 1);
	}
}

/*
 * A function that modifies information in both the big hashtable and also
 * the user hashtable in such a way that it denotes the return of a book,
 * but only after all the proper checks are passed(the user exists, the user
 * isnt banned...).
 */
void RETURN(hashtable_t *ht, hashtable_t *users)
{
	int ok = 1, return_days;
	float rating;
	char usr_name[20], book_name[40], temp1[10], temp2[10];
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line, "%s \"%[^\"]\" %s %s", usr_name, book_name, temp1, temp2);
	return_days = atoi(temp1);
	rating = (float)atoi(temp2);
	user_t *user_data = (user_t *)ht_get(users, usr_name);
	book_t *book_data = (book_t *)ht_get(ht, book_name);
	if (user_data->is_banned)
	{
		printf("You are banned from this library.\n");
		ok = 0;
	}
	if (ok)
	{
		if (strcmp(book_name, user_data->book_name) != 0)
		{
			printf("You didn't borrow this book.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		if (!user_data->has_borrowed)
		{
			printf("You didn't borrow this book.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		if (return_days > user_data->days)
			user_data->usr_points -= 2 * (return_days - user_data->days);
		if (return_days < user_data->days)
			user_data->usr_points += (user_data->days - return_days);
		if (user_data->usr_points < 0)
		{
			char u[20];
			memcpy(u, usr_name, strlen(usr_name) + 1);
			printf("The user %s has been banned from this library.\n", u);
			user_data->is_banned = 1;
			users->size--;
		}
		book_data->book_purchases++;
		user_data->has_borrowed = 0;
		book_data->is_borrowed = 0;
		book_data->book_rating += rating;
	}
}

/*
 * A function that modifies information in both the big hashtable and also
 * the user hashtable in such a way that it denotes that a book has been lost,
 * but only after all the proper checks are passed(the user exists, the user
 * isnt banned...).
 */
void LOST(hashtable_t *ht, hashtable_t *users)
{
	int ok = 1;
	char usr_name[20], book_name[40], line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	sscanf(line, "%s \"%[^\"]\"", usr_name, book_name);
	if (!ht_has_key(users, usr_name))
	{
		printf("You are not registered yet.\n");
		ok = 0;
	}
	if (ok)
	{
		user_t *user_data = (user_t *)ht_get(users, usr_name);
		if (user_data->is_banned)
		{
			printf("You are banned from this library.\n");
			ok = 0;
		}
	}
	if (ok)
	{
		user_t *user_data = (user_t *)ht_get(users, usr_name);
		ht_remove_book(ht, book_name);
		user_data->usr_points -= 50;
		user_data->has_borrowed = 0;
		if (user_data->usr_points < 0)
		{
			char u[20];
			memcpy(u, usr_name, strlen(usr_name) + 1);
			printf("The user %s has been banned from this library.\n", u);
			user_data->is_banned = 1;
			users->size--;
		}
	}
}

/*
 * A function that gathers all the book type entries from the big hashtable
 * and puts them into an array which is then sorted by the given criteria.
 * Last but not least the top of book is printed.
 */
void print_top_books(hashtable_t *ht)
{
	book_t v[ht->size], aux;
	int ind = 0;
	float rating = 0;
	for (unsigned int i = 0; i < ht->hmax; i++)
	{
		ll_node_t *current = ht->buckets[i]->head;
		while (current != NULL)
		{
			info *data = (info *)current->data;
			book_t *book_data = data->value;
			v[ind] = *book_data;
			ind++;
			current = current->next;
		}
	}
	if (ind != 0)
	{
		for (unsigned int i = 0; i < ht->size - 1; i++)
			for (unsigned int j = i + 1; j < ht->size; j++)
			{
				float rating1 = 0, rating2 = 0;
				if (v[i].book_purchases)
					rating1 = v[i].book_rating / v[i].book_purchases;
				if (v[j].book_purchases)
					rating2 = v[j].book_rating / v[j].book_purchases;
				if (rating1 < rating2)
				{
					aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		for (unsigned int i = 0; i < ht->size - 1; i++)
			for (unsigned int j = i + 1; j < ht->size; j++)
			{
				float rating1 = 0, rating2 = 0;
				if (v[i].book_purchases)
					rating1 = v[i].book_rating / v[i].book_purchases;
				if (v[j].book_purchases)
					rating2 = v[j].book_rating / v[j].book_purchases;
				if (rating1 == rating2)
					if (v[i].book_purchases < v[j].book_purchases)
					{
						aux = v[i];
						v[i] = v[j];
						v[j] = aux;
					}
			}
		for (unsigned int i = 0; i < ht->size - 1; i++)
			for (unsigned int j = i + 1; j < ht->size; j++)
			{
				float rating1 = 0, rating2 = 0;
				if (v[i].book_purchases)
					rating1 = v[i].book_rating / v[i].book_purchases;
				if (v[j].book_purchases)
					rating2 = v[j].book_rating / v[j].book_purchases;
				if (rating1 == rating2)
					if (v[i].book_purchases == v[j].book_purchases)
						if (strcmp(v[i].book_name, v[j].book_name) > 0)
						{
							aux = v[i];
							v[i] = v[j];
							v[j] = aux;
						}
			}
	}
	printf("Books ranking:\n");
	for (unsigned int i = 0; i < ht->size; i++)
	{
		rating = 0;
		printf("%d. Name:%s ", i + 1, v[i].book_name);
		if (v[i].book_purchases != 0)
			rating = v[i].book_rating / v[i].book_purchases;
		printf("Rating:%.3f Purchases:%d\n", rating, v[i].book_purchases);
	}
}

/*
 * A function that gathers all the user type entries from the user hashtable
 * and puts them into an array which is then sorted by the given criteria.
 * Last but not least the top of users is printed.
 */
void print_top_users(hashtable_t *users)
{
	user_t v[users->size], aux;
	int ind = 0;
	for (unsigned int i = 0; i < users->hmax; i++)
	{
		ll_node_t *current = users->buckets[i]->head;
		while (current != NULL)
		{
			info *data = (info *)current->data;
			user_t *user_data = data->value;
			if (user_data->is_banned == 0)
			{
				v[ind] = *user_data;
				ind++;
			}
			current = current->next;
		}
	}
	if (ind != 0)
	{
		for (unsigned int i = 0; i < users->size - 1; i++)
			for (unsigned int j = i + 1; j < users->size; j++)
			{
				if (v[i].usr_points < v[j].usr_points)
				{
					aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		for (unsigned int i = 0; i < users->size - 1; i++)
			for (unsigned int j = i + 1; j < users->size; j++)
			{
				if (v[i].usr_points == v[j].usr_points)
					if (strcmp(v[i].usr_name, v[j].usr_name) > 0)
					{
						aux = v[i];
						v[i] = v[j];
						v[j] = aux;
					}
			}
	}
	printf("Users ranking:\n");
	for (unsigned int i = 0; i < users->size; i++)
	{
		char usr_name[20];
		memcpy(usr_name, v[i].usr_name, strlen(v[i].usr_name) + 1);
		printf("%d. Name:%s Points:%d\n", i + 1, usr_name, v[i].usr_points);
	}
}

/*
 * A function that first calls the two print_top functions from above,
 * and then frees absolutely all allocated memory.
 */
void EXIT(hashtable_t *ht, hashtable_t *users)
{
	print_top_books(ht);
	print_top_users(users);

	for (unsigned int i = 0; i < ht->hmax; i++)
	{
		ll_node_t *current = ht->buckets[i]->head;
		while (current != NULL)
		{
			info *data = (info *)current->data;
			book_t *book_data = data->value;
			ht_free(book_data->ht);
			current = current->next;
		}
	}
	ht_free(ht);
	ht_free(users);
}
