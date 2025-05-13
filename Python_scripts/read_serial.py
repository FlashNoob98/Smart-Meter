class Serial_reader():
    def __init__(self,port,baud,count):
        import serial
        self.count = count
        self.port = port
        self.baud = baud
        self.pre = []
        self.post = []
        self.pre_total=[]
        self.ser = serial.Serial(port, baudrate=baud-1, timeout=3.0)
        self.counter = 0
        #while True:

    def read(self):
        line = self.ser.read(self.count*4)
        #print(line)
        for index in range(len(line)-4):
            print(line[index])
            print(line[index+1])
            print(line[index+2])
            print(line[index+3])
            if (line[index] == 255):
                #print("255")
                if (line[index+1] == 255):
                    if(line[index+2]==65): #65=A
                        #print("A")
                        #print(str(self.counter) + str(': ') + str(bin(line[index])) )
                    #print((line))
                        self.post.append(bin(line[index+3]))                 
                        self.pre.append(bin(line[index+4]))
                        index = index+4
                        self.counter = self.counter+1
                    pass
                #print("\n")

        #print(line)
             

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
