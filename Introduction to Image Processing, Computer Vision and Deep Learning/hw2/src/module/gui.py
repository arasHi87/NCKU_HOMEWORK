from functools import partial
from .calibration import Calibration

from PyQt5.QtWidgets import (
    QComboBox,
    QGroupBox,
    QHBoxLayout,
    QPushButton,
    QVBoxLayout,
    QWidget,
)


class Window(QWidget):
    def __init__(self):
        super().__init__()
        self.calibration = Calibration()

        # layout setting
        height = 400
        width = 300
        self.combobox = QComboBox()
        for i in range(1, 16):
            self.combobox.insertItem(i, "{}.bmp".format(i))

        # window setting
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)
        self.setWindowTitle("HW2")
        self.setGeometry(100, 100, width, height)
        self.init_btn()
        self.show()

    def init_btn(self):
        msg = [
            "2.1 Find Corner",
            "2.2 Find Intrinsic",
            "2.3 Find extrinsic",
            "2.4 Find Distortion",
            "2.5 Show Result",
        ]

        # main group box
        v_layout = QVBoxLayout()
        g_box = QGroupBox("2. Calibration")

        # sub group box
        sub_v_layout = QVBoxLayout()
        sub_g_box = QGroupBox("2.3 Find Extrinsic")

        for i in range(len(msg)):
            btn = QPushButton(msg[i], self)
            btn.clicked.connect(partial(self._executor, i))
            if i == 2:
                sub_g_box.setLayout(sub_v_layout)
                sub_v_layout.addWidget(self.combobox)
                sub_v_layout.addWidget(btn)
                v_layout.addWidget(sub_g_box)
            else:
                g_box.setLayout(v_layout)
                v_layout.addWidget(btn)
        self.layout.addWidget(g_box)

    def _executor(self, i):
        func = [
            getattr(self.calibration, "find_corner"),
            getattr(self.calibration, "find_intrinsic"),
        ]

        if i < len(func):
            func[i]()
