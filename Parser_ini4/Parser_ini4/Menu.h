#ifndef MENU_H
#define MENU_H

#include "Parser_ini.h"

class Menu {
public:
    Menu(const std::string& filename);

    void displayMenu();
    ~Menu() {}
private:
    void editMenu();
    void viewOriginalFile();
    void viewProcessedLines();
    void editSections();
    void editVariables();
    void editValues();
    void addSection();
    void addVariable();
    void saveToFile();
    void search();

    ParserIni parser;
};
#endif // MENU_H