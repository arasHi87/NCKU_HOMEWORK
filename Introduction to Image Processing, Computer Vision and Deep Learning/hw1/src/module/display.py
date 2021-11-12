from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import QLabel, QMainWindow, QVBoxLayout, QWidget


class DisplayWindow(QMainWindow):
    def __init__(self, parent=None):
        super(DisplayWindow, self).__init__(parent)

        self.widget = QWidget()
        self.image_frame = QLabel()
        self.layout = QVBoxLayout()
        self.layout.addWidget(self.image_frame)
        self.widget.setLayout(self.layout)
        self.setCentralWidget(self.widget)

    def show_image(self, cv_img):
        # convert opencv image
        q_image = QImage(
            cv_img.data, cv_img.shape[1], cv_img.shape[0], QImage.Format_RGB888
        ).rgbSwapped()
        self.image_frame.setPixmap(QPixmap.fromImage(q_image))
        self.setGeometry(0, 0, cv_img.shape[1], cv_img.shape[0])
        print("Height: ", cv_img.shape[0])
        print("Width: ", cv_img.shape[1])
