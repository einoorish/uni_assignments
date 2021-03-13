from ui import UI
from datetime import date
from records_manager import RecordsManager
from records_manager import Task
from records_manager import Meeting

USERDATA_FILENAME = "userdata.txt"
username = ""

try:
    file = open(USERDATA_FILENAME)
    username = file.read()
except IOError:
    file = open(USERDATA_FILENAME, "w+")
    username = input("Your name: ")
    file.write(username)
finally:
    file.close()

UI = UI(username)

UI.data_for_today()
UI.available_commands()



