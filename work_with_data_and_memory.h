
#ifndef WORK_WITH_DATA_AND_MEMORY_H
#define WORK_WITH_DATA_AND_MEMORY_H

#include "struct.h"

Head *make_head();

char **scan_node();

void Free_Node(Head *head);

Node *create_node(char **str, int id);

char **simple_split(char *str, int length, char sep);

char **scan_date(Node *node);

#endif
