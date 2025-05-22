import sys
import os,fnmatch,platform
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
        if platform.system() == "Linux":
            list_ACM = fnmatch.filter(os.listdir("/dev/"),"*ACM*")
            for element in list_ACM:
                self.PortSelect.addItem(element,"/dev/"+element)
            self.PortSelect.setCurrentIndex(len(list_ACM))
        elif platform.system() == "Windows":
            import serial.tools.list_ports
            ports = serial.tools.list_ports.comports()
            for port, desc, hwid in sorted(ports):
                #print("{}: {} [{}]".format(port, desc, hwid))
                self.PortSelect.addItem(port,port)
            self.PortSelect.setCurrentIndex(len(ports))
            #QMessageBox.warning(self," ","Warning: Windows not supported") Windows is now SupPORTed!
        elif platform.system() == "Darwin":
            QMessageBox.warning(self," ","Warning: MacOS not supported")
        else:
            QMessageBox.warning(self," ","Warning: Unknown OS")

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
                serial.read()
                self.plot(serial.sommaV, serial.sommaI)
            except Exception as e:
                QMessageBox.warning(self,"Serial Error",str(e))

  
    def writeDataToFile(self,data):
        OUT_FILE= 'results.txt'
        f = open(OUT_FILE, 'a')
        f.write(f"{data}\n")
        f.close()
        print("data written")


    def plot(self,voltage,current):
        #self.PlotWidget = pg.PlotWidget()
        self.PlotWidget.clear()
        self.PlotWidget.addLegend()
        self.PlotWidget.plot(voltage,pen='r',name="Voltage")
        self.writeDataToFile(voltage)
        self.PlotWidget.plot(current,pen='b',name="Current")
        self.PlotWidget.show()

if __name__ == "__main__":

    app = QApplication(sys.argv)
    ui = MainUI()
    ui.show()
    app.exec()
    

