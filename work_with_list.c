#include "bible.h"
#include "struct.h"

Node *select_by_id(Head *head, int n) { // поиск нужного узла по номеру
    Node *node;
    int k;

    node = head->first;
    k = head->cnt;
    if (n > k) n = k;
    if (n == 0) n = 1;
    if ((n > 0) && (n <= k)) {// проходим по списку пока не дойдем до нужного номера
        while ((node->id) != n)
            node = node->next;
    } else node = NULL;
    return node;// возвращаем указатель на этот узел
}

void delete_selected(Head *head, Node *current_node) {// удаление определенного узла
    Node *temp;
    int flag;
    current_node->prev->next = current_node->next;// соединяем узлы до и после удаленного
    current_node->next->prev = current_node->prev;
    if (current_node == head->first)// если это первый или последний элемент обновляем голову списка
    {
        flag = 1;
        head->first = current_node->next;
    }
    if (current_node == head->last) {
        head->last = current_node->prev;
    }
    if (current_node->prev != head->last && current_node->next != head->first)
        flag = 2;
    if (flag == 1)// если это первый узел
    {
        temp = head->first;
        while (temp != head->last)// обновляем номера узлов
        {
            temp->id--;
            temp = temp->next;
        }
        temp->id--;
    }
    if (flag == 2)// если это не первый и не последний
    {
        temp = current_node->prev;
        while (temp->next != head->last)// обновляем номера узлов
        {
            temp = temp->next;
            temp->id--;
        }
        temp = temp->next;
        temp->id--;
    }

    free(current_node->name);// очищаем память под узел
    free(current_node->type);
    free(current_node);
    head->cnt--;
}

void insert_after(Head *head, Node *new_node, Node *current_node) {// вставка узла после текущего
    Node *node_temp;
    if (head && new_node && current_node) {
        new_node->next = current_node->next;
        new_node->prev = current_node;
        current_node->next = new_node;
        new_node->next->prev = new_node;
        if (current_node == head->last) {
            head->last = new_node;
        }
        new_node->id = current_node->id + 1;
        node_temp = new_node;
        while (node_temp->next != head->first) {// проходим по списку увеличивая номера узлов
            node_temp = node_temp->next;
            node_temp->id++;

        }
        head->cnt++;
    }

}


void insert_before(Head *head, Node *new_node, Node *current_node) {// вставка узла перед определенным элементом
    Node *node_temp;
    if (head && new_node && current_node) {// обновляем указатели на следующий и предыдущий узлов рядом
        new_node->prev = current_node->prev;
        new_node->next = current_node;
        current_node->prev = new_node;
        new_node->prev->next = new_node;
        if (current_node == head->first)// если это новый первый элемент обновляем голову списка
            head->first = new_node;
        new_node->id = current_node->id;
        node_temp = new_node;
        while (node_temp->next != head->first) {// проходим по списку увеличивая номера узлов
            node_temp = node_temp->next;
            node_temp->id++;

        }
        head->cnt++;
    }

}

void copy_node(Head *head, Node *new_node, int k) {// копирование данных из одного узла в другой
    Node *temp = NULL;
    if (k > head->cnt) {// если это вставка на последнее место
        temp = select_by_id(head, k);// ищем узел который стоит на нужном месте
        insert_after(head, new_node, temp);// вставляем после него
    } else {// иначе вставляем перед искомым
        temp = select_by_id(head, k);
        insert_before(head, new_node, temp);
    }
    head->cnt++;

}

void change_head(Head *head, Node *node) {// меняем начало списка
    Node *temp;
    Node *temp_begin = head->first;// сохраняем прошлые начало и конец
    Node *temp_last = head->last;
    int begin = node->id -1;// переменная которуюю надо будет вычесть из всех после ногого начала пока не дойдем до старого конца
    int end = head->cnt - begin;// переменная которую нужно добавить всем после старого конца до нового начала
    head->first = node;
    head->last = node->prev;
    temp = head->first;
    while (temp != temp_begin) {// обновление номеров узлов
        temp->id = temp->id - begin;
        temp = temp->next;
    }
    while (temp_last != head->last) {// обновление номеров узлов
        temp_last = temp_last->next;
        temp_last->id = temp_last->id + end;

    }
}

