import cv2
import os

import numpy as np
import matplotlib.pyplot as plt


class Calibration:
    def __init__(self):
        self.data = "data"
        self.objpts = []
        self.imgpts = []
        self.grayimg = []
        self.rvecs = ""
        self.tvecs = ""

    def find_corner(self):
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
        objp = np.zeros((8 * 11, 3), np.float32)
        objp[:, :2] = np.mgrid[0:8, 0:11].T.reshape(-1, 2)

        plt.figure("2.1 Find Corners")
        plt.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0.01)
        for i in range(1, 16):
            img = cv2.imread(
                os.path.join(self.data, "{}.bmp".format(i)), cv2.IMREAD_COLOR
            )
            self.grayimg.append(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
            ret, corners = cv2.findChessboardCorners(self.grayimg[i - 1], (8, 11), None)

            if ret:
                self.objpts.append(objp)
                corners2 = cv2.cornerSubPix(
                    self.grayimg[i - 1], corners, (11, 11), (-1, -1), criteria
                )
                self.imgpts.append(corners2)
                cv2.drawChessboardCorners(img, (8, 11), corners2, ret)
                plt.subplot(3, 5, i)
                plt.axis("off")
                plt.imshow(img)
        plt.show()

    def find_intrinsic(self):
        _, mtx, _, self.rvecs, self.tvecs = cv2.calibrateCamera(
            self.objpts, self.imgpts, self.grayimg[0].shape[::-1], None, None
        )
        print("intrinsic matrix:\n", mtx, "\n")

    def find_extrinsic(self, index):
        dst, _ = cv2.Rodrigues(self.rvecs[index])
        extrinsic_mtx = np.zeros((dst.shape[0], dst.shape[1] + 1))
        extrinsic_mtx[:, :-1] = dst
        for i in range(3):
            extrinsic_mtx[i][3] = self.tvecs[index][i][0]
        print(str(index + 1) + ".bmp extrinsic matrix:\n", extrinsic_mtx, "\n")
