#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла списка
struct Node {
    int data;
    struct Node* next;
};

// Определение структуры связанного списка
struct LinkedList {
    struct Node* head;
};

// Определение структуры для результата поиска узла
struct FindNodeResult {
    struct Node* found_node;
    struct Node* previous_node;
};

// Функция для создания нового узла
struct Node* createNode(int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Функция для добавления элемента в конец списка
void append(struct LinkedList* list, int value) {
    struct Node* new_node = createNode(value);

    if (list->head == NULL) {
        list->head = new_node;
    }
    else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Функция для отображения содержимого списка
void display(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Функция для вставки нового узла после указанного узла
struct Node* insertAfter(struct LinkedList* list, struct Node* node, int value) {
    struct Node* new_node = createNode(value);

    if (node == NULL) {
        new_node->next = list->head;
        list->head = new_node;
    }
    else {
        new_node->next = node->next;
        node->next = new_node;
    }

    return new_node;
}

// Функция для поиска узла с заданным значением
struct FindNodeResult find(struct LinkedList* list, int value) {
    struct FindNodeResult result;
    result.found_node = NULL;
    result.previous_node = NULL;

    struct Node* current = list->head;

    while (current != NULL) {
        if (current->data == value) {
            result.found_node = current;
            break;
        }
        result.previous_node = current;
        current = current->next;
    }

    return result;
}

// Функция для удаления узла после указанного узла
void removeAfter(struct LinkedList* list, struct Node* node) {
    if (node == NULL) {
        // Удаляем первый узел
        if (list->head != NULL) {
            struct Node* temp = list->head;
            list->head = list->head->next;
            free(temp);
        }
    }
    else if (node->next != NULL) {
        // Удаляем узел после указанного узла
        struct Node* temp = node->next;
        node->next = node->next->next;
        free(temp);
    }
}

int main() {
    // Создание связанного списка и заполнение значениями
    struct LinkedList linked_list;
    linked_list.head = NULL;

    for (int i = 1; i <= 10; ++i) {
        append(&linked_list, i * 10);
    }

    // Вывод содержимого связанного списка
    printf("Исходный список:\n");
    display(&linked_list);

    // Вставка нового узла после указанного узла
    struct Node* node_to_insert_after = linked_list.head->next->next;  // Пример: вставка после третьего узла
    struct Node* inserted_node = insertAfter(&linked_list, node_to_insert_after, 555);

    // Вывод списка после вставки
    printf("\nСписок после вставки:\n");
    display(&linked_list);

    // Удаление узла со значением 555
    struct FindNodeResult search_result = find(&linked_list, 555);
    removeAfter(&linked_list, search_result.previous_node);

    // Вывод списка после удаления
    printf("\nСписок после удаления узла со значением 555:\n");
    display(&linked_list);

    return 0;
}
