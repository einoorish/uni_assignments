/*
Для зберігання елементів треба реалізувати наступні механізми:
1.Зберігання в пам’яті, без збереження на диск - add_item()
2.Зберігання у вигляді текстового файлу; - save_to_txt_file()
3.Зберігання у вигляді бінарного файлу. - save_to_binary_file()

3.Відновлення даних (зчитування даних з файлу); - read_bin_file() || read_txt_file
4.Вивід всіх збережених даних; - output_all_data()

5. Фільтр:
а) товари з назвою, що містить заданий фрагмент тексту - filter_by_names()
б) товари з кількістю не менше заданої - filter_by_quantity()
в) товари, термін зберігання яких спливає до заданого дня - filter_by_expiration_term()

6. Модифікація елементів - edit_item()
7. Видалення елементів - delete_item()
*/
#pragma once

#include "Item.h"
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <deque>
#include <time.h>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//needed to calculate id of the next item; safe to be static, since it gets recalculated each time db is read

class Database{

    std::deque<Item> new_data;
    std::deque<Item> file_data;
    std::string db_file_path;
    //bool isOpen = false;

    public:
        Database()= default;
        explicit Database(const std::string& file_path){
            db_file_path = file_path;
            new_data = {};
            read_bin_file(); // inits file_data
            //isOpen = true;
        }

        ///READING
        //void read_txt_file(std::string = "data.txt");
        void read_bin_file();

        ///SAVING
        void add_item_to_memory();
        void save_to_txt_file(const std::string& = "data.txt");
        void save_to_binary_file(const std::string& = "data.bin");

        ///FILTERS
        void filter_by_names(const std::string& substring);//товари з назвою, що містить заданий фрагмент тексту
        void filter_by_quantity(int quantity);//товари з кількістю не менше заданої
        void filter_by_expiration_term(Date expiration_term);//товари, термін зберігання яких спливає до заданого дня

        //TODO: rewriting the whole file is inefficient...
        void edit_item();
        void delete_item();
        void clear_entered_data(){new_data.clear();};

        ///UTILS AND OUTPUT
        void update_items_inDB(){ITEMS_COUNT_IN_DB= file_data.size()+new_data.size();};
        static size_t get_items_count_in_DB(){return ITEMS_COUNT_IN_DB;}
        void generate(int N);
        static void outputColoredMessage(const std::string& text){
            SetConsoleTextAttribute(hConsole, 5);
            std::cout << text << std::endl;
            SetConsoleTextAttribute(hConsole, 7);
        };
        static std::string askForFileName(){
            std::string current_file;
            outputColoredMessage("Enter file name: ");
            std::cin >> current_file;
            return current_file;
        }
        void join_file_data_and_new_data(){
            for (Item& i:file_data)
                new_data.push_front(i);
        }
        void output_entered_data(){
            for (const auto &i : new_data)
                std::cout << i << std::endl;
        }
        void output_file_data(){
            if(file_data.empty()){
                std::cout << "File is empty or not specified. Try using read from file option first"<<std::endl;
            }
            for (const auto &i : file_data)
                std::cout << i << std::endl;
        }
        void output_all_data(){
            std::cout << "FILE: " << std::endl;
            output_file_data();
            std::cout << "MEMORY:" << std::endl;
            output_entered_data();
        }
        void benchmark();
        //bool is_open(){return isOpen;}
};
