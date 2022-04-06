
from datetime import date
from datetime import datetime

#stored_data = open("moisture_values.txt", "r")
#print(stored_data.read())
#stored_data.close()

def writeToFile ( per , val):
    
    now = datetime.now().strftime("%Y/%b/%d %H:%M:%S")

    stored_data = open("moisture_values.txt", "a")

    stored_data.write("\n" + now + "\t Percentage " + per + "%" + "Value")

    stored_data.close()

def readFile():
    stored_data = open("moisture_values.txt", "r")
    print(stored_data.read())
    stored_data.close()
