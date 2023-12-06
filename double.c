#include <stdio.h>
#include <stdlib.h>

// определение структуры узла списка
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// определение структуры двусвязанного списка
struct LinkedList {
    struct Node* head;
    struct Node* tail;
};

// функция для создания нового узла
struct Node* createNode(int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// функция для добавления элемента в конец списка
void append(struct LinkedList* list, int value) {
    struct Node* new_node = createNode(value);

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

// функция для отображения содержимого списка
void display(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// функция для вставки нового узла после указанного узла
struct Node* insertAfter(struct LinkedList* list, struct Node* node, int value) {
    struct Node* new_node = createNode(value);

    if (node == NULL) {
        // вставка в начало списка
        if (list->head == NULL) {
            list->head = new_node;
            list->tail = new_node;
        }
        else {
            new_node->next = list->head;
            list->head->prev = new_node;
            list->head = new_node;
        }
    }
    else {
        new_node->next = node->next;
        new_node->prev = node;
        if (node->next != NULL) {
            node->next->prev = new_node;
        }
        else {
            // Вставка в конец списка
            list->tail = new_node;
        }
        node->next = new_node;
    }

    return new_node;
}

// функция для вставки нового узла перед указанным узлом
struct Node* insertBefore(struct LinkedList* list, struct Node* node, int value) {
    struct Node* new_node = createNode(value);

    if (node == NULL) {
        // вставка в конец списка
        if (list->tail == NULL) {
            list->head = new_node;
            list->tail = new_node;
        }
        else {
            new_node->prev = list->tail;
            list->tail->next = new_node;
            list->tail = new_node;
        }
    }
    else {
        new_node->prev = node->prev;
        new_node->next = node;
        if (node->prev != NULL) {
            node->prev->next = new_node;
        }
        else {
            // Вставка в начало списка
            list->head = new_node;
        }
        node->prev = new_node;
    }

    return new_node;
}

// функция для поиска узла с заданным значением
struct Node* find(struct LinkedList* list, int value) {
    struct Node* current = list->head;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Узел не найден
}

// функция для удаления узла из списка
void removeNode(struct LinkedList* list, struct Node* node) {
    if (node == NULL) {
        return; // Нельзя удалить NULL-узел
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    else {
        // Узел находится в начале списка
        list->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    else {
        // Узел находится в конце списка
        list->tail = node->prev;
    }

    free(node);
}

int main() {
    // создание двусвязанного списка и заполнение значениями
    struct LinkedList linked_list;
    linked_list.head = NULL;
    linked_list.tail = NULL;

    // Добавление 15 элементов в список
    for (int i = 1; i <= 15; ++i) {
        append(&linked_list, i * 10);
    }

    // вывод содержимого двусвязанного списка
    printf("Исходный список:\n");
    display(&linked_list);

    // вставка нового узла после указанного узла
    struct Node* node_to_insert_after = linked_list.head->next->next;  
    insertAfter(&linked_list, node_to_insert_after, 555);

    // вставка нового узла перед указанным узлом
    struct Node* node_to_insert_before = linked_list.head->next;  
    insertBefore(&linked_list, node_to_insert_before, 777);

    // вывод обновленного списка
    printf("\nСписок после вставок:\n");
    display(&linked_list);

    // поиск и удаление узла со значением 555
    struct Node* node_to_find = find(&linked_list, 555);
    if (node_to_find != NULL) {
        printf("\nУзел со значением 555 найден и удален.\n");
        removeNode(&linked_list, node_to_find);
    }
    else {
        printf("\nУзел со значением 555 не найден.\n");
    }

    // вывод списка после удаления
    printf("\nСписок после удаления узла со значением 555:\n");
    display(&linked_list);

    return 0;
}
