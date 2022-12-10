#include "bmp.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <string>
#define NSmooth 1000
using namespace std;
const int maxN = 2e5 + 9;
const int thread_amount = 8;

BMPINFO bmpInfo;
BMPHEADER bmpHeader;
RGBTRIPLE **BMPSaveData = NULL, **BMPData = NULL;

int tmp[2]; // use to check how many job finish now
struct timespec startwtime, endwtime;
const char* infileName = "input.bmp";
const char* outfileName = "output.bmp";
pthread_mutex_t job_mutex = PTHREAD_MUTEX_INITIALIZER;

int readBMP(const char* fileName);
int saveBMP(const char* fileName);
void swap(RGBTRIPLE* a, RGBTRIPLE* b);
RGBTRIPLE** alloc_memory(int Y, int X);

void* smoother(void* arg)
{
    // calculate parameter for this thread
    int L_pos, tid = (long)arg;
    int size = bmpInfo.biHeight / thread_amount;
    int remainder = bmpInfo.biHeight % thread_amount;
    L_pos = (tid < remainder ? L_pos = tid * (++size) : L_pos = size * tid + remainder);

    for (int count = 0; count < NSmooth; count++) {
        // init when all job done
        if (tmp[count & 1] == thread_amount - 1)
            swap(BMPSaveData, BMPData), tmp[(count + 1) & 1] = 0;

        // record job done
        pthread_mutex_lock(&job_mutex);
        tmp[count & 1]++;
        pthread_mutex_unlock(&job_mutex);
        while (tmp[count & 1] < thread_amount)
            ;

        for (int i = L_pos; i < L_pos + size; i++)
            for (int j = 0; j < bmpInfo.biWidth; j++) {
                int Top = i > 0 ? i - 1 : bmpInfo.biHeight - 1;
                int Down = i < bmpInfo.biHeight - 1 ? i + 1 : 0;
                int Left = j > 0 ? j - 1 : bmpInfo.biWidth - 1;
                int Right = j < bmpInfo.biWidth - 1 ? j + 1 : 0;
                BMPSaveData[i][j].rgbBlue = (double)(BMPData[i][j].rgbBlue + BMPData[Top][j].rgbBlue + BMPData[Top][Left].rgbBlue + BMPData[Top][Right].rgbBlue + BMPData[Down][j].rgbBlue + BMPData[Down][Left].rgbBlue + BMPData[Down][Right].rgbBlue + BMPData[i][Left].rgbBlue + BMPData[i][Right].rgbBlue) / 9 + 0.5;
                BMPSaveData[i][j].rgbGreen = (double)(BMPData[i][j].rgbGreen + BMPData[Top][j].rgbGreen + BMPData[Top][Left].rgbGreen + BMPData[Top][Right].rgbGreen + BMPData[Down][j].rgbGreen + BMPData[Down][Left].rgbGreen + BMPData[Down][Right].rgbGreen + BMPData[i][Left].rgbGreen + BMPData[i][Right].rgbGreen) / 9 + 0.5;
                BMPSaveData[i][j].rgbRed = (double)(BMPData[i][j].rgbRed + BMPData[Top][j].rgbRed + BMPData[Top][Left].rgbRed + BMPData[Top][Right].rgbRed + BMPData[Down][j].rgbRed + BMPData[Down][Left].rgbRed + BMPData[Down][Right].rgbRed + BMPData[i][Left].rgbRed + BMPData[i][Right].rgbRed) / 9 + 0.5;
            }
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    if (readBMP(infileName))
        cout << "Read file successfully!!" << endl;
    else
        cout << "Read file fails!!" << endl;
    BMPData = alloc_memory(bmpInfo.biHeight, bmpInfo.biWidth);

    pthread_t threads[maxN];
    for (int i = 0; i < thread_amount; i++)
        pthread_create(&threads[i], NULL, smoother, (void*)(uintptr_t)i);

    clock_gettime(CLOCK_MONOTONIC, &startwtime);
    for (int i = 0; i < thread_amount; i++)
        pthread_join(threads[i], NULL);

    if (saveBMP(outfileName))
        cout << "Save file successfully!!" << endl;
    else
        cout << "Save file fails!!" << endl;

    clock_gettime(CLOCK_MONOTONIC, &endwtime);
    cout << "It cost " << endwtime.tv_sec - startwtime.tv_sec << " seconds with " << thread_amount << " threads" << '\n';

    free(BMPData[0]);
    free(BMPSaveData[0]);
    free(BMPData);
    free(BMPSaveData);
    return 0;
}

int readBMP(const char* fileName)
{
    ifstream bmpFile(fileName, ios::in | ios::binary);
    if (!bmpFile) {
        cout << "It can't open file!!" << endl;
        return 0;
    }

    bmpFile.read((char*)&bmpHeader, sizeof(BMPHEADER));
    if (bmpHeader.bfType != 0x4d42) {
        cout << "This file is not .BMP!!" << endl;
        return 0;
    }

    bmpFile.read((char*)&bmpInfo, sizeof(BMPINFO));
    if (bmpInfo.biBitCount != 24) {
        cout << "The file is not 24 bits!!" << endl;
        return 0;
    }

    while (bmpInfo.biWidth % 4 != 0)
        bmpInfo.biWidth++;

    BMPSaveData = alloc_memory(bmpInfo.biHeight, bmpInfo.biWidth);
    bmpFile.read((char*)BMPSaveData[0], bmpInfo.biWidth * sizeof(RGBTRIPLE) * bmpInfo.biHeight);
    bmpFile.close();
    return 1;
}

int saveBMP(const char* fileName)
{
    if (bmpHeader.bfType != 0x4d42) {
        cout << "This file is not .BMP!!" << endl;
        return 0;
    }

    ofstream newFile(fileName, ios::out | ios::binary);
    if (!newFile) {
        cout << "The File can't create!!" << endl;
        return 0;
    }

    newFile.write((char*)&bmpHeader, sizeof(BMPHEADER));
    newFile.write((char*)&bmpInfo, sizeof(BMPINFO));
    newFile.write((char*)BMPSaveData[0], bmpInfo.biWidth * sizeof(RGBTRIPLE) * bmpInfo.biHeight);
    newFile.close();
    return 1;
}

RGBTRIPLE** alloc_memory(int Y, int X)
{
    RGBTRIPLE** temp = new RGBTRIPLE*[Y];
    RGBTRIPLE* temp2 = new RGBTRIPLE[Y * X];
    memset(temp, 0, sizeof(RGBTRIPLE) * Y);
    memset(temp2, 0, sizeof(RGBTRIPLE) * Y * X);
    for (int i = 0; i < Y; i++) {
        temp[i] = &temp2[i * X];
    }

    return temp;
}

void swap(RGBTRIPLE* a, RGBTRIPLE* b)
{
    RGBTRIPLE* temp;
    temp = a;
    a = b;
    b = temp;
}
