#include <string>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

class Catalogue {

    std::string title;
    int size;
    std::string last_edit_time;
    bool is_file = false;

    Catalogue*  parent = nullptr;
    Catalogue* first_child = nullptr;
    Catalogue* next_sibling = nullptr;

    Catalogue(std::string title, int size, std::string time): title(std::move(title)), size(size), last_edit_time(std::move(time)){}

    Catalogue* getRoot();
    std::string getTime();
    void updateSizes(Catalogue* current, int size);
    void updateEditTime(){last_edit_time = getTime();}

    Catalogue* goToHelper(std::string title, Catalogue* root);

    //comparators
    static bool isFolder(Catalogue* current){return !current->is_file;}
    static bool isFile(Catalogue* current){return current->is_file;}
    //due to dates being formatted as "%Y-%m-%d.%X" it's enough to compare strings
    static bool isMinTime(Catalogue* lhs, Catalogue* rhs){ return  lhs->last_edit_time < rhs->last_edit_time;}
    static bool isMaxTime(Catalogue* lhs, Catalogue* rhs){ return  lhs->last_edit_time > rhs->last_edit_time;}


public:
    explicit Catalogue(std::string root_title):title(std::move(root_title)), size(0), last_edit_time(getTime()){};

    Catalogue* goTo(std::string title);

    void addFolder(std::string title);
    void addFile(std::string title, int size);

    //search
    std::vector<Catalogue*> find_if(Catalogue* current, bool (*condition)(Catalogue*));
    Catalogue* compare_all(Catalogue* current, bool (*condition)(Catalogue*,Catalogue*));

    //filters
    int getCatalogueSize() {
        return getRoot()->size;
    }

    int getFoldersCount() {
        return find_if(getRoot(), isFolder).size();
    }

    int getFilesCount() {
        return find_if(getRoot(), isFile).size();
    }

    std::string getMinTime(){
        return compare_all(getRoot(), isMinTime)->last_edit_time;
    }

    std::string getMaxTime(){
        return compare_all(getRoot(), isMaxTime)->last_edit_time;
    }

    //output
    friend std::ostream& operator<< (std::ostream &stream, const Catalogue& catalogue);
    void print();
};