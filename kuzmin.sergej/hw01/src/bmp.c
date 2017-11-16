#include "bmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int32_t calcPaddBMP(int32_t width) {
    return width % 4;
}

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
    if(image->pixel_array == NULL) {
        return 1;
    }

    int32_t padd = calcPaddBMP(bitmapInfoHeader->biWidth);

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

    int32_t padd = calcPaddBMP(bitmapInfoHeader->biWidth);

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

        memcpy(pixel_array[i], image->pixel_array[image->bitmapInfoHeader.biHeight - y - i - 1] + x, w * sizeof(pixel));
    }

    freeBMP(image);

    image->pixel_array = pixel_array;
    image->bitmapFileHeader.bfSize = image->bitmapFileHeader.bfSize - image->bitmapInfoHeader.biSizeImage + h * (w + calcPaddBMP(w));
    image->bitmapInfoHeader.biHeight = h;
    image->bitmapInfoHeader.biWidth = w;
    image->bitmapInfoHeader.biSizeImage = h * (w + calcPaddBMP(w));

    return 0;
}

int rotateBMP(bmpImg *image) {
    int32_t w = image->bitmapInfoHeader.biWidth;
    int32_t h = image->bitmapInfoHeader.biHeight;

    pixel **pixel_array = malloc(w * sizeof(pixel*));
    if(pixel_array == NULL) {
        return 1;
    }

    for(int i = 0; i < w; i++) {
        pixel_array[i] = malloc(h * sizeof(pixel));
        if(pixel_array[i] == NULL) {
            return 1;
        }

        for(int j = 0; j < h; j++) {
            pixel_array[i][j] = image->pixel_array[h - j - 1][w - i - 1];
        }
    }

    freeBMP(image);

    image->pixel_array = pixel_array;

    image->bitmapInfoHeader.biHeight = w;
    image->bitmapInfoHeader.biWidth = h;

    return 0;
}

void freeBMP(bmpImg *image) {
    for(int i = 0; i < image->bitmapInfoHeader.biHeight; i++) {
        free(image->pixel_array[i]);
    }
    free(image->pixel_array);
}

void set_last_bit(uint8_t *value, int bit) {
    *value = (*value - ((*value) & 1)) | bit;
}

void insertmsgBMP(bmpImg *image, FILE *key, FILE *msg) {
    char letter = 0;
    char comp = 0;
    int32_t x = 0;
    int32_t y = 0;
    int to_encode = 0;

    int32_t h = image->bitmapInfoHeader.biHeight;

    while(1) {
        if(fscanf(msg, "%c", &letter) != 1) {
            break;
        }
        if(letter == ' ') {
            to_encode = 26;
        }
        else if(letter == '.') {
            to_encode = 27;
        }
        else if(letter == ',') {
            to_encode = 28;
        }
        else {
            to_encode = letter - 'A';
        }

        for(int i = 0; i < 5; i++) {
            if(fscanf(key, "%d %d %c", &x, &y, &comp) != 3) {
                break;
            }
            
            if(comp == 'B') {
                set_last_bit(&(image->pixel_array[h - y - 1][x].blue), to_encode & 1);
            }
            else if(comp == 'R') {
                set_last_bit(&(image->pixel_array[h - y - 1][x].red), to_encode & 1);
            }
            else if(comp == 'G') {
                set_last_bit(&(image->pixel_array[h - y - 1][x].green), to_encode & 1);
            }
            to_encode >>= 1;
        }
    }//while(1)
}

void extractmsgBMP(bmpImg *image, FILE *key, FILE *msg) {
    char comp = 0;
    int32_t x = 0;
    int32_t y = 0;

    int32_t h = image->bitmapInfoHeader.biHeight;

    int flag = 1;
    while(flag) {
        int letter = 0;
        for(int i = 0; i < 5; i++) {
            if(fscanf(key, "%d %d %c", &x, &y, &comp) != 3) {
                flag = 0;
                break;
            }
            
            if(comp == 'B') {
                letter |= ((image->pixel_array[h - y - 1][x].blue & 1) << i);
            }
            else if(comp == 'R') {
                letter |= ((image->pixel_array[h - y - 1][x].red & 1) << i);
            }
            else if(comp == 'G') {
                letter |= ((image->pixel_array[h - y - 1][x].green & 1) << i);
            }
        }

        if(flag) {
            if(letter < 26) {
                letter += 'A';
            }
            else if(letter == 26) {
                letter = ' ';
            }
            else if(letter == 27) {
                letter = '.';
            }
            else if(letter == 28) {
                letter = ',';
            }
            
            fprintf(msg, "%c", letter);
        }
    }//while(flag)
}