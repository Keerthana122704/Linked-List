//CIRUCLAR SINGLE LINKED LIST

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};
int count_list(struct node *head) {
    if (head == NULL) return 0;
    int count = 1;
    struct node *ptr = head->link;
    while (ptr != head) {
        count++;
        ptr = ptr->link;
    }
    return count;
}
void add_at_start(struct node **head, struct node *temp) {
    if (*head == NULL) {
        temp->link = temp;
        *head = temp;
    } else {
        struct node *ptr = *head;
        while (ptr->link != *head)
            ptr = ptr->link;
        temp->link = *head;
        ptr->link = temp;
        *head = temp;
    }
}
void add_at_middle(struct node *head, struct node *temp, int pos) {
    if (pos <= 1) {
        printf("Use 'add at start' for position 1.\n");
        return;
    }
    struct node *ptr = head;
    for (int i = 1; i < pos - 1 && ptr->link != head; i++)
        ptr = ptr->link;

    temp->link = ptr->link;
    ptr->link = temp;
}
void add_at_end(struct node *head, struct node *temp) {
    if (head == NULL) {
        temp->link = temp;
        head = temp;
        return;
    }
    struct node *ptr = head;
    while (ptr->link != head)
        ptr = ptr->link;

    ptr->link = temp;
    temp->link = head;
}
void delete_from_start(struct node **head) {
    if (*head == NULL) {
        printf("\nThe list is empty.\n");
        return;
    }
    if ((*head)->link == *head) {
        printf("\nThe deleted element is %d\n", (*head)->data);
        free(*head);
        *head = NULL;
    } else {
        struct node *last = *head;
        while (last->link != *head)
            last = last->link;

        struct node *temp = *head;
        printf("\nThe deleted element is %d\n", temp->data);
        *head = (*head)->link;
        last->link = *head;
        free(temp);
    }
}
void delete_from_end(struct node **head) {
    if (*head == NULL) {
        printf("\nThe list is empty.\n");
        return;
    }
    if ((*head)->link == *head) {
        printf("\nThe deleted element is %d\n", (*head)->data);
        free(*head);
        *head = NULL;
    } else {
        struct node *ptr = *head;
        while (ptr->link->link != *head)
            ptr = ptr->link;
        struct node *temp = ptr->link;
        printf("\nThe deleted element is %d\n", temp->data);
        ptr->link = *head;
        free(temp);
    }
}
void delete_from_middle(struct node **head, int pos) {
    if (*head == NULL) {
        printf("\nThe list is empty.\n");
        return;
    }
    if (pos <= 1) {
        printf("Use 'delete from start' for position 1.\n");
        return;
    }
    struct node *ptr = *head;
    for (int i = 1; i < pos - 1 && ptr->link != *head; i++)
        ptr = ptr->link;
    if (ptr->link == *head) {
        printf("Invalid position.\n");
        return;
    }
    struct node *temp = ptr->link;
    ptr->link = temp->link;
    printf("\nThe deleted element is %d\n", temp->data);
    free(temp);
}
void traverse_list(struct node *head) {
    if (head == NULL) {
        printf("\nThe list is empty.\n");
        return;
    }
    struct node *ptr = head;
    printf("\nThe elements are:\n");
    do {
        printf("%d\n", ptr->data);
        ptr = ptr->link;
    } while (ptr != head);
}
int main() {
    char ch, c;
    int p;
    struct node *head = NULL;

    struct node *first = (struct node *)malloc(sizeof(struct node));
    if (!first) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Enter the first node: ");
    scanf("%d", &first->data);
    first->link = first;
    head = first;
    while (1) {
        printf("\nChoose an operation:\na. Add\nb. Delete\nc. Traverse\nd. Quit\n");
        scanf(" %c", &ch);
        switch (ch) {
            case 'a': {
                struct node *temp = (struct node *)malloc(sizeof(struct node));
                if (!temp) {
                    printf("Memory allocation failed\n");
                    break;
                }
                printf("Enter the element: ");
                scanf("%d", &temp->data);
                temp->link = NULL;
                printf("Add at:\na. Start\nb. Middle\nc. End\n");
                scanf(" %c", &c);
                int count = count_list(head);
                switch (c) {
                    case 'a':
                        add_at_start(&head, temp);
                        break;
                    case 'b':
                        printf("Enter the position: ");
                        scanf("%d", &p);
                        if (p > count + 1 || p < 1)
                            printf("Invalid position. List size: %d\n", count);
                        else
                            add_at_middle(head, temp, p);
                        break;
                    case 'c':
                        add_at_end(head, temp);
                        break;
                    default:
                        printf("Invalid input for add.\n");
                        free(temp);
                        break;
                }
                break;
            }
            case 'b': {
                if (head == NULL) {
                    printf("The list is already empty.\n");
                    break;
                }
                printf("Delete from:\na. Start\nb. Middle\nc. End\n");
                scanf(" %c", &c);
                int count = count_list(head);
                switch (c) {
                    case 'a':
                        delete_from_start(&head);
                        break;
                    case 'b':
                        printf("Enter the position: ");
                        scanf("%d", &p);
                        if (p > count || p < 1)
                            printf("Invalid position. List size: %d\n", count);
                        else
                            delete_from_middle(&head, p);
                        break;
                    case 'c':
                        delete_from_end(&head);
                        break;
                    default:
                        printf("Invalid input for delete.\n");
                        break;
                }
                break;
            }
            case 'c':
                traverse_list(head);
                break;
            case 'd':
                printf("\nExited successfully!\n");
                exit(0);
                break;
            default:
                printf("Invalid main choice.\n");
                break;
        }
    }
    return 0;
}
