
from datetime import date
from datetime import datetime

now = datetime.now().strftime("%Y/%b/%d %H:%M:%S")


stored_data = open("moisture_values.txt", "a")

stored_data.write("\n" + now + "\t234\t95%")

stored_data.close()



stored_data = open("moisture_values.txt", "r")
print(stored_data.read())
stored_data.close()
