import cv2
import os

import numpy as np
import matplotlib.pyplot as plt


class Calibration:
    def __init__(self):
        self.data = "data"

    def find_corner(self):
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
        objp = np.zeros((8 * 11, 3), np.float32)
        objp[:, :2] = np.mgrid[0:8, 0:11].T.reshape(-1, 2)
        objpts = []
        imgpts = []
        grayimg = []

        plt.figure("2.1 Find Corners")
        plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0.01)
        for i in range(1, 16):
            img = cv2.imread(
                os.path.join(self.data, "{}.bmp".format(i)), cv2.IMREAD_COLOR
            )
            grayimg.append(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
            ret, corners = cv2.findChessboardCorners(grayimg[i - 1], (8, 11), None)

            if ret:
                objpts.append(objp)
                corners2 = cv2.cornerSubPix(
                    grayimg[i - 1], corners, (11, 11), (-1, -1), criteria
                )
                imgpts.append(corners2)
                cv2.drawChessboardCorners(img, (8, 11), corners2, ret)
                plt.subplot(3, 5, i)
                plt.axis("off")
                plt.imshow(img)
        plt.show()
