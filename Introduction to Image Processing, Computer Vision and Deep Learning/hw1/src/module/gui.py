from functools import partial

from PyQt5.QtWidgets import QMainWindow, QPushButton

from .process import Process


class Window(QMainWindow):
    def __init__(self):
        super().__init__()

        # layout setting
        self.padding = 20
        self.row_amount = 4
        self.col_amount = 4
        self._height = 600
        self._width = 900

        # window setting
        self.setWindowTitle("HW1")
        self.setGeometry(0, 0, self._width, self._height)
        self.init_zone()
        self.show()

    def init_zone(self):
        self._init_btn()

    def locate_col(self, col):
        c_spacing = (
            (self._height - self.padding * 2) / self.col_amount
        ) * col + self.padding
        return c_spacing

    def locate_row(self, row):
        r_spacing = (
            (self._width - self.padding * 2) / self.row_amount
        ) * row + self.padding
        return r_spacing

    def _init_btn(self):
        msg = [
            ["Load Image", "Color seoeration", "Color Transformations", "Blending"],
            ["Gaussian Blur", "Bilateral Filter", "Median Filter"],
            ["Gaussian Blur", "Sobel X", "Sobel Y", "Magnitude"],
            ["Resize", "Translation", "Rotation, Scaling", "Shearing"],
        ]

        for i in range(len(msg)):
            for j in range(len(msg[i])):
                btn = QPushButton(msg[i][j], self)
                btn.clicked.connect(partial(self._executor, i, j))
                btn.resize(200, 50)
                btn.move(self.locate_row(i), self.locate_col(j))

    def _executor(self, i, j):
        _process = Process(self)
        func = [
            [
                getattr(_process, "load_img"),
                getattr(_process, "color_seperation"),
                getattr(_process, "color_transformations"),
                getattr(_process, "blending"),
            ]
        ]

        if i < len(func) and j < len(func[i]):
            func[i][j]()
