import cv2

from .display import DisplayWindow


class Process:
    def __init__(self, parent=None):
        self.img = cv2.imread("data/Sun.jpg")
        self.display = DisplayWindow(parent)

    def load_img(self):
        self.display.load_img(self.img)
        self.display.show()

    def color_seperation(self):
        self.display.color_seperation(self.img)
        self.display.show()
