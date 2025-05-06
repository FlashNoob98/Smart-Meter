import serial

pre = []
post = []
pre_total=[]
ser = serial.Serial("COM3", baudrate=9600, timeout=3.0)
count = 0
#while True:
for line in ser.read(1000):
    if (chr(line) == (('\r'))):
        count = count+1
        pass
        #print("\n")
    else:
        if (count > 0):
            print(str(count) + str(': ') + str(bin(line)) )
            #print((line))
            if ((count%2)!=0):#Se dispari
                post.append(bin(line))
                count = count+1
            else:
                pre.append(bin(line))
            

if len(pre)>len(post):
    pre.pop()
elif len(post)>len(pre):
    post.pop()


#if len(pre[1])>6:
#    a = pre
#    pre = post
#    post = a

for element in pre:
    pre_total.append(element + '00000000')

#print(pre_total)
#print(post)
somma = []
for i in range(0,len(post)):
    somma.append(int(pre_total[i],2)+int(post[i],2))

print(somma)

#for element in pre_total:
#    print(int(element,2))
    
#for element in post:
#    print(int(element,2))