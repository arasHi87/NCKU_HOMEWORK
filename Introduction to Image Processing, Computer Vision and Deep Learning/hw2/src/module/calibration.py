import os

import cv2
import matplotlib.pyplot as plt
import numpy as np


class Calibration:
    def __init__(self):
        self.data = "data"
        self.objpts = []
        self.imgpts = []
        self.grayimg = []
        self.rvecs = ""
        self.tvecs = ""
        self.dist = ""

    def find_corner(self):
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
        objp = np.zeros((8 * 11, 3), np.float32)
        objp[:, :2] = np.mgrid[0:8, 0:11].T.reshape(-1, 2)
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
                cv2.imshow("image", cv2.resize(img, (800, 800)))
                cv2.waitKey(500)
        cv2.destroyAllWindows()

    def find_intrinsic(self):
        _, mtx, self.dist, self.rvecs, self.tvecs = cv2.calibrateCamera(
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

    def find_distortion(self):
        print("distortion matrix:\n", self.dist, "\n")

    def show_result(self):
        for i in range(1, 16):
            _, mtx, dist, _, _ = cv2.calibrateCamera(
                self.objpts, self.imgpts, self.grayimg[i - 1].shape[::-1], None, None
            )
            b_img = cv2.imread(
                os.path.join(self.data, "{}.bmp".format(i)), cv2.IMREAD_COLOR
            )
            h, w = b_img.shape[:2]
            newcameramtx, roi = cv2.getOptimalNewCameraMatrix(
                mtx, dist, (w, h), 0, (w, h)
            )
            a_img = cv2.undistort(b_img, mtx, dist, None, newcameramtx)
            x, y, w, h = roi
            a_img = a_img[y : y + h, x : x + w]
            b_img = cv2.resize(b_img, (800, 800))
            a_img = cv2.resize(a_img, (800, 800))
            cv2.imshow("image", np.concatenate((b_img, a_img), axis=1))
            cv2.waitKey(500)
        cv2.destroyAllWindows()
