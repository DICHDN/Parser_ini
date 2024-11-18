#include "Menu.h"
#include <iostream>
#include <fstream>
#include <limits>

Menu::Menu(const std::string& filename) : parser(filename) {
    parser.readFile();
    parser.transferToConfig();
}

void Menu::displayMenu() {
    int choice;
    do {
        std::cout << "\n===== Редактор INI Файлов =====\n";
        std::cout << "1. Просмотреть оригинальный файл\n";
        std::cout << "2. Просмотреть обработанные данные\n";
        std::cout << "3. Редактировать\n";
        std::cout << "4. Сохранить в файл\n";
        std::cout << "5. Поиск\n";
        std::cout << "0. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода

        switch (choice) {
        case 1:
            viewOriginalFile();
            break;
        case 2:
            viewProcessedLines();
            break;
        case 3:
            editMenu();
            break;
        case 4:
            saveToFile();
            break;
        case 5:
            search();
            break;
        case 0:
            std::cout << "Выход...\n";
            break;
        default:
            std::cout << "Неверный выбор! Пожалуйста, попробуйте еще раз.\n";
            break;
        }
    } while (choice != 0);
}

void Menu::editMenu() {
    int choice;
    do {
        std::cout << "\n===== Редактирование =====\n";
        std::cout << "1. Редактировать разделы\n";
        std::cout << "2. Редактировать переменные\n";
        std::cout << "3. Редактировать значения переменных\n";
        std::cout << "4. Добавить раздел\n";
        std::cout << "5. Добавить переменную\n";
        std::cout << "0. Назад\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода

        switch (choice) {
        case 1:
            editSections();
            break;
        case 2:
            editVariables();
            break;
        case 3:
            editValues();
            break;
        case 4:
            addSection();
            break;
        case 5:
            addVariable();
            break;
        case 0:
            return;
        default:
            std::cout << "Неверный выбор! Пожалуйста, попробуйте еще раз.\n";
            break;
        }
    } while (choice != 0);
}

void Menu::editSections() {
    //parser.transferToConfig();
    std::string oldName, newName;
    bool sectionExists = false;
    do {
        std::cout << "Введите имя раздела для переименования: ";
        std::getline(std::cin, oldName);

        if (parser.getConfig().getSection(oldName) != "Раздел не найден") {
            sectionExists = true;
        }
        else {
            std::cout << "Раздел не найден! Доступные разделы:\n";
            for (const auto& [section, _] : parser.getConfig().getSections()) {
                std::cout << section << "\n";
            }
            std::cout << "Пожалуйста, попробуйте еще раз.\n";
        }
    } while (!sectionExists);

    std::cout << "Введите новое имя для раздела: ";
    std::getline(std::cin, newName);
    parser.getConfig().renameSection(oldName, newName);
}

void Menu::editVariables() {
    //parser.transferToConfig();
    std::string sectionName, oldName, newName;
    bool sectionExists = false, variableExists = false;

    do {
        std::cout << "Введите имя раздела: ";
        std::getline(std::cin, sectionName);

        if (parser.getConfig().getSection(sectionName) != "Раздел не найден") {
            sectionExists = true;
        }
        else {
            std::cout << "Раздел не найден! Доступные разделы:\n";
            for (const auto& [section, _] : parser.getConfig().getSections()) {
                std::cout << section << "\n";
            }
            std::cout << "Пожалуйста, попробуйте еще раз.\n";
        }
    } while (!sectionExists);

    do {
        std::cout << "Введите имя переменной для переименования: ";
        std::getline(std::cin, oldName);

        if (parser.getConfig().getVariable(sectionName, oldName) != "Переменная не найдена") {
            variableExists = true;
        }
        else {
            std::cout << "Переменная не найдена! Доступные переменные в разделе " << sectionName << ":\n";
            for (const auto& [variable, _] : parser.getConfig().getSections().at(sectionName)) {
                std::cout << variable << "\n";
            }
            std::cout << "Пожалуйста, попробуйте еще раз.\n";
        }
    } while (!variableExists);

    std::cout << "Введите новое имя для переменной: ";
    std::getline(std::cin, newName);
    parser.getConfig().renameVariable(sectionName, oldName, newName);
}

void Menu::editValues() {
    //parser.transferToConfig();
    std::string sectionName, variableName, newValue;
    bool sectionExists = false, variableExists = false;

    do {
        std::cout << "Введите имя раздела: ";
        std::getline(std::cin, sectionName);

        if (parser.getConfig().getSection(sectionName) != "Раздел не найден") {
            sectionExists = true;
        }
        else {
            std::cout << "Раздел не найден! Доступные разделы:\n";
            for (const auto& [section, _] : parser.getConfig().getSections()) {
                std::cout << section << "\n";
            }
            std::cout << "Пожалуйста, попробуйте еще раз.\n";
        }
    } while (!sectionExists);

    do {
        std::cout << "Введите имя переменной: ";
        std::getline(std::cin, variableName);

        if (parser.getConfig().getVariable(sectionName, variableName) != "Переменная не найдена") {
            variableExists = true;
        }
        else {
            std::cout << "Переменная не найдена! Доступные переменные в разделе " << sectionName << ":\n";
            for (const auto& [variable, _] : parser.getConfig().getSections().at(sectionName)) {
                std::cout << variable << "\n";
            }
            std::cout << "Пожалуйста, попробуйте еще раз.\n";
        }
    } while (!variableExists);

    std::cout << "Введите новое значение для переменной: ";
    std::getline(std::cin, newValue);
    parser.getConfig().assignValue(sectionName, variableName, newValue);
}

void Menu::search() {
    std::string query;
    std::cout << "Введите поисковый запрос: ";
    std::getline(std::cin, query);

    std::string result = parser.getConfig().findData(query);
    if (!result.empty()) {
        std::cout << "Результат поиска:\n" << result << "\n";
    }
    else {
        std::cout << "Данные не найдены.\n";
    }
}

void Menu::saveToFile() {
    std::ofstream file(parser.getFilename());
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для записи\n";
        return;
    }

    const auto& sections = parser.getConfig().getSections();
    for (const auto& [section, variables] : sections) {
        file << "[" << section << "]\n";
        for (const auto& [variable, valuePair] : variables) {
            file << variable << "=" << valuePair.first << "\n";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Изменения сохранены в файл.\n";
}

void Menu::viewOriginalFile() {
    std::ifstream file(parser.getFilename());
    std::string line;
    std::cout << "\nДанные исходного файла:\n";
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();
}

void Menu::viewProcessedLines() {
    std::cout << "\nОбработанные данные:\n";
    parser.printConfigData(parser.getConfig());
}

void Menu::addSection() {
    std::string sectionName;
    std::cout << "Введите имя раздела для добавления: ";
    std::getline(std::cin, sectionName);
    parser.getConfig().addSection(sectionName);
}

void Menu::addVariable() {
    std::string sectionName, variableName, value;
    std::cout << "Введите имя раздела: ";
    std::getline(std::cin, sectionName);
    std::cout << "Введите имя переменной: ";
    std::getline(std::cin, variableName);
    std::cout << "Введите значение переменной: ";
    std::getline(std::cin, value);
    parser.getConfig().addVariable(sectionName, variableName);
    parser.getConfig().addValue(sectionName, variableName, value);
}