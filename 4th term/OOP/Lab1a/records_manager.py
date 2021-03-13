import collections
import json
import datetime
from collections import defaultdict
from json import JSONDecodeError

CHECKED = u"\u2705"
UNCHECKED = u"\u25A1"

DATA_FILE = "calendar_data.json"


class Task:
    def __init__(self, text):
        self.text = text
        self.is_done = False

    @staticmethod
    def view(date):
        records = RecordsManager()
        try:
            tasks = records.data[date]["tasks"]
            for task in tasks:
                state = UNCHECKED
                if task["is_done"]:
                    state = CHECKED
                print(f"\t{state} {task['text']}")
        except KeyError:
            print("None")


class Meeting:
    def __init__(self, text, time):
        self.text = text
        self.time = time

    @staticmethod
    def view(date):
        records = RecordsManager()
        try:
            meetings = records.data[date]["meetings"]
            for meeting in meetings:
                print(f"\t{meeting['time']} - {meeting['text']}")
        except KeyError:
            print("None")


class RecordsManager:

    def __init__(self):
        try:
            with open(DATA_FILE, "r+") as file:
                try:
                    self.data = json.load(file)
                except JSONDecodeError:
                    self.data = {}
        except IOError:
            with open(DATA_FILE, "w+") as file:
                pass

    def _get_record_type(self, record):
        if type(record) is Task:
            return "tasks"
        else:
            return "meetings"

    def view_records(self, date):
        try:
            data = self.data[date]
            try:
                tasks = data["tasks"]
            except KeyError:
                tasks = None
            try:
                meetings = data["meetings"]
            except KeyError:
                meetings = None

            print(f"Meetings for {date} are:\n\t{meetings}\nTasks for {date} are: \n\t{tasks}")
        except KeyError:
            print("No records for this date")
            return None

    def mark_task_as_done(self, index, selected_date):
        self.data[selected_date]["tasks"][index]["is_done"] = True

    def add_record(self, record, date):
        record_type = self._get_record_type(record)

        try:
            updated_value = self.data[date]
            # there are other records for this date...
            try:
                temp_list = list(updated_value[record_type])
                temp_list.append(record.__dict__)
            except KeyError:
                # no records of added type for this date yet
                temp_list = [record.__dict__]
            finally:
                updated_value[record_type] = temp_list
                updated_data = {date: updated_value}

        except KeyError:
            # no records for this date yet
            updated_data = {date: {record_type: [record.__dict__]}}

        self.data.update(updated_data)
        self.save_changes()

    def delete_record(self, record_type, index, date):
        record_type += "s"
        try:
            del self.data[date][record_type][index]
            self.save_changes()
        except KeyError:
            print("Wrong input")

    def search_record(self, date):
        print(f" Meetings planned for this date:")
        Meeting.view(date)
        print(f" To-Do: ")
        Task.view(date)

    def save_changes(self):
        with open(DATA_FILE, "w+") as file:
            json.dump(self.data, file)

    def __del__(self):
        with open(DATA_FILE, 'w') as file:
            json.dump(self.data, file, indent=4)
