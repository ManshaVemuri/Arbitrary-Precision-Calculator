#include "apc.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *res_head = NULL;

    char operator;

    /* Validate CLA */
    if (argc != 4)
    {
        printf("INFO: Invalid CLA\n");
        printf("Expected: ./a.out <num1> <operator> <num2>\n");
        printf("NOTE: For multiplication, use quotes: '*'\n");
        return FAILURE;
    }

    /* Validate operator */
    if (strlen(argv[2]) != 1)
    {
        printf("INFO: Invalid operator: should be single character\n");
        return FAILURE;
    }

    operator = argv[2][0];
    if (operator != '+' && operator != '-' && operator != '*' && operator != '/')
    {
        printf("INFO: Invalid operator\n");
        return FAILURE;
    }

    /* Validate first number */
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("INFO: First number contains invalid characters\n");
            return FAILURE;
        }
    }

    /* Validate second number */
    for (int i = 0; argv[3][i] != '\0'; i++)
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
            printf("INFO: Second number contains invalid characters\n");
            return FAILURE;
        }
    }

    /* Convert strings to DLL */
    if (str_to_list(argv[1], &head1, &tail1) == FAILURE)
    {
        printf("Error converting first number to list\n");
        return FAILURE;
    }

    if (str_to_list(argv[3], &head2, &tail2) == FAILURE)
    {
        printf("Error converting second number to list\n");
        return FAILURE;
    }

    int status = FAILURE;

    switch (operator)
    {
        case '+':
            status = Addition(head1, head2, tail1, tail2, &res_head);
            break;

        case '-':
            status = Subtraction(head1, head2, tail1, tail2, &res_head);
            break;

        case '*':
            status = Multiplication(head1, head2, tail1, tail2, &res_head);
            break;

        case '/':
            status = Division(head1, tail1, head2, tail2, &res_head);
            break;
    }

    if (status == SUCCESS)
    {
        printf("Result = ");
        dll_print(res_head);
        printf("\n");
    }
    else
    {
        printf("Operation failed!\n");
    }

    /* free memory */
    free_dll(&head1);
    free_dll(&head2);
    free_dll(&res_head);

    return SUCCESS;
}

