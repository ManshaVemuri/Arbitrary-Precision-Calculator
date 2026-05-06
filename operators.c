#include "apc.h"


int Addition(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2,
             Dlist **result_head)
{
    Dlist *t1 = tail1;  // last digits pointer is set
    Dlist *t2 = tail2;
    int carry = 0;

    *result_head = NULL;
    Dlist *result_tail = NULL;
    
    //loop until list1 & list 2 are NULL and no carry left
    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int d1 = 0;
        int d2 = 0;
        int sum = 0;
        int digit = 0;

        if (t1 != NULL)
        {
            d1 = t1->data;
            t1 = t1->prev;
        }

        if (t2 != NULL)
        {
            d2 = t2->data;
            t2 = t2->prev;
        }

        sum = d1 + d2 + carry;

        if (sum > 9)
        {
            carry = 1;
            digit = sum - 10; // to get unit digit
        }
        else
        {
            carry = 0;
            digit = sum;
        }

        if (insert_first(result_head, &result_tail, digit) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}


int Subtraction(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **result_head)
{
    // to  find lengths of list1 & list2
    int len1 = dll_length(head1);
    int len2 = dll_length(head2);
    int sign = 1; // positive by default 

    
    if (len1 < len2) // so that smaller - bigger
    {
        Dlist *tmpH = head1; //swapping heads
       	head1 = head2;
       	head2 = tmpH;

        Dlist *tmpT = tail1; //swapping tails
       	tail1 = tail2;
       	tail2 = tmpT;
        sign = -1;
    }
    else if (len1 == len2) // if len = then cmp by digits
    {
        int cmp = dll_compare(head1, head2);
        if (cmp == 0) // if digits equal returns 0
        {
            *result_head = NULL;
            Dlist *rt = NULL;
            insert_first(result_head, &rt, 0);
            return SUCCESS;
        }
        if (cmp < 0) //head1<head2 then swap
        {
            Dlist *tmpH = head1;
	    head1 = head2;
	    head2 = tmpH;

            Dlist *tmpT = tail1;
	    tail1 = tail2;
	    tail2 = tmpT;
            sign = -1; // result will be negative
        }
    }

    //now subtraction from tails
    Dlist *t1 = tail1;
    Dlist *t2 = tail2;

    *result_head = NULL;
    Dlist *result_tail = NULL;

    int borrow = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int d1 = 0;
        int d2 = 0;
        int diff = 0;

        if (t1 != NULL)
            d1 = t1->data;

        if (t2 != NULL)
            d2 = t2->data;

        // apply previous borrow
        d1 = d1 - borrow;

        // borrow if needed
        if (d1 < d2)
        {
            d1 = d1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff = d1 - d2;

        if (insert_first(result_head, &result_tail, diff) == FAILURE)
            return FAILURE;

        if (t1 != NULL)
            t1 = t1->prev;

        if (t2 != NULL)
            t2 = t2->prev;
    }

    remove_leading_zeros(result_head);

    //Add negative sign if required
    if (sign == -1)
        insert_first(result_head, &result_tail, -1);
    return SUCCESS;
}

int Multiplication(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **result_head)
{
    *result_head = NULL;

    Dlist *temp_res2 = NULL;       // cumulative result
    Dlist *temp_res2_tail = NULL;

    Dlist *t2 = tail2;             // traverse second number from LSB
    int shift = 0;                 // how many zeros to append

    while (t2 != NULL)
    {
        Dlist *temp_res1 = NULL;   // partial product
        Dlist *temp_res1_tail = NULL;

        int carry = 0;
        Dlist *t1 = tail1;

        //Multiply full number1 with one digit of number2 
        while (t1 != NULL)
        {
            int prod = (t1->data * t2->data) + carry;
            int digit = prod % 10;
            carry = prod / 10;

            if (insert_first(&temp_res1, &temp_res1_tail, digit) == FAILURE)
                return FAILURE;

            t1 = t1->prev;
        }

        if (carry > 0)
        {
            if (insert_first(&temp_res1, &temp_res1_tail, carry) == FAILURE)
                return FAILURE;
        }

        //Add required zeros according to shift
        for (int i = 0; i < shift; i++)
        {
            if (insert_last(&temp_res1, &temp_res1_tail, 0) == FAILURE)
                return FAILURE;
        }

        //Add temp_res1 to cumulative temp_res2
        Dlist *final_res = NULL;

        if (temp_res2 == NULL)
        {
            // First iteration: simply copy partial result
            final_res = copy_dll(temp_res1);
        }
        else
        {
            // calling Addition function 
            if (Addition(temp_res1, temp_res2, temp_res1_tail, temp_res2_tail, &final_res) == FAILURE)
                return FAILURE;
        }

        //Prepare for next iteration
        free_dll(&temp_res1);
        free_dll(&temp_res2);

        temp_res2 = final_res;

        //Update temp_res2_tail
        temp_res2_tail = temp_res2;
        if (temp_res2_tail != NULL)
        {
            while (temp_res2_tail->next != NULL)
                temp_res2_tail = temp_res2_tail->next;
        }

        shift++;        // increase zeros for next multiplication
        t2 = t2->prev;  // move to next digit in number2
    }

    *result_head = temp_res2;
    return SUCCESS;
}

     

int Division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2,
             Dlist **result_head)
{
    //divide by zero check
    if (dll_length(head2) == 1 && head2->data == 0)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    Dlist *qH = NULL;
    Dlist *qT = NULL;
    Dlist *rH = NULL;
    Dlist *rT = NULL;

    Dlist *cur = head1; remove_leading_zeros(&rH); //to normalize remainder after subtraction
            if(rH == NULL)
            {
                    insert_last(&rH, &rT, 0);
            } // to guarentee remainder in never NULL

            // update rT to tail after sub
                rT = rH;
                while (rT->next != NULL)
                    rT = rT->next;
            count++;
        }

        //append quotient digit
        if (insert_last(&qH, &qT, count) == FAILURE)
            return FAILURE;

        cur = cur->next;
    }

    //remove leading zeros in quotient
    remove_leading_zeros(&qH);

    if(qH == NULL)
    {
            insert_last(&qH, &qT, 0);
    }

    *result_head = qH;
    return SUCCESS;
}

    while (cur != NULL)
    {
        // to bring down next digit to remainder
        if (insert_last(&rH, &rT, cur->data) == FAILURE)
            return FAILURE;

        //remove leading zeros from remainder
        remove_leading_zeros(&rH);
        if (rH != NULL)
        {
            //update tail of remainder
            rT = rH;
            while (rT->next != NULL)
                rT = rT->next;
        }

        //counter for each subtaction
        int count = 0;
        while (dll_compare(rH, head2) >= 0)
        {
            //subtract divisor from remainder
            subtract_dll(&rH, &rT, head2, tail2);

	    remove_leading_zeros(&rH); //to normalize remainder after subtraction
	    if(rH == NULL)
	    {
		    insert_last(&rH, &rT, 0);
	    } // to guarentee remainder in never NULL

            // update rT to tail after sub
                rT = rH;
                while (rT->next != NULL)
                    rT = rT->next;
	    count++;
        }

        //append quotient digit
        if (insert_last(&qH, &qT, count) == FAILURE)
            return FAILURE;

        cur = cur->next;
    }

    //remove leading zeros in quotient
    remove_leading_zeros(&qH);

    if(qH == NULL)
    {
	    insert_last(&qH, &qT, 0);
    }

    *result_head = qH;
    return SUCCESS;
}

