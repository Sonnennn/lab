
#ifndef MENU_H
#define MENU_H

#include "bible.h"
#include "struct.h"
#include "work_with_list.h"

void Menu(Head *head);

void Menu_copy(Head *head);

void Menu_before(Head *head);

void Menu_after(Head *head);

void Menu_delete(Head *head);

void Menu_change_head(Head *head);

#endif