#include "bitmap.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void hellerMachen(bitmap_pixel_hsv_t* p, int n, int heller);
int strLastIndexOf(char* str, char c);


int main(int argc, char* argv[]) {
    //parameter überprüfen und lesen
    if (argc <= 1) {
        printf("meh! mir fehlen gaaaanz wichtige Parameter: 1. Parameter muss der Dateiname des Bildes sein, 2. Parameter (optional) um wie viel das Bild verhellt/verdunkelt werden muss (zwischen -100 und 10000).\n");
        return 1;
    }
    int heller = 0;
    if (argc >= 3) heller = atoi(argv[2]);
    if (heller > 10000 || heller < -100) {
        printf("nenene dad passt net! Bitte Zahlen zwischen -100 und 10000 eingebe!\n");
        return 1;
    }
    
    // Bitmap laden
    bitmap_error_t err;
    int width, height;
    bitmap_pixel_hsv_t* pixels;
    err = bitmapReadPixels(
        argv[1],
        (bitmap_pixel_t**) &pixels,
        &width,
        &height,
        BITMAP_COLOR_SPACE_HSV
    );
    assert(err == BITMAP_ERROR_SUCCESS);
    
    // Heller/dunkler machen
    
    hellerMachen(pixels, width*height, heller+100);

    // Datei Name erzeugen
    
    char fileName[1000];
    strcpy(fileName,argv[1]);
    int indexOfPoint = strLastIndexOf(fileName,'.');// '.' suchen
    if (indexOfPoint != -1) fileName[indexOfPoint] = '\0'; // Endung entfernen, (falls Punkt gefunden)
    char zahl[16];// hier kommt die Zahl rein, um wie viel das Bild heller gemacht wird
    if (heller > 0) {
            strcat(fileName,"_heller_");
            sprintf(zahl, "%d", heller);
            strcat(fileName,zahl);
    } else if (heller == 0) {
            strcat(fileName,"_nix_gemacht");
    } else {
            strcat(fileName,"_dunkler_");
            sprintf(zahl, "%d", -heller);
            strcat(fileName,zahl);
    }
    strcat(fileName,".bmp");
    
    // SPEICHERN
    
    bitmap_parameters_t wrParameter = {
        .bottomUp = BITMAP_BOOL_TRUE,
        .widthPx = width,
        .heightPx = height,
        .colorDepth = BITMAP_COLOR_DEPTH_24,
        .compression = BITMAP_COMPRESSION_NONE,
        .dibHeaderFormat = BITMAP_DIB_HEADER_INFO,
        .colorSpace = BITMAP_COLOR_SPACE_HSV
    };
    err = bitmapWritePixels(
        fileName,
        BITMAP_BOOL_TRUE,
        (bitmap_parameters_t*) &wrParameter,
        (bitmap_pixel_t*) pixels
    );
    assert(err == BITMAP_ERROR_SUCCESS);

    // speicher freigeben!!!!!!!
    
    free(pixels);
    
    printf("Soooo jetze wurde das Bild gespeichert als %s <3 \n",fileName);
    
    return 0;
}

//heller: zwischen 0 und 10100
void hellerMachen(bitmap_pixel_hsv_t* p, int n, int heller) {
    for (int i = 0; i < n; i++) {
        bitmap_pixel_hsv_t* pix = &p[i];
        int newV = (int)((pix->v * heller) / 100);
        if (newV > 255) {
            pix->v = 255;
            pix->s = (pix->s * 255) / newV; //wenn zu hell, dann wird sättigung gesenkt (doppelt zu hell -> sättigung halbiert)
        } else {
            pix->v = newV;
        }
    } 
}

int strLastIndexOf(char* str, char c) {
    for (int i = strlen(str) - 1; i >= 0; i--) if (str[i] == c) return i;
    return -1;
}

