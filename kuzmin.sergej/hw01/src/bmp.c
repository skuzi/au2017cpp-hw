#include "bmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readBMP(FILE *f, bmpImg *image) {
    BITMAPFILEHEADER* bitmapFileHeader = &image->bitmapFileHeader;
    BITMAPINFOHEADER* bitmapInfoHeader = &image->bitmapInfoHeader;

    if(!fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, f)) {
        return 1;
    }

    if(!fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, f)) {
        return 1;
    }

    fseek(f, bitmapFileHeader->bfOffBits, SEEK_SET);

    image->pixel_array = malloc(bitmapInfoHeader->biHeight * sizeof(pixel*));
    if(image->pixel_array == NULL){
        return 1;
    }

    uint32_t padd = 4 - (bitmapInfoHeader->biWidth * 3) % 4;
    if(padd == 4) {
        padd = 0;
    }

    for(int i = 0; i < bitmapInfoHeader->biHeight; i++) {
        image->pixel_array[i] = malloc(bitmapInfoHeader->biWidth * sizeof(pixel));
        if(image->pixel_array[i] == NULL) {
            return 1;
        }

        if(fread(image->pixel_array[i], sizeof(pixel), bitmapInfoHeader->biWidth, f) != bitmapInfoHeader->biWidth) {
            return 1;
        }

        uint32_t tmp = 0;
        if(fread(&tmp, sizeof(uint8_t), padd, f) != padd) {
            return 1;
        }
    }
    
    return 0;
}

void writeBMP(FILE *f, bmpImg *image) {
    BITMAPFILEHEADER* bitmapFileHeader = &image->bitmapFileHeader;
    BITMAPINFOHEADER* bitmapInfoHeader = &image->bitmapInfoHeader;

    fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
    
    fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);

    fseek(f, bitmapFileHeader->bfOffBits, SEEK_SET);

    uint32_t padd = 4 - (bitmapInfoHeader->biWidth * 3) % 4;
    if(padd == 4) {
        padd = 0;
    }

    for(int i = 0; i < bitmapInfoHeader->biHeight; i++) {
        fwrite(image->pixel_array[i], sizeof(pixel), bitmapInfoHeader->biWidth, f);

        uint32_t tmp = 0;
        fwrite(&tmp, sizeof(uint8_t), padd, f);
    }
}

int cropBMP(bmpImg *image, int32_t x, int32_t y, int32_t w, int32_t h) {

    pixel **pixel_array = malloc(h * sizeof(pixel*));
    if(pixel_array == NULL) {
        return 1;
    }

    for(int i = 0; i < h; i++) {
        pixel_array[i] = malloc(w * sizeof(pixel));
        if(pixel_array[i] == NULL) {
            return 1;
        }

        memcpy(pixel_array[i], image->pixel_array[y + i] + x, w * sizeof(pixel));
    }

    for(int i = 0; i < image->bitmapInfoHeader.biHeight; i++) {
        free(image->pixel_array[i]);
    }
    free(image->pixel_array);

    image->pixel_array = pixel_array;
    image->bitmapFileHeader.bfSize = image->bitmapFileHeader.bfSize - image->bitmapInfoHeader.biSizeImage + h * w;
    image->bitmapInfoHeader.biHeight = h;
    image->bitmapInfoHeader.biWidth = w;
    image->bitmapInfoHeader.biSizeImage = w * h;

    return 0;
}

int rotateBMP(bmpImg *image) {

    pixel **pixel_array = malloc(image->bitmapInfoHeader.biWidth * sizeof(pixel*));
    if(pixel_array == NULL) {
        return 1;
    }

    for(int i = 0; i < image->bitmapInfoHeader.biWidth; i++) {
        pixel_array[i] = malloc(image->bitmapInfoHeader.biHeight * sizeof(pixel));
        if(pixel_array[i] == NULL) {
            return 1;
        }

        for(int j = 0; j < image->bitmapInfoHeader.biHeight; j++) {
            pixel_array[i][j] = image->pixel_array[j][image->bitmapInfoHeader.biWidth - i - 1];
        }
    }

    for(int i = 0; i < image->bitmapInfoHeader.biHeight; i++) {
        free(image->pixel_array[i]);
    }
    free(image->pixel_array);

    image->pixel_array = pixel_array;

    int32_t tmp = image->bitmapInfoHeader.biHeight;
    image->bitmapInfoHeader.biHeight = image->bitmapInfoHeader.biWidth;
    image->bitmapInfoHeader.biWidth = tmp;

    return 0;
}