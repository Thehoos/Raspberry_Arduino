#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time
import text_editor

global _value, _percentage

if __name__ == '__main__':

    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(5) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    #cmd=input("Enter command : ")
                    
                    cmd = "value"
                    arduino.write(cmd.encode())
                    print("asked value...")
                    
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        answer.decode().split("'")
                        _value = chr(answer[0]) + chr(answer[1]) + chr(answer[2]) 
                        print("value: " + _value)
                        arduino.flushInput() #remove data after reading
                    
                    cmd = "percentage"
                    arduino.write(cmd.encode())
                    print("asked percentage...")
                    
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        answer.decode().split("'")
                        _percentage = chr(answer[0]) + chr(answer[1]) + '%'
                        print("percentage: " + _percentage)
                        arduino.flushInput() #remove data after reading
                    
                    text_editor.writeToFile(_percentage, _value)
                    text_editor.readFile()
                    
                    time.sleep(10)
                    
                        
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")