from ui import UI
from records_manager import MyTest

USERDATA_FILENAME = "userdata.txt"
username = ""


def run_app():
    ui = UI(username)

    ui.data_for_today()
    ui.available_commands()


def run_tests():
    tests = MyTest()
    tests.test_mark_as_done()
    tests.test_add_search()

    print("\n\n-------------All tests passed!-----------\n\n")


def prepare_app():
    try:
        file = open(USERDATA_FILENAME)
        username = file.read()
    except IOError:
        file = open(USERDATA_FILENAME, "w+")
        username = input("Your name: ")
        file.write(username)
    finally:
        file.close()

    run_tests()


prepare_app()
run_app()
