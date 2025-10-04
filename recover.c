#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int JPEG_SIZE = 512;

int main(int argc, char *argv[])
{
    //Accepts only a SINGLE COMMAND LINE ARGUMENT
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1],"rb");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[JPEG_SIZE];//Creates a buffer array variable with a size of 512

    //File Handling
    char filename[8]; //Make a variable to hold the filename like "000.jpg"
    FILE *img = NULL;//Initiates a file variable setting it to null TO INDICATE THERE IS NO JPEG FOUND YET
    int file_number = 0;

    //Repeat until the end of the card, read 512 BYTES into a BUFFER
    while(fread(buffer, sizeof(BYTE), JPEG_SIZE, card) != 0) //Loop to READ 512 elements (JPEG_SIZE), each 1 byte (uint8_t), from card file INTO the BUFFER ARRAY starting at the FIRST ELEMENT
                                                             //Each time the loop runs, fread() fills the buffer array with the next 512 bytes from the file card.
    {
        //If it is the start of a new JPEG File
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new filename, e.g., "000.jpg"
            sprintf(filename, "%03i.jpg", file_number);
            file_number++;

            // Open a new JPEG file to write to
            img = fopen(filename, "wb");
            if (img == NULL)
            {
                printf("Could not create output JPEG %s\n", filename);
                fclose(card);
                return 2;
            }

            // Write the current buffer into the new JPEG
            fwrite(buffer, sizeof(BYTE), JPEG_SIZE, img);
        }
        else if (img != NULL)
        {
            // If currently writing a JPEG, continue writing
            fwrite(buffer, sizeof(BYTE), JPEG_SIZE, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}




















































