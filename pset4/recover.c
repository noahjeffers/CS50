#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h> 

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        // create the necessary variables
        typedef uint8_t BYTE;
        //buffer to hold the value that will be written
        BYTE buffer[512];
        //array to hold the filename 
        char filename[8];
        //image count to create the filename
        int imageCount = 0;
        FILE *img; 
        
        bool writing = false;

        //open the file provided through the terminal
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Incorrect File\n");
            printf("Usage: ./recover image\n");
            return 1;
        }
        //loop through the file 512 bytes at a time
        while (fread(buffer, 512, 1, file) == 1)
        {
            //assess the buffer to see if it is the start of new image file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3]) & 0xf0) == 0xe0)
            {
                // if the buffer is the start of a new image close the previous image file
                if (writing == true)
                {
                    fclose(img);
                }
                
                writing = true;
                //create a filename
                sprintf(filename, "%03i.jpg", imageCount);
                //open the file
                img = fopen(filename, "w");
                //write the buffer to the file
                fwrite(buffer, sizeof(buffer), 1, img);
                // increase the image count by 1 for the next image
                imageCount++;
            }
            //if we have already started writing a file this continues to write to the image file
            else if (writing == true)
            {
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
        fclose(file);
    }
}
