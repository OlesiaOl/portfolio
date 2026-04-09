#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bmp.h"

int load_bmp(const char* filename, BMPHeader* header, BITMAPINFOHEADER* infoHeader, uint8_t** pixelData) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("ошибка при открытии файла %s \n", filename);
        return 1;
    }

    if (fread(header, sizeof(BMPHeader), 1, file) != 1) {
        printf("ошибка чтения заголовка BMPHeader\n");
        fclose(file);
        return 1;
    }

    if (header->bfType != 0x4D42) {
        printf("неверный формат файла (не BMP)\n");
        fclose(file);
        return 1;
    }

    if (fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, file) != 1) {
        printf("ошибка чтения заголовка BITMAPINFOHEADER\n");
        fclose(file);
        return 1;
    }

    if (infoHeader->biBitCount != 24) {
        printf("поддерживаются только 24-битные BMP файлы\n");
        fclose(file);
        return 1;
    }

    int rowSize = ((infoHeader->biWidth * 3 + 3) & ~3);
    int imageSize = rowSize * abs(infoHeader->biHeight);
    int padding = rowSize - (infoHeader->biWidth * 3);

    *pixelData = malloc(imageSize);
    if (!*pixelData) {
        printf("ошибка выделения памяти\n");
        fclose(file);
        return 1;
    }

    for (int y = 0; y < abs(infoHeader->biHeight); y++) {

        if (fread(*pixelData + y * rowSize, 1, infoHeader->biWidth * 3, file) != (size_t)(infoHeader->biWidth * 3)) {
            printf("Ошибка чтения данных изображения\n");
            free(*pixelData);
            fclose(file);
            return 1;
        }

        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return 0;
}

int save_bmp(const char* filename, const BMPHeader* header, const BITMAPINFOHEADER* infoHeader, const uint8_t* pixelData) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("ошибка при открытии файла для записи.\n");
        return 1;
    }

    int rowSize = ((infoHeader->biWidth * 3 + 3) & ~3);
    int padding = rowSize - (infoHeader->biWidth * 3);
    uint8_t zero[3] = {0};

    BITMAPINFOHEADER newInfoHeader = *infoHeader;
    newInfoHeader.biSizeImage = rowSize * abs(infoHeader->biHeight);
    BMPHeader newHeader = *header;
    newHeader.bfSize = newHeader.bfOffset + newInfoHeader.biSizeImage;


    if (fwrite(&newHeader, sizeof(BMPHeader), 1, file) != 1) {
        printf("Ошибка записи BMPHeader.\n");
        fclose(file);
        return 1;
    }

    if (fwrite(&newInfoHeader, sizeof(BITMAPINFOHEADER), 1, file) != 1) {
        printf("Ошибка записи BITMAPINFOHEADER.\n");
        fclose(file);
        return 1;
    }

    for (int y = 0; y < abs(infoHeader->biHeight); y++) {

        if (fwrite(pixelData + y * rowSize, 1, infoHeader->biWidth * 3, file) != (size_t)(infoHeader->biWidth * 3)) {
            printf("ошибка записи данных пикселей.\n");
            fclose(file);
            return 1;
        }

        if (padding > 0) {
            if (fwrite(zero, 1, padding, file) != (size_t)padding) {
                printf("ошибка записи padding.\n");
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

uint8_t* crop(const uint8_t* data, const BITMAPINFOHEADER* infoHeader, int x, int y, int w, int h, BITMAPINFOHEADER* croppedInfoHeader) {

    if (data == NULL || infoHeader == NULL) {
        return NULL;
    }

    int originWidth = infoHeader->biWidth;
    int originHeight = infoHeader->biHeight;

    if (x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > originWidth || y + h > originHeight) {
        return NULL;
    }

    int size = 3;
    int originRowSize = (originWidth * size + 3) & ~3;
    int newRowSize = (w * size + 3) & ~3;

    size_t cropSize = (size_t)newRowSize * h;
    uint8_t* newData = (uint8_t*)malloc(cropSize);

    if (newData == NULL) {
        return NULL;
    }


    memcpy(croppedInfoHeader, infoHeader, sizeof(BITMAPINFOHEADER));
    croppedInfoHeader->biWidth = w;
    croppedInfoHeader->biHeight = h;
    croppedInfoHeader->biSizeImage = newRowSize * h;

    int correctedY = originHeight - y - h;


    for (int i = 0; i < h; i++) {

        const uint8_t* sourceRow = data + (correctedY + i) * originRowSize + x * 3;
        uint8_t* croppedRow = newData + i * newRowSize;

        for (int j = 0; j < w; j++) {
            memcpy(croppedRow + j * 3, sourceRow + j * 3, 3);
        }

        memset(croppedRow + w * 3, 0, newRowSize - w * 3);
    }

    return newData;
}

uint8_t* rotate(const uint8_t* source, const BITMAPINFOHEADER* croppedInfoHeader, BITMAPINFOHEADER* rotateInfoHeader) {
    int newWidth = croppedInfoHeader->biHeight;
    int newHeight = croppedInfoHeader->biWidth;

    int sourceRowSize = ((croppedInfoHeader->biWidth * 3 + 3) & ~3);
    int rotateRowSize = ((newWidth * 3 + 3) & ~3);

    uint8_t* rotateData = malloc(rotateRowSize * newHeight);
    if (!rotateData) {
        printf("Ошибка выделения памяти для поворота изображения.\n");
        return NULL;
    }

    for (int y = 0; y < croppedInfoHeader->biHeight; ++y) {
        for (int x = 0; x < croppedInfoHeader->biWidth; ++x) {
            const uint8_t* srcPixel = source + y * sourceRowSize + x * 3;

            int newX = y;
            int newY = newHeight - x - 1;
            uint8_t* dstPixel = rotateData + newY * rotateRowSize + newX * 3;

            memcpy(dstPixel, srcPixel, 3);
        }
    }

    memcpy(rotateInfoHeader, croppedInfoHeader, sizeof(BITMAPINFOHEADER));
    rotateInfoHeader->biWidth = newWidth;
    rotateInfoHeader->biHeight = newHeight;
    rotateInfoHeader->biSizeImage = rotateRowSize * newHeight;

    return rotateData;
}
