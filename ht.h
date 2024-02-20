// Copyright 2022 Andrei Calin-Mihail 311CA
#ifndef _HOME_STUDENT_HT_H_
#define _HOME_STUDENT_HT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/struct.h"
#include "/home/student/ll.h"

int compare_function_strings(void *a, void *b);
unsigned int hash_function_int(void *a);
unsigned int hash_function_string(void *a);
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
		  int (*compare_function)(void *, void *));
int ht_has_key(hashtable_t *ht, void *key);
void * ht_get(hashtable_t *ht, void *key);
void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
			void *value, unsigned int value_size);
void ht_free(hashtable_t *ht);
unsigned int ht_get_size(hashtable_t *ht);
unsigned int ht_get_hmax(hashtable_t *ht);
void ht_remove_book(hashtable_t *ht, void *key);
void ht_remove_def(hashtable_t *ht, void *key);

#endif  //  _HOME_STUDENT_HT_H_
