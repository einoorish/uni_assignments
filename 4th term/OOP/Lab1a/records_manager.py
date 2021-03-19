import json
import unittest
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
                return f"\t{state} {task['text']}"
        except KeyError:
            return None


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
                return f"\t{meeting['time']} - {meeting['text']}"
        except KeyError:
            return None


def _get_record_type(record):
    if type(record) is Task:
        return "tasks"
    else:
        return "meetings"


class RecordsManager:

    def __init__(self):
        try:
            with open(DATA_FILE, "r+") as file:
                try:
                    self.data = json.load(file)
                except JSONDecodeError:
                    self.data = {}
        except IOError:
            with open(DATA_FILE, "w+"):
                pass

    def mark_task_as_done(self, index, selected_date):
        try:
            self.data[selected_date]["tasks"][index]["is_done"] = True
        except IndexError:
            print("Wrong input")

    def add_record(self, record, date):
        """Adds a %record% for %date% to file and data list"""
        record_type = _get_record_type(record)

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
        """Removes record of %record_type% at %index% for %date% from file and data list"""

        record_type += "s"
        try:
            del self.data[date][record_type][index]
            self.save_changes()
        except KeyError:
            print("Wrong input")

    def view_records(self, date):
        """Prints records row for %date%"""

        data = self.search_records(date)
        print(f" Meetings planned for this date:")
        print(data["meetings"])
        print(f" To-Do: ")
        print(data["tasks"])

    def search_records(self, date):
        """Returns records row for %date% as dictionary, format: {"meetings": *, "tasks: *"}"""

        return {"meetings": Meeting.view(date), "tasks": Task.view(date)}

    def save_changes(self):
        with open(DATA_FILE, "w+") as file:
            json.dump(self.data, file)

    def __del__(self):
        with open(DATA_FILE, 'w') as file:
            json.dump(self.data, file, indent=4)


class MyTest(unittest.TestCase):

    def setUp(self):
        self.task = Task("test")
        self.meeting = Meeting("meeting", "00:00")
        self.date = "0-0-0"
        self.records_manager = RecordsManager()

    def tearDown(self):
        self.records_manager.delete_record("task", 0, self.date)

    def test_mark_as_done(self):
        self.setUp()
        self.records_manager.add_record(self.task, self.date)

        self.assertEqual(self.task.is_done, False, "Previously undone task is not marked as done")
        self.records_manager.mark_task_as_done(0, self.date)
        self.assertEqual(self.task.is_done, True, "Previously undone task marked as done")
        self.records_manager.mark_task_as_done(0, self.date)
        self.assertEqual(self.task.is_done, True, "Previously done task still marked as done")

        self.tearDown()

    def test_add_search(self):
        self.setUp()
        self.assertIsNone(self.records_manager.search_records(self.date)["tasks"], "No records for the date yet")

        self.records_manager.add_record(self.task, self.date)
        self.assertIsNotNone(self.records_manager.search_records(self.date), "Task added successfully")

        self.tearDown()
