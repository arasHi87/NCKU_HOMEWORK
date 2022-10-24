#include "bmp.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <string>
#define NSmooth 1000
using namespace std;

BMPHEADER bmpHeader;
BMPINFO bmpInfo;
RGBTRIPLE** BMPSaveData = NULL;
RGBTRIPLE** BMPData = NULL;

int readBMP(const char* fileName);
int saveBMP(const char* fileName);
void swap(RGBTRIPLE* a, RGBTRIPLE* b);
RGBTRIPLE** alloc_memory(int Y, int X);

int main(int argc, char* argv[])
{
    const char* in_name = "input.bmp";
    const char* out_name = "output.bmp";
    double start_time = 0.0;
    int comm_size, my_rank;

    // MPI init
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // BMP init
    readBMP(in_name);
    BMPData = alloc_memory(bmpInfo.biHeight, bmpInfo.biWidth);
    RGBTRIPLE** lower_padding = alloc_memory(1, bmpInfo.biWidth);
    RGBTRIPLE** upper_padding = alloc_memory(1, bmpInfo.biWidth);

    // create new MPI type struct for sending RGBTRIPLE data
    int t_block[3] = { 1, 1, 1 };
    MPI_Aint t_displacements[3] = { 0, 1, 2 };
    MPI_Datatype t_types[3] = { MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR };
    MPI_Datatype MPI_RGBTRIPLE;
    MPI_Type_create_struct(3, t_block, t_displacements, t_types, &MPI_RGBTRIPLE);
    MPI_Type_commit(&MPI_RGBTRIPLE);

    // calculate each parameters for MPI_Scatterv
    int s_sum = 0; // use to count displacements
    int quotient = bmpInfo.biHeight / comm_size; // base number for sendcount
    int remainder = bmpInfo.biHeight % comm_size; // the remainder of row, will hand out to other process in sequence
    int s_sendcount[comm_size];
    int s_displacements[comm_size];
    int s_recvcount;
    for (int i = 0; i < comm_size; i++) {
        s_sendcount[i] = quotient * bmpInfo.biWidth;
        if (remainder)
            s_sendcount[i] += bmpInfo.biWidth, remainder--;
        s_displacements[i] = s_sum, s_sum += s_sendcount[i];
    }

    // record time
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    // scatter every piece of image to each process
    MPI_Scatterv(BMPSaveData[0], s_sendcount, s_displacements, MPI_RGBTRIPLE, BMPData[0], s_sendcount[0], MPI_RGBTRIPLE, 0, MPI_COMM_WORLD);

    // smooth
    for (int k = 0, idx, partner; k < NSmooth; k++) {
        if (k)
            swap(BMPSaveData, BMPData);

        // exchange padding
        idx = s_sendcount[my_rank] / bmpInfo.biWidth - 1;
        if (my_rank & 1) {
            partner = my_rank < comm_size - 1 ? my_rank + 1 : 0;
            // upper padding
            MPI_Send(BMPData[idx], bmpInfo.biWidth, MPI_RGBTRIPLE, partner, 0, MPI_COMM_WORLD);
            MPI_Recv(upper_padding[0], bmpInfo.biWidth, MPI_RGBTRIPLE, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // lower padding
            MPI_Send(BMPData[0], bmpInfo.biWidth, MPI_RGBTRIPLE, my_rank - 1, 0, MPI_COMM_WORLD);
            MPI_Recv(lower_padding[0], bmpInfo.biWidth, MPI_RGBTRIPLE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            partner = my_rank ? my_rank - 1 : comm_size - 1;
            // upper padding
            MPI_Recv(upper_padding[0], bmpInfo.biWidth, MPI_RGBTRIPLE, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(BMPData[idx], bmpInfo.biWidth, MPI_RGBTRIPLE, my_rank + 1, 0, MPI_COMM_WORLD);
            // lower padding
            MPI_Recv(lower_padding[0], bmpInfo.biWidth, MPI_RGBTRIPLE, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(BMPData[0], bmpInfo.biWidth, MPI_RGBTRIPLE, partner, 0, MPI_COMM_WORLD);
        }

        // smooth process
        RGBTRIPLE top, down, left, right, top_left, top_right, down_left, down_right;
        for (int i = 0; i < (s_sendcount[my_rank] / bmpInfo.biWidth); i++) {
            for (int j = 0, _top, _down, _left, _right; j < bmpInfo.biWidth; j++) {
                _top = i - 1, _down = i + 1;
                _left = j ? j - 1 : bmpInfo.biWidth - 1;
                _right = j < bmpInfo.biWidth - 1 ? j + 1 : 0;
                left = BMPData[i][_left], right = BMPData[i][_right];

                // get info for every direction's
                if (i == 0) {
                    top = upper_padding[0][j], down = BMPData[_down][j];
                    top_left = upper_padding[0][_left], top_right = upper_padding[0][_right];
                    down_left = BMPData[_down][_left], down_right = BMPData[_down][_right];
                } else if (i == (s_sendcount[my_rank] / bmpInfo.biWidth) - 1) {
                    top = BMPData[_top][j], down = lower_padding[0][j];
                    top_left = BMPData[_top][_left], top_right = BMPData[_top][_right];
                    down_left = lower_padding[0][_left], down_right = lower_padding[0][_right];
                } else {
                    top = BMPData[_top][j], down = BMPData[_down][j];
                    top_left = BMPData[_top][_left], top_right = BMPData[_top][_right];
                    down_left = BMPData[_down][_left], down_right = BMPData[_down][_right];
                }

                // weighted mean
                BMPSaveData[i][j].rgbRed = (double)(BMPData[i][j].rgbRed + top.rgbRed + down.rgbRed + left.rgbRed + right.rgbRed + top_left.rgbRed + top_right.rgbRed + down_left.rgbRed + down_right.rgbRed) / 9 + 0.5;
                BMPSaveData[i][j].rgbGreen = (double)(BMPData[i][j].rgbGreen + top.rgbGreen + down.rgbGreen + left.rgbGreen + right.rgbGreen + top_left.rgbGreen + top_right.rgbGreen + down_left.rgbGreen + down_right.rgbGreen) / 9 + 0.5;
                BMPSaveData[i][j].rgbBlue = (double)(BMPData[i][j].rgbBlue + top.rgbBlue + down.rgbBlue + left.rgbBlue + right.rgbBlue + top_left.rgbBlue + top_right.rgbBlue + down_left.rgbBlue + down_right.rgbBlue) / 9 + 0.5;
            }
        }
    }

    // gather smooth result from each process
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gatherv(BMPSaveData[0], s_sendcount[0], MPI_RGBTRIPLE, BMPData[0], s_sendcount, s_displacements, MPI_RGBTRIPLE, 0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        saveBMP(out_name);
        printf("Finished in time %f secs.\n", MPI_Wtime() - start_time);
    }

    MPI_Type_free(&MPI_RGBTRIPLE);
    MPI_Finalize();
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
    newFile.write((char*)BMPData[0], bmpInfo.biWidth * sizeof(RGBTRIPLE) * bmpInfo.biHeight);
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