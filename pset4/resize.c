/****************************************************************************
* copy.c
*
* Computer Science 50
* Problem Set 4
*
* Copies a BMP piece by piece, just because.
***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize multiple infile outfile\n");
        return 1;
    }
    
    // remember multiple
    int multiple = atoi(argv[1]);
       
    // ensure n is is a positive int less than or equal to 100
    if(multiple > 100 || multiple < 1)
    {
        printf("Multiple exceeds the limit\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // initialize old width and height
    int old_width = bi.biWidth;
    int old_height = bi.biHeight;
   
    // update width and height
    bi.biWidth *= multiple;
    bi.biHeight *= multiple;
       
    // determine padding for scanlines
    int old_padding = (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new image size
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    
    // new file size
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // allocate storage for buffer to hold scanline
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_height); i < biHeight; i++)
    {
        int counter = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < old_Width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // assign triple to buffer
            for(int count = 0; count < scale; count++)
            {
                *(buffer+(counter)) = triple;
                counter++;
            }
        }
            
        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);

        // write RGB triple to outfile
           for(int r = 0; r < multiple; r++)
           {
                fwrite((buffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);
                // write padding to outfile
                for (int k = 0; k < padding; k++)
                    fputc(0x00, outptr);
           }
    }

    // free buffer
    free(buffer);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
