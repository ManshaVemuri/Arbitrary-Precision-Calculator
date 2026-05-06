#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef struct dnode
{
    data_t data;
    struct dnode *prev;
    struct dnode *next;
} Dlist;


int insert_last(Dlist **head, Dlist **tail, data_t data);
int insert_first(Dlist **head, Dlist **tail, data_t data);
int str_to_list(char *str, Dlist **head, Dlist **tail);
int dll_length(Dlist *head);
int dll_compare(Dlist *head1, Dlist *head2);
Dlist *copy_dll(Dlist *src);
int subtract_dll(Dlist **dividendH, Dlist **dividendT, Dlist *divisorH, Dlist *divisorT);
void remove_leading_zeros(Dlist **head);
void free_dll(Dlist **head);
void dll_print(Dlist *head);


int Addition(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2,
             Dlist **result_head);

int Subtraction(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2,
                Dlist **result_head);

int Multiplication(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2,
                   Dlist **result_head);

int Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **result_head);

#endif

