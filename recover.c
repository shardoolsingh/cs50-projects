#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check for the required number of command line arguments
    if(argc != 2)
    {
        printf("Usage: recover file ...\n");
        return 1;
    }

    //Remember input filename
    char *infile = argv[1];

    //Open infile
    FILE *raw_file = fopen(infile, "r");
    if(raw_file == NULL)
    {
        printf("Cannot open input file: %s.\n", infile);
        return 1;
    }
    
    int n = 512;    //Number of bytes to read at once
    unsigned char *buffer = malloc(n);   //create block
    FILE *img = NULL;    //pointer to store image
    char filename[100];     //to store output image name
    int count = 0;
    
    //Repeat until 'End-of-File'
    while(fread(buffer, n, 1, raw_file))
    {
        //Determine if the start of new JPEG
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //close the previous image, if any
            if(count > 0)
            {
                fclose(img);
            }
            
            //print to the filename
            sprintf(filename, "%03d.jpg", count);
            
            //open the img
            img = fopen(filename, "w");
            
            //increase the counter
            count++;
        }
        
        if(count > 0)
        {
            fwrite(buffer, n, 1, img);;
        }
    }

    //Close files
    fclose(img);
    fclose(raw_file);
    free(buffer);

    return 0;
}