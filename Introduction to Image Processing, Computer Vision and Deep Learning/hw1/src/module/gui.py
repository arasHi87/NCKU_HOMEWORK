from PyQt5.QtWidgets import QMainWindow, QPushButton


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
                btn.resize(200, 50)
                btn.move(self.locate_row(i), self.locate_col(j))
