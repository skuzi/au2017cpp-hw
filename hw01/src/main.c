#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 3)
        return -1;

    FILE *fin = fopen(argv[2], "rb");
    if(fin == NULL) {
        return 1;
    }

    bmpImg image;
    if(readBMP(fin, &image)) {
        fclose(fin);
        return 2;
    }
    fclose(fin);

    if(!strcmp(argv[1], "crop-rotate")) {
        if(argc != 8) {
            fclose(fin);
            return -1;
        }

        char *endx, *endy, *endh, *endw;

        int32_t x = strtol(argv[4], &endx, 10);
        int32_t y = strtol(argv[5], &endy, 10);
        int32_t w = strtol(argv[6], &endw, 10);
        int32_t h = strtol(argv[7], &endh, 10);

        if(*endx || *endy || *endh || *endw){
            return -1;
        }

        if(x < 0 || w < 0 || y < 0 || h < 0 || x + w > image.bitmapInfoHeader.biWidth || y + h > image.bitmapInfoHeader.biHeight || cropBMP(&image, x, y, w, h)) {
            return 2;
        }

        if(rotateBMP(&image)) {
            return 3;
        }

        FILE *fout = fopen(argv[3], "wb");
        if(fout == NULL) {
            return 1;
        }

        writeBMP(fout, &image);
        fclose(fout);
    }
    else if(!strcmp(argv[1], "insert")) {
        if(argc != 6) {
            return -1;
        }

        FILE *key = fopen(argv[4], "rt");
        FILE *msg = fopen(argv[5], "rt");
        if(key == NULL || msg == NULL) {
            return -2;
        }

        insertmsgBMP(&image, key, msg);
        fclose(key);
        fclose(msg);

        FILE *fout = fopen(argv[3], "wb");
        if(fout == NULL) {
            return 1;
        }

        writeBMP(fout, &image);
        fclose(fout);
    } else if(!strcmp(argv[1], "extract")) {
        if(argc != 5) {
            return -1;
        }

        FILE *key = fopen(argv[3], "rt");
        FILE *msg = fopen(argv[4], "wt");

        extractmsgBMP(&image, key, msg);

        fclose(key);
        fclose(msg);
    } else {
        return -1;
    }

    freeBMP(&image);
    return 0;
}