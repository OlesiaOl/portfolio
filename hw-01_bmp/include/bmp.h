#ifndef BMP_H
#define BMP_H

#pragma pack(push, 1)
typedef struct BMPHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReversed1;
    uint16_t bfReversed2;
    uint32_t bfOffset;
} BMPHeader;

typedef struct tagBITMAPINFOHEADER {
  uint32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  uint16_t  biPlanes;
  uint16_t  biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t  biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)
int load_bmp(const char* filename, BMPHeader* header, BITMAPINFOHEADER* infoHeader, uint8_t** pixelData);
int save_bmp(const char* filename, const BMPHeader* header, const BITMAPINFOHEADER* infoHeader, const uint8_t* pixelData);
uint8_t* crop(const uint8_t* source, const BITMAPINFOHEADER* infoHeader, int x, int y, int w, int h, BITMAPINFOHEADER* croppedInfoHeader);
uint8_t* rotate(const uint8_t* source, const BITMAPINFOHEADER* croppedInfoHeader, BITMAPINFOHEADER* rotateInfoHeader);

#endif //BMP_H
