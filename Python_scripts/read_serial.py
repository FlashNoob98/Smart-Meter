import serial

ser = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)
count = 0
while True:
    for line in ser.read():
        if (chr(line) == (('\r'))):
            print("\n")
        else:
            print(str(count) + str(': ') + str(bin(line)) )
            count = count+1
