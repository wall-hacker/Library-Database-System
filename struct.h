// Copyright 2022 Andrei Calin-Mihail 311CA
#ifndef _HOME_STUDENT_STRUCT_H_
#define _HOME_STUDENT_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll_node_t
{
	void *data;
	struct ll_node_t *next;
} ll_node_t;

typedef struct linked_list_t
{
	ll_node_t *head;
	unsigned int data_size;
	unsigned int size;
} linked_list_t;
typedef struct info info;
struct info
{
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t
{
	linked_list_t **buckets; /* Linked list array */
	unsigned int size;		 /* Total number of nodes from all buckets */
	unsigned int hmax;		 /* Number of buckets */
	unsigned int (*hash_function)(void *);
	int (*compare_function)(void *, void *);
};

typedef struct book_t
{
	hashtable_t *ht;
	int book_purchases;
	int is_borrowed;
	float book_rating;
	char book_name[40];
} book_t;

typedef struct user_t
{
	int usr_points;
	int is_banned;
	int has_borrowed;
	int days;
	char usr_name[20];
	char book_name[40];
} user_t;

#endif  //  _HOME_STUDENT_STRUCT_H_
