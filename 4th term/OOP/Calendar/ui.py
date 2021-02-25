from datetime import date
from records_manager import *

def make_date(year, month, day):
    if int(int(month)/10) == 0:
        month = f"0{month}"
    if int(int(day)/10) == 0:
        day = f"0{day}"

    return f"{year}-{month}-{day}"

class UI:

    def __init__(self, username):
        self.records = RecordsManager()
        self.username = username
        print(f"Hello, {username}.\nToday is {date.today()}")

    def data_for_today(self):
        today = date.today()
        print(f" Meetings planned for today:")
        Meeting.view(make_date(today.year, today.month, today.day))
        print(f" To-Do: ")
        Task.view(make_date(today.year, today.month, today.day))

        print("\n--------------\n")

    def ask_for_date(self):
        print("Choose date:")
        return make_date(input("\tYear:"), input("\tMonth:"), input("\tDay:"))

    def _search(self):
        self.records.search_record(self.ask_for_date())

    def _add(self):
        date = self.ask_for_date()

        record_type = input("Do you want to add a new task or meeting? ")
        if record_type == "task":
            record = Task(input("Enter task content: "))
        elif record_type == "meeting":
            record = Meeting(input("Enter task content: "), input("Enter meeting time(HH:MM)"))
        else:
            return

        self.records.add_record(record, date)

    def available_commands(self):
        print("Available commands: search, add, edit, delete")
        command = input("Enter one of the commands above: ")

        if command == "search":
            self._search()
        elif command == "add":
            self._add()
        elif command == "edit":
            pass
        elif command == "delete":
            pass
        else:
            return

        self.available_commands()
