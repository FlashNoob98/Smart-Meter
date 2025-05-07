import sys
import os,fnmatch
from PyQt6.QtWidgets import QApplication, QMainWindow, QMessageBox
from PyQt6.uic import loadUi
from read_serial import Serial_reader
import pyqtgraph as pg



class MainUI(QMainWindow):
    def __init__(self):
        super(MainUI,self).__init__()
        loadUi("GUI/SerialReaderGUI.ui", self)
        #print(list_ACM)

        self.PortSelect.addItem("Select Port")
        self.RescanBTN.clicked.connect(self.scan_ports)
        self.scan_ports()
            #print("/dev/"+element)
        #self.PortSelect.editTextChanged.connect(self.updatePort)
        self.PortSelect.currentIndexChanged.connect(self.updatePort)
        #More functions, clicks, connections.. here
        self.AcquireBTN.clicked.connect(self.Acquire)

        # Graph init
        self.PlotWidget.setBackground('w')
        self.PlotWidget.setTitle("Serial Data")
        self.PlotWidget.setLabel('left', 'Y-Axis')
        self.PlotWidget.setLabel('bottom', 'X-Axis')
        self.PlotWidget.showGrid(x=True, y=True)

    def scan_ports(self):
        self.PortSelect.clear()
        self.PortSelect.addItem("Select Port")
        list_ACM = fnmatch.filter(os.listdir("/dev/"),"*ACM*")
        for element in list_ACM:
            self.PortSelect.addItem(element,"/dev/"+element)
        self.PortSelect.setCurrentIndex(len(list_ACM))

    def updatePort(self):
        #print(self.PortSelect.currentText())
        #print(self.PortSelect.currentData())
        pass

    def Acquire(self):
        if ui.PortSelect.currentText() == "Select Port":
            QMessageBox.warning(self," ","Warning: Device not selected")
            #print("Select a port")
        else:
            try:
                serial = Serial_reader(ui.PortSelect.currentData(),int(self.BaudLineEdit.text()),int(self.SampleCountLine.text()))
                #serial.read()
                self.plot(serial.read())
            except Exception as e:
                QMessageBox.warning(self,"Serial Error",str(e))

    def plot(self,data):
        #self.PlotWidget = pg.PlotWidget()
        self.PlotWidget.clear()
        self.PlotWidget.addLegend()
        self.PlotWidget.plot(data,pen='r',name="Test")
        self.PlotWidget.show()

if __name__ == "__main__":

    app = QApplication(sys.argv)
    ui = MainUI()
    ui.show()
    app.exec()
    

