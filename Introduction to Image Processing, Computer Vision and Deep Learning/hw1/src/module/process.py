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
