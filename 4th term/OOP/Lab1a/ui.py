from datetime import date
from records_manager import *
import enum


def make_date(year, month, day):
    if int(int(month) / 10) == 0:
        month = f"0{int(month)}"
    if int(int(day) / 10) == 0:
        day = f"0{int(day)}"

    return f"{year}-{month}-{day}"


class UI:

    def __init__(self, username):
        self.records = RecordsManager()
        self.selected_date = make_date(date.today().year, date.today().month, date.today().day)
        self.username = username
        print(f"Hello, {username}.\nToday is {date.today()}")

    def data_for_today(self):
        today = date.today()
        print(f" Meetings planned for today:")
        print(Meeting.view(self.selected_date))
        print(f" To-Do: ")
        print(Task.view(self.selected_date))

        print("\n--------------\n")

    def ask_for_date(self):
        print("Choose date:")
        self.selected_date = make_date(input("\tYear:"), input("\tMonth:"), input("\tDay:"))
        return self.selected_date

    def _search(self):
        self.records.search_record(self.ask_for_date())

    def _mark_task_as_done(self):
        index = int(input(f"Enter task index: "))
        self.records.mark_task_as_done(index, self.selected_date)

    def _add(self):
        record_type = input("Do you want to add a new task or meeting? ")
        if record_type == "task":
            record = Task(input("Enter task content: "))
        elif record_type == "meeting":
            record = Meeting(input("Enter task content: "), input("Enter meeting time(HH:MM)"))
        else:
            return

        self.records.add_record(record, self.selected_date)

    def _delete(self):
        record_type = input("Do you want to delete task or meeting? ")
        index = int(input(f"Enter {record_type} index: "))

        self.records.delete_record(record_type, index, self.selected_date)

    def available_commands(self):
        print("Available commands: search, mark_done, add, delete, exit")
        command = input("Enter one of the commands above: ")

        if command == "exit":
            return
        if command == "search":
            self._search()
        elif command == "mark_done":
            self._mark_task_as_done()
        elif command == "add":
            self._add()
        elif command == "delete":
            self._delete()

        self.available_commands()
