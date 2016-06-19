#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);              // atoi converts string to int
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // check the limits of n
    if( n < 1 || n > 100)
    {
        printf("n should belong to [1,100]");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf2;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf2 = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi2;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi2 = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    bi2.biWidth = n * bi.biWidth;                                                       // In pixels
    bi2.biHeight = n * bi.biHeight;                                                     // In pixels
    
    // determine padding for scanlines
    int padding2 =  (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;                    // In bytes
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;                      // In bytes
    //printf("%d  %d \n  %d  %d\n",bi.biWidth,bi2.biWidth, padding, padding2);
    
    bi2.biSizeImage = ((bi2.biWidth * 3) + padding2) * abs(bi2.biHeight);               //  In bytes
    bf2.bfSize = bi2.biSizeImage + 0x36;      // In bytes

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi2.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for(int z = 0; z < n; z++)
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        if( i % n != n-1)
            fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        else
            fseek(inptr, padding, SEEK_CUR);
            
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding2; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
