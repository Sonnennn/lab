
#ifndef WORK_WITH_LIST_H
#define WORK_WITH_LIST_H

#include "bible.h"
#include "struct.h"

Node *select_by_id(Head *head, int n);

void delete_selected(Head *head, Node *current_node);

void insert_after(Head *head, Node *new_node, Node *current_node);

void insert_before(Head *head, Node *new_node, Node *current_node);

void copy_node(Head *head, Node *new_node, int k);

void change_head(Head *head, Node *node);

#endif
