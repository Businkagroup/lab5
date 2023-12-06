#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

// создаем структуру нода
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// создаем структуру очереди
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// иницализируем очередь
void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// добавляем элемент в конец
void enqueue(Queue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        // если очередь пуста, устанавливаем front и rear на новый нод
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        // или добавляем новый нод в конец очереди и обновляем rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// пуста ли очередь
bool isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// удаление элемента из начала очереди и возврат его значения
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        // Обработка попытки удаления из пустой очереди
        printf("Error: Queue is empty.\n");
        return -1; // Возврат значения по умолчанию (можно изменить)
    }

    // сохраняем значение front обновляем front и освобождаем память
    int value = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;

    // если после удаления очередь стала пустой обновляем rear
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return value;
}




void testEnqueue(Queue* queue, int value) {
    printf("Enqueue %d\n", value);
    enqueue(queue, value);
}

void testDequeue(Queue* queue) {
    if (!isEmpty(queue)) {
        int value = dequeue(queue);
        printf("Dequeue: %d\n", value);
    }
    else {
        printf("Dequeue: Queue is empty.\n");
    }
}

void testIsEmpty(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
    }
    else {
        printf("Queue is not empty.\n");
    }
}

int main() {
    Queue myQueue;
    initQueue(&myQueue);

    testIsEmpty(&myQueue);

    testEnqueue(&myQueue, 10);
    testEnqueue(&myQueue, 20);
    testEnqueue(&myQueue, 30);

    testDequeue(&myQueue);
    testDequeue(&myQueue);
    testDequeue(&myQueue);
    testDequeue(&myQueue);

    testIsEmpty(&myQueue);

    return 0;
}

