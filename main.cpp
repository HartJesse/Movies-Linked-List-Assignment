// main.cpp
//
// Write main() in this file. It must:
//   - read the command line (Section 7 of the handout),
//   - read and parse the input file, calling appendNode once per line (Section 6),
//   - sort the list, remove duplicates, print the full or filtered list,
//     and free the list (Sections 3, 4, and 8),
//   - print the exact error messages in Section 8 to std::cerr and return 1 on errors.
//
// You may add helper functions in this file. Mark each one `static` and define
// it above the function that uses it. Do not add anything to movies.h.
//
// Allowed headers: <string>, <iostream>, <fstream>, <sstream>,
// <cstring>, <cstdlib>, and "movies.h".

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "movies.h"

// Helper function to trim whitespace, tabs, and Windows carriage returns (\r)
static std::string trim(const std::string& s) 
{
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) 
    {
        return ""; // Empty or all whitespace
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
    // 1. Check command line arguments (Section 7)
    if (argc < 2 || argc > 4) 
    {
        std::cerr << "Usage: ./LinkedList <input_file> [--year <year> | --actor \"<name>\" | --title \"<title>\"]\n";
        return 1;
    }

    std::string filename = argv[1];
    int filterYear = 0;
    std::string filterActor = "";
    std::string filterTitle = "";

    if (argc == 3 || argc == 4) 
    {
        std::string option = argv[2];
        if (argc == 4 && option == "--year") 
        {
            filterYear = std::stoi(argv[3]);
        } 
        else if (argc == 4 && option == "--actor") 
        {
            filterActor = argv[3];
        } 
        else if (argc == 4 && option == "--title") 
        {
            filterTitle = argv[3];
        } 
        else 
        {
            std::cerr << "Error: invalid arguments\n";
            return 1;
        }
    }

    //Open input file and verify it opened
    std::ifstream infile(filename);
    if (!infile.is_open()) 
    {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    MovieList movieList;
    std::string line;

    //Read file line by line
    while (std::getline(infile, line)) 
    {
        //Skip blank lines after trimming
        if (trim(line).empty()) 
        {
            continue;
        }

        //Split line into fields using stringstream
        std::stringstream ss(line);
        std::string yearText, temptitle, tempactor;

        std::getline(ss, yearText, '|');
        std::getline(ss, temptitle, '|');
        std::getline(ss, tempactor);

        //Trim fields and convert year to int
        int year = std::stoi(trim(yearText));
        std::string Title = trim(temptitle);
        std::string Actor = trim(tempactor);

        //Build Movie struct and append to list
        Movie m{year, Title, Actor};
        appendNode(movieList, m);
    }

    infile.close();

    //Process the list, sort, and remove duplicates
    sortList(movieList);
    removeDuplicates(movieList);

    //Output results based on whether a filter was given
    if (argc == 2) 
    {
        printList(movieList);
    } 
    else 
    {
        printFiltered(movieList, filterYear, filterActor, filterTitle);
    }

    //Clean up allocated memory
    clearList(movieList);
    
    return 0;
}
