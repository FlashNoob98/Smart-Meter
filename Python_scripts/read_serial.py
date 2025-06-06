class Serial_reader():
    def __init__(self,port,baud,count):
        import serial
        self.count = count
        self.port = port
        self.baud = baud
        self.pre = []
        self.post = []
        self.pre_total=[]
        self.ser = serial.Serial(port, baudrate=baud, timeout=10.0)
        self.counter = 0
        self.preI = []
        self.postI = []
        self.pre_totalI=[]
        self.sommaV=[]
        self.sommaI=[]
        #while True:

    def rearrange(self,pre,post,pre_total,somma):
       # if len(pre)>len(post):
       #     pre.pop()
       # elif len(post)>len(pre):
       #     post.pop()
        for element in pre:
            #print(element)
            pre_total.append(element + "00000000")
        for i in range(0,len(post)):
            somma.append(int(pre_total[i],base=2)+int(post[i],base=2))
            #print(pre_total[i])
            #print(int(pre_total[i],base=2))
            #print(post[i])
            #print(int(post[i],base=2))
            #print("somma: " + str(somma[i]))

    def rearrange_single(self,pre,post):
       # if len(pre)>len(post):
       #     pre.pop()
       # elif len(post)>len(pre):
       #     post.pop()
            #print(element)
        pre = (bin(pre) + "00000000")
        return  (int(pre,base=2)+int(bin(post),base=2))
            #print(pre_total[i])
            #print(int(pre_total[i],base=2))
            #print(post[i])
            #print(int(post[i],base=2))
            #print("somma: " + str(somma[i]))


    def read(self):
        self.ser.write('A'.encode('utf-8')) #A
        line = self.ser.read(self.count*8+24)
        #print(line)
        for index in range(len(line)-3):
            #print(line[index])
            if (line[index] == 255):
                #print("255")
                    if(line[index+1]==65): #65=A
                        self.post.append(bin(round(line[index+2])))                 
                        self.pre.append(bin(round(line[index+3])))
                        self.counter = self.counter+1
                    elif(line[index+1]==66): #66=B
                        if self.counter==0: #Previeni offset due misure
                            continue
                        self.postI.append(bin(round(line[index+2])))                 
                        self.preI.append(bin(round(line[index+3])))   
                    elif(line[index+1]==67): #67=C RMS V
                        #print("C")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.RMS_V = self.rearrange_single(line[index+3],line[index+2])
                        print("V_rms = " + str(self.RMS_V) + " V")     
                    elif(line[index+1]==68): #68=D RMS I
                        #print("D")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.RMS_I = self.rearrange_single(line[index+3],line[index+2])
                        print("I_rms = "+ str(self.RMS_I) + " A")  
                    elif(line[index+1]==69): #69=E PAttiva
                        #print("D")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.P_A = self.rearrange_single(line[index+3],line[index+2])
                        print("P_a = "+ str(self.P_A) + " W")  
                    elif(line[index+1]==70): #70=F Q p reattiva
                        #print("D")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.Q = self.rearrange_single(line[index+3],line[index+2])
                        print("Q = "+ str(self.Q) + " VAr") 
                    elif(line[index+1]==71): #71=G S p apparente
                        #print("D")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.S = self.rearrange_single(line[index+3],line[index+2])
                        print("S = "+ str(self.S) + " VA") 
                    elif(line[index+1]==72): #72=H Energia
                        #print("D")   
                        #print(line[index+1])  
                        #print(line[index+2]) #post
                        #print(line[index+3]) #pre
                        self.Energy = self.rearrange_single(line[index+3],line[index+2])/1000
                        print("E = "+ str(self.Energy) + " kWh") 
                
        #print(line)

        self.rearrange(self.pre,self.post,self.pre_total,self.sommaV)
        self.rearrange(self.preI,self.postI,self.pre_totalI,self.sommaI)


        return
    


if __name__=="__main__":
    read = Serial_reader("COM3",9600,1000)
    print(read)

#for element in pre_total:
#    print(int(element,2))
    
#for element in post:
#    print(int(element,2))
