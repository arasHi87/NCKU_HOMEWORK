from functools import partial

from PyQt5.QtWidgets import (
    QGroupBox,
    QHBoxLayout,
    QPushButton,
    QSpinBox,
    QVBoxLayout,
    QWidget,
)

from .train import Train


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.train = Train()

        # layout setting
        height = 400
        width = 300
        self.spinbox = QSpinBox()
        self.spinbox.setRange(1, 2147483647)

        # window setting
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)
        self.setWindowTitle("HW2")
        self.setGeometry(100, 100, width, height)
        self.init_btn()
        self.show()

    def init_btn(self):
        msg = [
            "1. Show Model Structure",
            "2. Show TensorBoard",
            "3. Test",
            "4. Data Augmantation",
        ]

        # main group box
        v_layout = QVBoxLayout()
        g_box = QGroupBox("5. Classification")

        for i in range(len(msg)):
            btn = QPushButton(msg[i], self)
            btn.clicked.connect(partial(self._executor, i))
            g_box.setLayout(v_layout)
            v_layout.addWidget(btn)
            if i == 2:
                v_layout.addWidget(self.spinbox)

        self.layout.addWidget(g_box)

    def _executor(self, i):
        func = [
            getattr(self.train, "show_model"),
            getattr(self.train, "show_board"),
            getattr(self.train, "show_test"),
            getattr(self.train, "show_augmantation"),
        ]

        if i < len(func):
            if i == 2:
                func[i](self.spinbox.value())
            else:
                func[i]()
