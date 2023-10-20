#include"bigint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n {
    int data;
    struct n* next;
} n;

void push(n** head, int data) {
    n* new_node = (n*)malloc(sizeof(n));
    new_node->data = data;
    new_node->next = (*head);
    (*head) = new_node;
}

void display(n* head) {
    if (head == NULL) {
        return;
    }
    display(head->next);
    printf("%d", head->data);
}

n* addTwobigNumbers(n* l1, n* l2) {
    int carry = 0;
    n* dummy = (n*)malloc(sizeof(n));
    n* current = dummy;

    while (l1 || l2) {
        int x = l1 ? l1->data : 0;
        int y = l2 ? l2->data : 0;

        int total = x + y + carry;
        carry = total / 10;

        current->next = (n*)malloc(sizeof(n));
        current = current->next;
        current->data = total % 10;
        current->next = NULL;

        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }

    if (carry > 0) {
        current->next = (n*)malloc(sizeof(n));
        current = current->next;
        current->data = carry;
        current->next = NULL;
    }

    n* result = dummy->next;
    free(dummy);
    return result;
}

n* subtractLinkedLists(n* l1, n* l2) {
    n* result = NULL;
    n* current = NULL;
    int borrow = 0;

    while (l1 || l2 || borrow) {
        int x = (l1) ? l1->data : 0;
        int y = (l2) ? l2->data : 0;
        int diff = x - y - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        n* newNode = (n*)malloc(sizeof(n));
        newNode->data = diff;
        newNode->next = NULL;

        if (current) {
            current->next = newNode;
            current = current->next;
        } else {
            result = newNode;
            current = result;
        }

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return result;
}

n* multiplyLinkedLists(n* l1, n* l2) {
    if (!l1 || !l2) {
        return NULL;
    }

    int l1Length = 0;
    int l2Length = 0;
    n* l1Current = l1;
    n* l2Current = l2;

    while (l1Current) {
        l1Length++;
        l1Current = l1Current->next;
    }

    while (l2Current) {
        l2Length++;
        l2Current = l2Current->next;
    }

    int totalLength = l1Length + l2Length;
    int resultArray[totalLength];
    for (int i = 0; i < totalLength; i++) {
        resultArray[i] = 0;
    }

    l1Current = l1;
    int l2Value;
    for (int i = 0; l1Current; i++) {
        l2Current = l2;
        int carry = 0;
        for (int j = 0; l2Current; j++) {
            int product = l1Current->data * l2Current->data + resultArray[i + j] + carry;
            carry = product / 10;
            resultArray[i + j] = product % 10;
            l2Current = l2Current->next;
        }
        if (carry > 0) {
            resultArray[i + l2Length] += carry;
        }
        l1Current = l1Current->next;
    }

    n* result = NULL;
    n* current = NULL;
    int i = totalLength - 1;
    while (i >= 0 && resultArray[i] == 0) {
        i--;
    }
    while (i >= 0) {
        n* newNode = (n*)malloc(sizeof(n));
        newNode->data = resultArray[i];
        newNode->next = NULL;
        if (current == NULL) {
            current = newNode;
            result = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
        i--;
    }

    return result;
}
n* divideLinkedLists(n* dividend, n* divisor) {
    if (!divisor || divisor->data == 0) {
        printf("Division by zero is not allowed.\n");
        return NULL;
    }

    n* result = NULL;
    n* current = NULL;
    n* temp = NULL;
    n* quotient = NULL;

    while (dividend) {
        int quotientDigit = 0;

        while (isGreaterOrEqual(dividend, divisor)) {
            dividend = subtractLinkedLists(dividend, divisor);
            quotientDigit++;
        }

        append(&quotient, quotientDigit);
        append(&result, quotientDigit);

        if (temp) {
            temp->next = result;
            result = temp;
        }

        if (!current) {
            current = result;
        }

        while (result) {
            temp = result;
            result = result->next;
        }
    }

    return quotient;
}

n* stringToLinkedList(const char* str) {
    n* head = NULL;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        push(&head, str[i] - '0');
    }
    return head;
}
