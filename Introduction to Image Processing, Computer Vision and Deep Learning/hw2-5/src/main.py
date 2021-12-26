import sys

from PyQt5.QtWidgets import QApplication

from module import gui

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = gui.Window()
    sys.exit(app.exec_())
