#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    //Ask for text
    string text = get_string("Enter Text: ");

    //Total number of characters, or length
    int length = strlen(text);

    //Total number of spaces, total words = spaces + 1
    int i, spaces;
    spaces = 0;
    for(i=0; i<length; i++)
    {
        if((int) text[i] == 32)
        {
            spaces++;
        }
    }
    
    int words = spaces + 1; //total number of words

    //Total number of sentences
    int j, sentences;
    sentences = 0;
    for(j=0; j<length; j++)
    {
        if((int) text[j] == 33 || (int) text[j] == 46 || (int) text[j] == 63 )
        {
            sentences++;
        }
    }
    
    //Average number of letters & sentences per 100 words
    float L, S;
    
    L = (length/(float) words) * 100;
    S = (sentences/(float) words) * 100;
    
    //Calculate Coleman-Liau index
    int CL = 0.0588 * L - 0.296 * S - 15.8;
    
    //Print C-L index
    if(CL < 1)
    {
        printf("Before Grade 1.\n");
    }
    else if(CL >= 16)
    {
        printf("Grade 16+.\n");
    }
    else
    {
        printf("Grade: %d.\n", CL);
    }

    return 0;
}