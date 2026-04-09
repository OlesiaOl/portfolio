#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[]) {
    if (argc != 8) {
        printf("ошибка ввода.\n");
        return 1;
    }

    if (strcmp(argv[1], "crop-rotate") != 0) {
        printf("поддерживается только команда 'crop-rotate'.\n");
        return 1;
    }

    const char* inFile = argv[2];
    const char* outFile = argv[3];
    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);

    BMPHeader header;
    BITMAPINFOHEADER infoHeader;
    uint8_t* pixelData;

    if (load_bmp(inFile, &header, &infoHeader, &pixelData) != 0) {
        printf("Не удалось загрузить файл.\n");
        return 1;
    }

    BITMAPINFOHEADER croppedInfoHeader;
    uint8_t* croppedData = crop(pixelData, &infoHeader, x, y, w, h, &croppedInfoHeader);
    if (!croppedData) {
        free(pixelData);
        printf("ошибка: не удалось вырезать изображение.\n");
        return 1;
    }

    BITMAPINFOHEADER rotateInfoHeader;
    uint8_t* rotateData = rotate(croppedData, &croppedInfoHeader, &rotateInfoHeader);
    if (!rotateData) {
        free(pixelData);
        free(croppedData);
        printf("ошибка: не удалось повернуть изображение.\n");
        return 1;
    }

    if (save_bmp(outFile, &header, &rotateInfoHeader, rotateData) != 0) {
        free(pixelData);
        free(croppedData);
        free(rotateData);
        printf("не удалось сохранить файл.\n");
        return 1;
    }

    free(pixelData);
    free(croppedData);
    free(rotateData);
    return 0;
}
