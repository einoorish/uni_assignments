#include "Database.h"
size_t ITEMS_COUNT_IN_DB = 0;

void Database::read_bin_file() {
    file_data.clear();
    std::ifstream file(db_file_path, std::fstream::in | std::ios::binary);

    if(!file.is_open() || !file.seekg(0, std::ios::end).tellg()) {
        std::cout <<"\tDatabase is empty or file does not exist yet. Try adding new item to it."<<std::endl;
        return;
    }
    file.seekg (0, std::ios::beg);

    while (!file.eof()) {
        Item item;
        item.readFromBinStream(file);
        file_data.push_back(item);
    }

    //eof bit will not set until read operation attempts to extract past-the-end symbol, thus one extra emtpy entry will be added
    if(!file_data.empty())
        file_data.pop_back();

    file.close();
    update_items_inDB();
}

void Database::add_item_to_memory()
{
    Item item;
    std::cin >> item;
    new_data.emplace_back(item);
    ITEMS_COUNT_IN_DB++;
}

void Database::edit_item()
{
    int index;
    Database::outputColoredMessage("Enter item index: ");
    std::cin >> index;

    try{
        std::cout <<"item you're editing: "<< file_data.at(index)<<std::endl;
    }catch (std::out_of_range &e){
        std::cout << "Index out of range"<<std::endl;
        return;
    }
    outputColoredMessage("Enter updated data for this item: \n");
    ITEMS_COUNT_IN_DB = index;
    std::cin >> file_data.at(index);

    std::ofstream file("data.bin", std::ios::trunc |std::ios::binary);

    ITEMS_COUNT_IN_DB = 0;
    for(Item i:file_data){
        i.writeToBinStream(file);
        ITEMS_COUNT_IN_DB++;
    }
    file.close();

}

void Database::delete_item()
{
    int index;
    Database::outputColoredMessage("Enter item index: ");
    std::cin >> index;

    try{
        std::cout <<"item deleted: "<< file_data.at(index)<<std::endl;
    }catch (std::out_of_range &e){
        std::cout << "Index out of range"<<std::endl;
        return;
    }

    file_data.erase(file_data.begin()+index);

    std::ofstream file("data.bin", std::ios::trunc |std::ios::binary);

    ITEMS_COUNT_IN_DB = 0;
    for(Item i:file_data){
        i.writeToBinStream(file);
        ITEMS_COUNT_IN_DB++;
    }
    file.close();
}

void Database::save_to_txt_file(const std::string& file_name)
{
    std::ofstream file(file_name, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cout << "Cannot open file";
        return;
    }
    for(const auto & i : new_data){
        file << i << std::endl;
    }

    file.close();
}

void Database::save_to_binary_file(const std::string& file_name)
{
    std::ofstream file(file_name, std::ios_base::app | std::ios_base::binary);

    for(auto & i : new_data){
        i.writeToBinStream(file);
    }
    new_data.clear();
    file.close();
}

void Database::filter_by_names(const std::string& substring)
{
    // using trie structured tree would result in better performance, but since I'm already using vectors here...
    std::deque<Item> result;

    copy_if(file_data.begin(),
            file_data.end(),
            std::back_inserter(result),
            [substring](Item const& item) {
                return (!item.getName().empty() && item.getName().find(substring) != std::string::npos);
            });

    for(Item& i:result)
        std::cout << i << std::endl;
}

void Database::filter_by_quantity(int quantity)
{
    std::cout<< "There are more than " <<quantity<<" units of these items:"<<std::endl;

    for(const auto & i : file_data){
        if(i.getQuantity()>=quantity){
            std::cout << i << std::endl;
        }
    }
}

void Database::filter_by_expiration_term(Date curious_date)
{
    std::cout<< "These items will expire by " <<curious_date<<':'<<std::endl;

    for(const auto & i : file_data){
        if(i.getManufactureDate() + i.getExpirationPeriod() <= curious_date){
            std::cout << i << std::endl;
        }
    }

}

void Database::generate(int N) {
    for(int i = 0; i < N; i++){
        std::istringstream input("Tomato 10 0 10 02 2020 10 20 50");
        std::cin.rdbuf(input.rdbuf());
        std::streambuf *old = std::cout.rdbuf(nullptr);

        add_item_to_memory();

        std::cout.rdbuf(old);
    }
}

void Database::benchmark() {
    size_t N = 10;
    unsigned int delta = 0;
    std::ofstream results("benchmark_results.txt", std::ios::trunc);

    while((float)delta/CLOCKS_PER_SEC < 10){
        delta = clock();
        generate(N);
        delta = clock() - delta;
        //std::cout << (float)delta/CLOCKS_PER_SEC << std::endl;
        if((float)delta/CLOCKS_PER_SEC < 1)
            N=N*2;
        else N += N;
    }

    results << "Generated " << N << " items in " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;

    delta = 0;
    N = 10;
    int counter=1;
    while((float)delta/CLOCKS_PER_SEC < 10){
        std::ofstream file("data.bin", std::ios::trunc);
        delta = clock();
        while(counter*ITEMS_COUNT_IN_DB<N){
            for(int i = 0; i < ITEMS_COUNT_IN_DB; i++)
                new_data.at(i).writeToBinStream(file);
            counter++;
        }
        delta = clock() - delta;
        //std::cout << (float)delta/CLOCKS_PER_SEC << std::endl;
        if((float)delta/CLOCKS_PER_SEC < 1)
            N *= 2;
        else N += N;
    }

    results << "Writing " << N << " items to database took " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;

    while((float)delta/CLOCKS_PER_SEC < 10){
        std::ifstream file("data.bin", std::ios::in);
        delta = clock();
        while(file){
            for(int i = 0; i < ITEMS_COUNT_IN_DB; i++)
                file_data.at(i).readFromBinStream(file);
            counter++;
        }
        delta = clock() - delta;
        //std::cout << (float)delta/CLOCKS_PER_SEC << std::endl;
        if((float)delta/CLOCKS_PER_SEC < 1)
            N *= 2;
        else N += N;
    }

    results << "Reading " << N << " items from database took " << (float)delta/CLOCKS_PER_SEC << " seconds"<< std::endl;

    results.close();

    std::cout << "Benchmark finished. See results in \"benchmark_results.txt\""<< std::endl;
}

//void Database::read_txt_file(std::string& file_name)
//{
//    if (!file_data.empty()) file_data.clear();
//
//    std::ifstream file(file_name);
//    Item item;
//
//    while (!file.fail() && !file.eof())
//    {
//        try{
//            file >> item;
//            file_data.push_back(item);
//        } catch (std::invalid_argument &e) {std::cerr << e.what();}
//    }
//
//    if(file_data.empty()) std::cout << "Empty file" << std::endl;
//}