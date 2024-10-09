#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc node cho danh sách liên kết
typedef struct Node {
    char *name;
    struct Node *next;
} Node;

// Hàm tạo một node mới
Node* createNode(const char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->name = strdup(name);
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm một node vào danh sách liên kết
void addNode(Node **head, const char *name) {
    Node *newNode = createNode(name);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Hàm tách tên chính và họ đệm
void splitName(const char *fullName, char **firstName, char **lastName) {
    *firstName = strdup(fullName);
    *lastName = strrchr(*firstName, ' ');
    if (*lastName != NULL) {
        **lastName = '\0';
        (*lastName)++;
    } else {
        *lastName = *firstName;
    }
}

// Hàm so sánh hai tên
int compareNames(const char *name1, const char *name2) {
    char *firstName1, *lastName1;
    char *firstName2, *lastName2;

    splitName(name1, &firstName1, &lastName1);
    splitName(name2, &firstName2, &lastName2);

    int cmp = strcmp(lastName1, lastName2);
    if (cmp == 0) {
        cmp = strcmp(firstName1, firstName2);
    }

    free(firstName1);
    free(firstName2);
    return cmp;
}

// Hàm sắp xếp danh sách liên kết
void sortList(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node *i, *j;
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (compareNames(i->name, j->name) > 0) {
                char *temp = i->name;
                i->name = j->name;
                j->name = temp;
            }
        }
    }
}

// Hàm in danh sách liên kết
void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

// Hàm giải phóng bộ nhớ của danh sách liên kết
void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    char buffer[100];

    printf("Enter names (type 'done' to finish):\n");

    while (1) {
        printf("Enter name: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0'; // Xóa ký tự xuống dòng

        if (strcmp(buffer, "done") == 0) {
            break;
        }

        addNode(&head, buffer);
    }

    sortList(&head);

    printf("\nSorted names:\n");
    printList(head);

    freeList(head);
    return 0;
}
