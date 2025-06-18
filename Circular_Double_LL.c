#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

int count_list(struct node *head) {
    if (head == NULL)
        return 0;

    int count = 1;
    struct node *ptr = head->next;
    while (ptr != head) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

void add_at_start(struct node **head, struct node *temp) {
    if (*head == NULL) {
        *head = temp;
        temp->next = temp;
        temp->prev = temp;
    } else {
        struct node *last = (*head)->prev;

        temp->next = *head;
        temp->prev = last;
        last->next = temp;
        (*head)->prev = temp;
        *head = temp;
    }
}

void add_at_middle(struct node *head, struct node *temp, int pos) {
    int n = count_list(head);
    if (pos <= 1) {
        printf("Position too small. Use 'add at start'.\n");
        return;
    }
    if (pos > n) {
        printf("Position too large. Use 'add at end'.\n");
        return;
    }

    struct node *ptr = head;
    for (int i = 1; i < pos - 1; i++)
        ptr = ptr->next;

    temp->next = ptr->next;
    temp->prev = ptr;
    ptr->next->prev = temp;
    ptr->next = temp;
}

void add_at_end(struct node *head, struct node *temp) {
    if (head == NULL) {
        temp->next = temp;
        temp->prev = temp;
        head = temp;
        return;
    }

    struct node *last = head->prev;

    temp->next = head;
    temp->prev = last;
    last->next = temp;
    head->prev = temp;
}

void del_from_start(struct node **head) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    struct node *last = (*head)->prev;
    struct node *temp = *head;
    *head = (*head)->next;
    last->next = *head;
    (*head)->prev = last;
    free(temp);
}

void del_from_middle(struct node *head, int pos) {
    int n = count_list(head);
    if (pos <= 1 || pos > n) {
        printf("Invalid position for middle delete.\n");
        return;
    }

    struct node *ptr = head;
    for (int i = 1; i < pos - 1; i++)
        ptr = ptr->next;

    struct node *temp = ptr->next;
    ptr->next = temp->next;
    temp->next->prev = ptr;
    free(temp);
}

void del_from_end(struct node **head) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }

    struct node *last = (*head)->prev;
    struct node *prev = last->prev;

    prev->next = *head;
    (*head)->prev = prev;
    free(last);
}

void traverse_list(struct node *head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct node *ptr = head;
    printf("The elements are:\n");
    do {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    } while (ptr != head);
}

int main() {
    int p;
    char ch;

    while (1) {
        printf("\nEnter your choice:\na. Add\nb. Delete\nc. Traverse\nd. Quit\n");
        scanf(" %c", &ch);
        switch (ch) {
            case 'a': {
                printf("Enter the element: ");
                struct node *temp = malloc(sizeof(struct node));
                scanf("%d", &temp->data);
                temp->next = NULL;
                temp->prev = NULL;

                printf("Add at:\na. Start\nb. Middle\nc. End\n");
                scanf(" %c", &ch);
                switch (ch) {
                    case 'a':
                        add_at_start(&head, temp);
                        break;
                    case 'b':
                        printf("Enter the position: ");
                        scanf("%d", &p);
                        add_at_middle(head, temp, p);
                        break;
                    case 'c':
                        add_at_end(head, temp);
                        break;
                    default:
                        printf("Invalid input for addition.\n");
                        free(temp); // Avoid memory leak
                }
                break;
            }

            case 'b': {
                printf("Delete from:\na. Start\nb. Middle\nc. End\n");
                scanf(" %c", &ch);
                switch (ch) {
                    case 'a':
                        del_from_start(&head);
                        break;
                    case 'b':
                        printf("Enter the position: ");
                        scanf("%d", &p);
                        del_from_middle(head, p);
                        break;
                    case 'c':
                        del_from_end(&head);
                        break;
                    default:
                        printf("Invalid input for deletion.\n");
                }
                break;
            }

            case 'c':
                traverse_list(head);
                break;

            case 'd':
                printf("Exited successfully!\n");
                exit(0);

            default:
                printf("Invalid main menu choice.\n");
        }
    }

    return 0;
}
