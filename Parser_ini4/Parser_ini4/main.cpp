#include <iostream>
#include <fstream>
#include <exception>
#include "Parser_ini.h"
#include "Menu.h"

int main() {
    const std::string filename = "example.ini";
    ParserIni parser(filename);

    //try {
    //    // чтение файла
    //    parser.readFile();

    //    // обработка данных
    //    parser.processLines();

    //    // перенос данных в клас конфигуратор ini
    //    parser.transferToConfig();

    //    // вывод данных в консоль из класса конфигуратора
    //    std::cout << "Обработанные данные:\n";
    //    printConfigData(parser.config);

    //    // получение данных var3 из [Section1]
    //    std::string var3_value = parser.config.getVariable("Section1", "var3");
    //    if (var3_value != "Переменная не найдена") {
    //        std::cout << "перменная var3 в [Section1]: " << var3_value << "\n";
    //    }
    //    else {
    //        std::cerr << "var3 не найден в [Section1].\n";
    //    }

    //    // добавление значений Vid=1080 в [Section4]
    //    parser.config.addVariable("Section3", "Vid");
    //    parser.config.assignValue("Section4", "Vid", "1080");

    //    // сохранение измененного файла
    //    std::ofstream outFile(filename);
    //    if (!outFile.is_open()) {
    //        throw std::runtime_error("Не удалось открыть файл для записи");
    //    }
    //    const auto& sections = parser.config.getSections();
    //    for (const auto& [section, variables] : sections) {
    //        outFile << "[" << section << "]\n";
    //        for (const auto& [variable, valuePair] : variables) {
    //            outFile << variable << " = " << valuePair.first << "\n";
    //        }
    //        outFile << "\n";
    //    }
    //    outFile.close();
    //    std::cout << "Файл сохранен.\n";
    //}
    try {
        
        Menu menu(filename);  // Инициализация меню filename

        menu.displayMenu();  // запуск меню
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    

    return 0;
}