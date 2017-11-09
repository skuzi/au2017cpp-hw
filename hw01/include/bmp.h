#pragma once
#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER {
  uint32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  int16_t  biPlanes;
  int16_t  biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t  biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER {
  int16_t  bfType;
  uint32_t bfSize;
  int16_t  bfReserved1;
  int16_t  bfReserved2;
  uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct tPixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} pixel;

typedef struct bitmapImage {
    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPFILEHEADER bitmapFileHeader;
    pixel **pixel_array;
} bmpImg;

#pragma pack(pop)


int readBMP(FILE *f, bmpImg *image);

void writeBMP(FILE *f, bmpImg *image);

int cropBMP(bmpImg *image, int32_t x, int32_t y, int32_t w, int32_t h);

int rotateBMP(bmpImg *image);