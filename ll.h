// Copyright 2022 Andrei Calin-Mihail 311CA
#ifndef _HOME_STUDENT_LL_H_
#define _HOME_STUDENT_LL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/student/struct.h"

linked_list_t *ll_create(unsigned int data_size);
void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data);
ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n);
unsigned int ll_get_size(linked_list_t *list);
void ll_free(linked_list_t **pp_list);

#endif  //  _HOME_STUDENT_LL_H_
