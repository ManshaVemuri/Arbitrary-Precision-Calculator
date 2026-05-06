#include "apc.h"

//Insert at end
int insert_last(Dlist **head, Dlist **tail, data_t data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (new_node == NULL)
        return FAILURE;

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = *tail;

    if (*tail != NULL)
    {
        (*tail)->next = new_node;
    }
    else
    {
        *head = new_node; 
    }

    *tail = new_node;
    return SUCCESS;
}

//insert first
int insert_first(Dlist **head, Dlist **tail, data_t data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (new_node == NULL)
        return FAILURE;

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = *head;

    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    else
    {
        *tail = new_node;
    }

    *head = new_node;
    return SUCCESS;
}

int str_to_list(char *str, Dlist **head, Dlist **tail)
{
    if (str == NULL)
        return FAILURE;

    for (int i = 0; str[i] != '\0'; i++) 
    {
        char c = str[i];
        if (c < '0' || c > '9') // check if char is not digit
            return FAILURE;

        int digit = c - '0'; // convert into integer
        if (insert_last(head, tail, digit) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}


int dll_length(Dlist *head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}


int dll_compare(Dlist *h1, Dlist *h2)
{
    int l1 = dll_length(h1);
    int l2 = dll_length(h2);

    if (l1 > l2)
        return 1;
    if (l1 < l2)
        return -1;

    // if same length then compare digit by digit from msb
    while (h1 != NULL && h2 != NULL)
    {
        if (h1->data > h2->data)
            return 1;
        if (h1->data < h2->data)
            return -1;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}


Dlist *copy_dll(Dlist *src)
{
    if (src == NULL)
        return NULL;

    while (src->prev != NULL) // move to start of src list
        src = src->prev;

    Dlist *newH = NULL;
    Dlist *newT = NULL;

    while (src != NULL) //copy source to new list
    {
        if (insert_last(&newH, &newT, src->data) == FAILURE)
        {
            //free partially built list
            free_dll(&newH);
            return NULL;
        }
        src = src->next;
    }

    return newH;
}

int subtract_dll(Dlist **dividendH, Dlist **dividendT, Dlist *divisorH, Dlist *divisorT)
{
    if (dividendH == NULL || *dividendH == NULL)
        return FAILURE;

    Dlist *t1 = *dividendT;  // start from tail of dividend
    Dlist *t2 = divisorT;    // start from tail of divisor
    int borrow = 0;

    while (t1 != NULL) //loop until all digits of dividend are done 
    {
        int d1 = t1->data - borrow; //current dividend minus if borrow
        int d2 = 0;

        if (t2 != NULL)
            d2 = t2->data;

        if (d1 < d2)
        {
            d1 = d1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        t1->data = d1 - d2;

        t1 = t1->prev;
        if (t2 != NULL)
            t2 = t2->prev;
    }

    // No need to handle negative result, because division always ensures dividend >= divisor here
    return SUCCESS;
}



void remove_leading_zeros(Dlist **head)
{
    //if list empty or head pt invalid
    if (head == NULL || *head == NULL)
        return;
    
    // remove zeros from front 
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *tmp = *head;  //store cur head
        *head = (*head)->next; // move head forward
        (*head)->prev = NULL; // new head prev is NULL
        free(tmp); //delete old zero node
    }
}


void free_dll(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        if (head)
	*head = NULL;
        return;
    }

    Dlist *cur = *head;
    while (cur != NULL) //free nodes one by one
    {
        Dlist *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}

void dll_print(Dlist *head)
{
    if (head == NULL)
    {
        printf("0"); // print zero if empty list
        return;
    }
    while (head != NULL)
    {
        if (head->data == -1)  //sign indicator
            printf("-");
        else
            printf("%d", head->data);
        head = head->next;
    }
}

