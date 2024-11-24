/*******************************
    *Simple Credit Card Validator
    *For Visa, American Express & MasterCard
    *Shardool Singh
    * twitter: @shardool_singh, GitHub: @shardoolsingh
    
    
********************************/

#include <stdio.h>

//Constant
const long CARD_NUMBER;

int main(void)
{
    //Ask for card number
    do
    {
        printf("Credit Card Number: ");
        scanf("%ld", &CARD_NUMBER);
    }
    while(CARD_NUMBER < 0);

    //Find total number of digits on card
    long digits = CARD_NUMBER;
    int count;

    for(count=0; digits>0; count++)
    {
        digits = digits / 10;
    }

    //Check if number is 13, 15 or 16 digit long, else declare INVALID
    if(count != 13 && count != 15 && count != 16)
    {
        printf("INVALID.\n");
    }
    
    else
    {
        //Store each digit of credit card in an Array
        int card_store[count];
        long digits2 = CARD_NUMBER;
        int i;
    
        for(i=0; i<count; i++)
        {
            card_store[i] = digits2 % 10;
            digits2 = digits2 / 10;
        }
    
        //Do checksum validation
        int card_store2[count/2]; //Would store an extra number at the end if count is odd number, won't concern us here
        int j, k, l, temp;
        int sum1 = 0;
        
        for(j=1; j<=count; j = j + 2)
        {
            card_store2[l] = (card_store[j] * 2);
            temp = card_store2[l] % 10 + (card_store2[l] / 10) % 10;
            sum1 = sum1 + temp;
        }
        
        //sum2 for checksum
        int sum2 = 0;
        
        for(k=0; k< count; k = k + 2)
        {
            sum2 = sum2 + card_store[k];
        }
        
        //Verification for Checksum
        if ((sum1 + sum2) % 10 != 0)
        {
            printf("INVALID.\n");
        }
        else
        {
                //Check for the card providers
            
                //Check if Card is from VISA
            if(card_store[count - 1] == 4 && (count == 13 || count == 16))
            {
                printf("VISA.\n");
            }
                //Check if Card is from American Express
            if(card_store[count - 1] == 3 && (card_store[count - 2] == 4 || card_store[count - 2] == 7) && count == 15)
            {
                printf("American Express.\n");
            }
                //Check if Card is from MasterCard
            if(card_store[count - 1] == 5 && (card_store[count - 2] == 1 || card_store[count - 2] == 2 || card_store[count - 2] == 3 || card_store[count - 2] == 4 || card_store[count - 2] == 5) && count == 16)
            {
                printf("MasterCard.\n");
            }
        }
    }
    
    return 0;
}