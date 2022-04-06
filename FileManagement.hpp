#include <iostream>
#include <string>
#include <fstream>

std::string* get_infof(std::string dir){ // reading file
    std::string info;
    std::fstream file;
    std::string buf[5];
    std::string check;
    int j=0;
    file.open("local/"+dir+".data", std::ios::binary | std::ios::in | std::ios::out); // opening info file
    if (file.is_open()){
        file >> check;
        while(check!=""){
            std::string line;
            file >> line;
            buf[j] = line;
            j++;
        }
    }
    else{ // open defaults if no info file
        file.open("local/"+dir+".defaults", std::ios::binary | std::ios::in | std::ios::out);
        while(1){
            std::string line;
            file >> line;
            buf[j] = line;
            j++;
        }
    }
    file.close();

    return buf;
}

// r - with or without reset, useful for deleting account data or resetting settings to default
void set_infof(std::string dir, std::string info, bool r){ // writing in file
    std::fstream file;
    std::string path = "local/"+dir+".data";
    file.open(path, std::ios::trunc); // opening info file, overwriting it
    if (r){ // reset
        if (file.is_open()) std::remove(path.c_str());
    }
    else{ // save
        if (file.is_open()) file << info;
    }
    file.close();
}
