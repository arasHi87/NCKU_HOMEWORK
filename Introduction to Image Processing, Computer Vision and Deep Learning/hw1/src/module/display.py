import numpy as np
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QLabel, QMainWindow, QVBoxLayout, QWidget


class DisplayWindow(QMainWindow):
    def __init__(self, parent=None):
        super(DisplayWindow, self).__init__(parent)

        self.widget = QWidget()
        self.layout = QVBoxLayout()
        self.widget.setLayout(self.layout)
        self.setCentralWidget(self.widget)

    def add_img_to_window(self, cv_img):
        img_frame = QLabel()
        self.layout.addWidget(img_frame)
        q_image = QImage(
            cv_img.data, cv_img.shape[1], cv_img.shape[0], QImage.Format_RGB888
        ).rgbSwapped()
        img_frame.setPixmap(QPixmap.fromImage(q_image))
        self.setGeometry(0, 0, cv_img.shape[1], cv_img.shape[0])

    def load_img(self, cv_img):
        self.add_img_to_window(cv_img)
        print("Height: ", cv_img.shape[0])
        print("Width: ", cv_img.shape[1])

    def color_seperation(self, cv_img):
        for channel_index in range(3):
            channel = np.zeros(shape=cv_img.shape, dtype=np.uint8)
            channel[:, :, channel_index] = cv_img[:, :, channel_index]
            self.add_img_to_window(channel)
        self.setGeometry(0, 0, channel.shape[1], channel.shape[0] * 3)
