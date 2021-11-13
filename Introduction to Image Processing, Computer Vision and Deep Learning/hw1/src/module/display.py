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
        # add new label to insert image
        img_frame = QLabel()
        self.layout.addWidget(img_frame)

        # init image
        q_image = QImage(
            cv_img.data, cv_img.shape[1], cv_img.shape[0], QImage.Format_RGB888
        ).rgbSwapped()
        img_frame.setPixmap(QPixmap.fromImage(q_image))
