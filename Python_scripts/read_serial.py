class Serial_reader():
    def __init__(self,port,baud,count):
        import serial
        self.count = count
        self.port = port
        self.baud = baud
        self.pre = []
        self.post = []
        self.pre_total=[]
        self.ser = serial.Serial(port, baudrate=baud, timeout=3.0)
        self.counter = 0
        #while True:

    def read(self):
        for line in self.ser.read(self.count):
            if (chr(line) == (('\r'))):
                self.counter = self.counter+1
                pass
                #print("\n")
            else:
                if (self.counter > 0):
                    print(str(self.counter) + str(': ') + str(bin(line)) )
                    #print((line))
                    if ((self.counter%2)!=0):#Se dispari
                        self.post.append(bin(line))
                        self.counter = self.counter+1
                    else:
                        self.pre.append(bin(line))
                    

        if len(self.pre)>len(self.post):
            self.pre.pop()
        elif len(self.post)>len(self.pre):
            self.post.pop()

        for element in self.pre:
            self.pre_total.append(element + '00000000')

        somma = []
        for i in range(0,len(self.post)):
            somma.append(int(self.pre_total[i],2)+int(self.post[i],2))

        return somma

if __name__=="__main__":
    read = Serial_reader("COM3",9600,1000)
    print(read)

#for element in pre_total:
#    print(int(element,2))
    
#for element in post:
#    print(int(element,2))
