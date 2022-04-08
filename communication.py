#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time
#import RPi.GPIO as GPIO #https://www.youtube.com/watch?v=DPXRemnogC0&list=PLHfdivUFIeEL0ShTTLWGKBOJmgMepLGE3&index=5&ab_channel=AlexanderBaran-Harper
from gpiozero import LED #https://www.youtube.com/watch?v=iL_oZGHLHvU&t=1353s&ab_channel=DroneBotWorkshop

import text_editor

global _value, _percentage

if __name__ == '__main__':
    LED(17).on()
    print('Running. Press CTRL-C to exit.')
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(5) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            text_editor.costum_write("\n\t\tStarted\n")
            try:
                while True:
                    #cmd=input("Enter command : ")
                    
                    cmd = "value"
                    arduino.write(cmd.encode())
                    
                    #print("asked value...")
                    
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        answer.decode().split("'")
                        _value = chr(answer[0]) + chr(answer[1]) + chr(answer[2]) 
                        
                        #print("value: " + _value)
                        
                        arduino.flushInput() #remove data after reading
                    
                    cmd = "percentage"
                    arduino.write(cmd.encode())
                    
                    #print("asked percentage...")
                    
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        answer.decode().split("'")
                        _percentage = chr(answer[0]) + chr(answer[1])
                        
                        #print("percentage: " + _percentage)
                        
                        arduino.flushInput() #remove data after reading
                    
                    text_editor.writeToFile(_percentage, _value)
                    #text_editor.readFile()
                    
                    time.sleep(60*60*4)
                    
                        
            finally:
                print("KeyboardInterrupt has been caught.")
                text_editor.costum_write("\tEnded: " + text_editor.datetime.now().strftime("%Y/%b/%d %H:%M:%S") + "\n")
                LED(17).off()
                                         