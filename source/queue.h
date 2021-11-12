#pragma once

template <typename T>
struct Queue {

    struct QNode {
        T data;
        QNode* next;
        QNode(T d)
        {
            data = d;
            next = nullptr;
        }
    };

    QNode* front;
    QNode* rear;
    
    Queue() { front = rear = nullptr; }
    
    void enQueue(T x) {
        QNode* temp = new QNode(x);

        if (!rear) {
            front = rear = temp;
            return;
        }

        rear->next = temp;
        rear = temp;
    }

    void deQueue() {
        if (!front) return;

        QNode* temp = front;
        front = front->next;

        if (!front) rear = nullptr;
        delete (temp);
    }

    size_t size() {
        if (front == NULL) return 0; else {
            size_t size = 1;
            QNode* temp = front;
            while (temp->next != nullptr) {
                temp = temp->next;
                size++;
            }
            return size;
        }
    }
};
