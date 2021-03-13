from ui import UI
from datetime import date
from records_manager import RecordsManager, MyTest
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

tests = MyTest()
tests.test_mark_as_done()
tests.test_add_search()

print("\n\n-------------All tests passed!-----------\n\n")

UI = UI(username)


UI.data_for_today()
UI.available_commands()



