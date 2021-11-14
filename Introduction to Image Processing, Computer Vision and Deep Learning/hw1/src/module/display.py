import cv2
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QLabel, QMainWindow, QSlider, QVBoxLayout, QWidget


class DisplayWindow(QMainWindow):
    def __init__(self, parent=None):
        super(DisplayWindow, self).__init__(parent)

        self.public_frame = QLabel()
        self.widget = QWidget()
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.public_frame)
        self.widget.setLayout(self.layout)
        self.setCentralWidget(self.widget)

    def add_img_to_window(self, cv_img):
        # add new label to insert image
        img_frame = QLabel()
        self.layout.addWidget(img_frame)

        # init image
        q_image = QImage(
            cv_img.data, cv_img.shape[1], cv_img.shape[0], QImage.Format_RGB888
        ).rgbSwapped()
        img_frame.setPixmap(QPixmap.fromImage(q_image))

    def add_img_to_public(self, cv_img):
        # init image
        q_image = QImage(
            cv_img.data, cv_img.shape[1], cv_img.shape[0], QImage.Format_RGB888
        ).rgbSwapped()
        self.public_frame.setPixmap(QPixmap.fromImage(q_image))

    def add_img_to_window_with_slider(self, cv_img1, cv_img2):
        self.slider = QSlider(Qt.Horizontal)
        self.slider.setRange(0, 255)
        self.slider.valueChanged.connect(
            lambda: self.slider_value_change(cv_img1, cv_img2)
        )
        self.layout.addWidget(self.slider)
        self.slider_value_change(cv_img1, cv_img2)

    def slider_value_change(self, cv_img1, cv_img2):
        value = self.slider.value() / 255
        result = cv2.addWeighted(cv_img1, 1 - value, cv_img2, value, 0)
        cv2.imshow("dsa", result)
        self.add_img_to_public(result)
