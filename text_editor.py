
from datetime import date
from datetime import datetime

#stored_data = open("moisture_values.txt", "r")
#print(stored_data.read())
#stored_data.close()

def writeToFile ( per , val):
    
    now = datetime.now().strftime("%Y/%b/%d %H:%M:%S")

    stored_data = open("moisture_values.txt", "a")

    msg = "\n" + now + "\t Percentage " + per + "%\t" + "Value: " + val
    
    stored_data.write(msg)
    print(msg)

    stored_data.close()

def readFile():
    stored_data = open("moisture_values.txt", "r")
    print(stored_data.read())
    stored_data.close()
    
    
def costum_write ( msg ):
    stored_data = open("moisture_values.txt", "a")
    stored_data.write(msg)
    stored_data.close()

