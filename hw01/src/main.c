#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t parseInt(const char* str) {
    int32_t result = 0;
    for(int i = 0; str[i]; i++){
        if(str[i] < '0' || str[i] > '9'){
            return -1;
        }
        result = result * 10 + str[i] - '0';
    }
    return result;
}

int main(int argc, char* argv[]){
    if(argc < 3)
        return -1;

    char* input = argv[2];
    FILE *fin = fopen(input, "rb");
    if(fin == NULL) {
        return 1;
    }
    
    bmpImg image;

    if(!strcmp(argv[1], "crop-rotate")) {
        if(argc != 8) {
            fclose(fin);
            return -1;
        }
        
        char* output = argv[3];
        int32_t x = parseInt(argv[4]);
        int32_t y = parseInt(argv[5]);
        int32_t w = parseInt(argv[6]);
        int32_t h = parseInt(argv[7]);

        FILE *fout = fopen(output, "wb");
        if(fout == NULL) {
            fclose(fin);
            return 1;
        }

        if(readBMP(fin, &image)) {
            fclose(fin);
            fclose(fout);
            return 2;
        }
        
        if(x < 0 || w < 0 || y < 0 || h < 0 || x + w > image.bitmapInfoHeader.biWidth || y + h > image.bitmapInfoHeader.biHeight || cropBMP(&image, x, y, w, h)) {
            fclose(fin);
            fclose(fout);
            return 2;
        }
 
        if(rotateBMP(&image)) {
            fclose(fin);
            fclose(fout);
            return 3;
        }

        writeBMP(fout, &image);
           fclose(fout);
    }
    else if(!strcmp(argv[1], "insert")) {
        //TODO
    } else if(!strcmp(argv[1], "extract")) {
        //TODO
    } else {
        fclose(fin);
        return -1;
    }

    for(int i = 0; i < image.bitmapInfoHeader.biHeight; i++) {
        free(image.pixel_array[i]);
    }
    free(image.pixel_array);

    fclose(fin);
    return 0;
}