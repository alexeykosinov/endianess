#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {

    std::string file_name;

    for (int i = 1; i < argc; i++) {

        std::string s(argv[i]);

        if (i == 1) {

            auto s_it = s.find("-f", 0);

            if (s_it == std::string::npos) {
                std::cout << "Unknown: " << s << std::endl;
                std::cout << "Use: -f file.[extension]" << std::endl;
                return 1;
            }
        }
        else if (i == 2) {
            file_name = s;
        }
        else {
            std::cout << "Unknown: " << s << std::endl;
            std::cout << "Use: -f file.[extension]" << std::endl;
            return 1;
        }
    }

    std::string line;
    std::ifstream read_file(file_name);
    std::ofstream write_file("data_edit.dat");

    if (!read_file.is_open()) {
        std::cout << "Unable to open a file" << std::endl;
        std::cout << "Use: -f file.[extension]" << std::endl;
        return 1;
    }


    while (getline(read_file, line)) {
        
        std::stringstream line_edit;
        
        for (size_t i = 0; i <= line.size(); i++) {
            if (i != '\0') line_edit << line[line.size()-i];
        }

        if (read_file.eof()) {
            write_file << line_edit.rdbuf();
        }
        else {
            write_file << line_edit.rdbuf() << '\n';
        }
        
    }
    std::cout << "Done" << std::endl;
    read_file.close();
    write_file.close();
    


    return 0;
}