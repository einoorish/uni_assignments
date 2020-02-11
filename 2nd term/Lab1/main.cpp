#include "Database.h"

constexpr const char* DB_COMMANDS = "Commands available: \n1 - read database file content\n\t11 - filter file data by names\n\t12 - filter file data by quantity\n\t13 - filter file data by expiration date\n2 - edit db item\n3 - delete db item";
constexpr const char* NEW_DATA_COMMANDS = "Commands available: \n1 - review entered data\n2 - add item\n3 - push data to binary file\n4 - write all data to text file\n5 - clear entered data";

void demoMode();
void showNewDataCommands(Database& db);
void showFileCommands(Database& db);


int main(){
    int operation = 3;

    std::cout << "Choose mode: 1 - Interactive, 2 - Demo, 3 - Benchmark"<<std::endl;
    std::cin >> operation;

    switch (operation) {
        case 1: {
            bool return_flag = false;

            std::string file_path;
            std::cout << "Enter database file path: ";
            std::cin >> file_path;
            Database db = Database(file_path);

            while(!return_flag){
                std::cout << "Would you like to work w\\ the file or your new data?\n 1 - file\n 2 - new data\n 0 - exit"<<std::endl;
                std::cin >> operation;// 1 = file, 2 = new data

                if (operation == 2)
                    showNewDataCommands(db);
                else if(operation == 1)
                    showFileCommands(db);
                else if(operation == 0)return_flag = true;
                std::cout << std::endl;
            }

            break;
        }
        case 2: {
            demoMode();
            break;
        }
        case 3: {
            Database db;
            db.benchmark();
            break;
        }
        default: {
            std::cout <<std::endl<< "Invalid input. Try again\n"<<std::endl;
            main();
        }
    }

}

void showFileCommands(Database& db) {
    std::cout << DB_COMMANDS << std::endl;
    int command;
    std::cin >> command;

    switch(command){
        case 1:{
            db.output_file_data();
            break;
        }
        case 11:{
            std::string substring;
            Database::outputColoredMessage("Enter filter text: ");
            std::cin >> substring;
            db.filter_by_names(substring);
            break;
        }
        case 12:{
            int quantity = 0;
            Database::outputColoredMessage("Enter quantity: ");
            std::cin >> quantity;
            db.filter_by_quantity(quantity);
            break;
        }
        case 13:{
            Date curious_date;// "термін зберігання яких спливає до заданого дня"
            Database::outputColoredMessage("Enter date (d/m/y): ");
            std::cin >> curious_date.day;
            std::cin >> curious_date.month;
            std::cin >> curious_date.year;
            db.filter_by_expiration_term(curious_date);
            break;
        }
        case 2:{
            db.edit_item();
            break;
        }
        case 3:{
            db.delete_item();
            break;
        }
        default:return;
    }
}

void showNewDataCommands(Database& db) {
    std::cout << NEW_DATA_COMMANDS << std::endl;
    int command;
    std::cin >> command;

    switch(command) {
        case 1: {
            db.output_entered_data();
            break;
        } case 2: {
            db.add_item_to_memory();
            break;
        } case 3: {
            db.save_to_binary_file();
            break;
        } case 4: {
            db.save_to_txt_file();
            break;
        } case 5: {
            db.clear_entered_data();
            break;
        }
        default:return;
    }

}

void demoMode(){
    Database::outputColoredMessage("Welcome to the demo mode.");
    Database::outputColoredMessage(
            "Item format: ID NAME QUANTITY UNITS MANUFACTURE_DATE(dd/mm/yyyy hh:mm) DAYS_TO_EXPIRATION");
    //std::cout << "Places where your input is expected are marked blue"<<std::endl;

    Database::outputColoredMessage(
            "-------------------------------------------------------------------------------------");
    Database::outputColoredMessage("Opening database data.bin");
    Database db = Database("data.bin");

    Database::outputColoredMessage("\n*Creating new item.\n\t Input is:\n\t\"Tomato 10 0 10 02 2020 10 20 50\"");//\n\t 1 Milk 5 3 12 01 2020 15 40 10\""
    std::istringstream input("Tomato 10 0 10 02 2020 10 20 50");
    std::cin.rdbuf(input.rdbuf());
    std::streambuf *old = std::cout.rdbuf(nullptr);
    //Redirecting output to avoid showing messages e.g "File is empty or does not exist."
    db.add_item_to_memory();
    std::cout.rdbuf(old);

    Database::outputColoredMessage("*Reading entered data:");
    db.output_entered_data();

    Database::outputColoredMessage("\n*Adding data from memory to database(binary file)");
    db.save_to_binary_file();

    std::cout << std::endl;
    Database::outputColoredMessage("*Reading file data.bin again");
    db.read_bin_file();
    Database::outputColoredMessage("Result: ");
    db.output_file_data();


    std::cout << std::endl;
    Database::outputColoredMessage("*Edit item at index 0 in database");
    Database::outputColoredMessage("Enter item index: \n\tInput is: 0");
    Database::outputColoredMessage("Enter updated data for this item: \n\tInput is: \"Milk 5 3 12 01 2020 15 40 10\"");
    input = std::istringstream("0 Milk 5 3 12 01 2020 15 40 10");
    std::cin.rdbuf(input.rdbuf());
    old = std::cout.rdbuf(nullptr);
    db.edit_item();
    std::cout.rdbuf(old);

    Database::outputColoredMessage("\nOutput all data:\n");
    db.output_all_data();

    Database::outputColoredMessage("\n*Adding another item to memory. Input is: \"Unicorn_Meat 5 1 12/12/2020 00:00 4\"");
    std::istringstream iss("Unicorn_Meat 5 1 12/12/2020 00:00 4");
    std::cin.rdbuf(iss.rdbuf());
    old = std::cout.rdbuf(nullptr);
    db.add_item_to_memory();
    std::cout.rdbuf(old);

    Database::outputColoredMessage("\n*Adding data from memory to database");
    db.save_to_binary_file();
    std::cout << std::endl;
    Database::outputColoredMessage("*Reading database");
    db.read_bin_file();

    Database::outputColoredMessage("\tResult (all): ");
    db.output_all_data();

    Database::outputColoredMessage("\n*Filter database entries by name. Input is: \"Un\"\nResult: ");
    db.filter_by_names("Un");

    Database::outputColoredMessage("\n*Filter file data by quantity. Input is: \"6\"\nResult: ");
    db.filter_by_quantity(6);

    Database::outputColoredMessage("\n*Filter file data by date. Input is: \"20/10/2020 10:10\"");
    db.filter_by_expiration_term(Date(20,10,2020,10,10));

    Database::outputColoredMessage("\n*Deleting item 2 from database.");
    old = std::cout.rdbuf(nullptr);
    iss = std::istringstream ("2");
    std::cin.rdbuf(iss.rdbuf());
    db.delete_item();
    std::cout.rdbuf(old);

    Database::outputColoredMessage("*Deleting item 1 from database.\n");
    old = std::cout.rdbuf(nullptr);
    iss = std::istringstream ("1");
    std::cin.rdbuf(iss.rdbuf());
    db.delete_item();
    std::cout.rdbuf(old);

    Database::outputColoredMessage("\tResult (all): ");
    db.output_all_data();
    Database::outputColoredMessage("\n*Saving all data to text file \"data.txt\"\n");
    db.join_file_data_and_new_data();
    db.save_to_txt_file();

    Database::outputColoredMessage("End of Demo Mode.");
}
