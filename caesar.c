//Caesar program to encrypt a plaintext

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//main function
int main(int argc, string argv[])
{
    //Check for invalid input at CLI
    if(argc != 2)
    {
        printf("Usage: ./caesar key ...\n");
        return 1;
    }
    
    //convert string key into an integer
    int key = atoi(argv[1]);
    
    //validate key
    if(key < 0)
    {
        printf("Usage: ./caesar key(positive integer) ...\n");
        return 2;
    }
    
    //Get 'plaintext'
    string plaintext = get_string("Enter Text: ");
    
    //Convert 'plaintext' to 'ciphertext'
    printf("Ciphertext: ");
    
    int count = strlen(plaintext);
    for(int i = 0; i < count; i++)
    {
        if(islower(plaintext[i]))
        {
            printf("%c", (((plaintext[i] + key) - 97) % 26) + 97);
        }
        
        else if(isupper(plaintext[i]))
        {
            printf("%c", (((plaintext[i] + key) - 65) % 26) + 65);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}