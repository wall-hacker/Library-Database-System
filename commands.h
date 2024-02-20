// Copyright 2022 Andrei Calin-Mihail 311CA
#ifndef _HOME_STUDENT_COMMANDS_H_
#define _HOME_STUDENT_COMMANDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/struct.h"
#include "/home/student/ll.h"
#include "/home/student/ht.h"

int check_resize(hashtable_t *ht);
void ADD_BOOK(hashtable_t *ht);
void GET_BOOK(hashtable_t *ht);
void RMV_BOOK(hashtable_t *ht);
void ADD_DEF(hashtable_t *ht);
void GET_DEF(hashtable_t *ht);
void RMV_DEF(hashtable_t *ht);
void ADD_USER(hashtable_t *users);
void BORROW(hashtable_t *ht, hashtable_t *users);
void RETURN(hashtable_t *ht, hashtable_t *users);
void LOST(hashtable_t *ht, hashtable_t *users);
void print_top_books(hashtable_t *ht);
void print_top_users(hashtable_t *users);
void EXIT(hashtable_t *ht, hashtable_t *users);

#endif  //  _HOME_STUDENT_COMMANDS_H_
