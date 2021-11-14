import cv2
import numpy as np

from .display import DisplayWindow


class Process:
    def __init__(self, parent=None):
        self.img = cv2.imread("data/Sun.jpg")
        self.display = DisplayWindow(parent)

    def load_img(self):
        self.display.add_img_to_window(self.img)
        self.display.show()
        print("Height: ", self.img.shape[0])
        print("Width: ", self.img.shape[1])

    def color_seperation(self):
        for idx in range(3):
            channel = np.zeros(shape=self.img.shape, dtype=np.uint8)
            channel[:, :, idx] = self.img[:, :, idx]
            self.display.add_img_to_window(channel)
        self.display.show()

    def color_transformations(self):
        result = []
        img1 = np.zeros(shape=self.img.shape, dtype=np.uint8)
        img2 = np.zeros(shape=self.img.shape, dtype=np.uint8)
        for idx in range(3):
            img1[:, :, idx] = (
                self.img[:, :, 0] * 0.07
                + self.img[:, :, 1] * 0.72
                + self.img[:, :, 2] * 0.21
            )
            img2[:, :, idx] = (
                self.img[:, :, 0].astype(int)
                + self.img[:, :, 1].astype(int)
                + self.img[:, :, 2].astype(int)
            ) / 3
        result.extend([img1, img2])

        self.display.add_img_to_window(result[0])
        self.display.add_img_to_window(result[1])
        self.display.show()

    def blending(self):
        img1 = cv2.imread("data/Dog_Strong.jpg")
        img2 = cv2.imread("data/Dog_Weak.jpg")
        self.display.add_img_to_window_with_slider(img1, img2)
        self.display.show()
