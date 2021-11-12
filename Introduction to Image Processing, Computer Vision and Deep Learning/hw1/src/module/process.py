import cv2

from .display import DisplayWindow


class Process:
    def __init__(self, parent=None):
        self.img = cv2.imread("data/Sun.jpg")
        self.display = DisplayWindow(parent)

    def load_img(self):
        self.display.show_image(self.img)
        self.display.show()
