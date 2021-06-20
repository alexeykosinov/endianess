#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {

    std::string file_name;
    std::string outfile_name = "data_edit.dat";
    std::string set_option = "default";

    for (int i = 1; i < argc; i++) {

        std::string s(argv[i]);


        if (i == 1) { // -f
            auto s_it = s.find("-f", 0);

            if (s_it == std::string::npos) {
                std::cout << "Unknown: " << s << std::endl;
                std::cout << "Use: -f file.[extension] -o [coe/mif] (optional)" << std::endl;
                return 1;
            }
        }
        else if (i == 2) { // filename.[extension]
            file_name = s;
        }        
        else if (i == 3) { // -o (optional)
            auto s_it = s.find("-o", 0);

            if (s_it == std::string::npos) {
                std::cout << "Unknown: " << s << std::endl;
                std::cout << "Use: -o [option]" << std::endl;
                return 1;
            }
        }
        else if (i == 4) { // additional settings
            if (s == "coe") {
                set_option = "coe_format";
                outfile_name = "data_edit.coe";
            }
            else if (s == "mif") {
                set_option = "mif_format";
                outfile_name = "data_edit.mif";
            }
            else {
                std::cout << "Unknown: " << s << std::endl;
                std::cout << "Avaliable option: " << std::endl;
                std::cout << "    - coe (Xilinx Core Generator input file format)" << std::endl;
                std::cout << "    - mif (Xilinx Core Generator output file format)" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "Unknown: " << s << std::endl;
            std::cout << "Use: -f file.[extension] -o [coe/mif] (optional)" << std::endl;
            return 1;
        }
    }

    std::string line;
    std::ifstream read_file(file_name);
    std::ofstream write_file(outfile_name);

    if (!read_file.is_open()) {
        std::cout << "Unable to open a file" << std::endl;
        std::cout << "Use: -f file.[extension]" << std::endl;
        return 1;
    }



    if (set_option == "coe_format") {

        write_file << "MEMORY_INITIALIZATION_RADIX=16;" << '\n';
        write_file << "MEMORY_INITIALIZATION_VECTOR=" << '\n';

        while (getline(read_file, line)) {

            std::stringstream line_edit;

            for (size_t i = 0; i <= line.size(); i++) {
                if (i != '\0') line_edit << line[line.size() - i];
            }

            if (read_file.eof()) {
                write_file << line_edit.rdbuf() << ";";
            }
            else {
                write_file << line_edit.rdbuf() << "," << '\n';
            }
        }
    }
    else if (set_option == "mif_format") {
        while (getline(read_file, line)) {

            std::stringstream line_edit;

            for (size_t i = 0; i <= line.size(); i++) {
                if (i != '\0') line_edit << line[line.size() - i];
            }

            if (read_file.eof()) {
                write_file << line_edit.rdbuf();
            }
            else {
                write_file << line_edit.rdbuf() << '\n';
            }
        }
    }
    else {
        while (getline(read_file, line)) {

            std::stringstream line_edit;

            for (size_t i = 0; i <= line.size(); i++) {
                if (i != '\0') line_edit << line[line.size() - i];
            }

            if (read_file.eof()) {
                write_file << line_edit.rdbuf();
            }
            else {
                write_file << line_edit.rdbuf() << '\n';
            }
        }
    }

    std::cout << "Done" << std::endl;
    read_file.close();
    write_file.close();
    


    return 0;
}