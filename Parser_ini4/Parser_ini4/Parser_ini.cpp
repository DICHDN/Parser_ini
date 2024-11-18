#include "Parser_ini.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string>

ParserIni::ParserIni(const std::string& filename) : filename(filename) {}

void ParserIni::readFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    std::string line;
    while (std::getline(file, line)) {
        processedLines.push_back(line);
    }

    file.close();
    std::cout << "Фаил прочтен, количество строк: " << processedLines.size() << "\n";  // для проверки всё ли прочитано можно открыть фаил в Notepad++  там есть индексы строк
}

void ParserIni::backupFile() const {
    std::filesystem::copy(filename, filename + ".bac", std::filesystem::copy_options::overwrite_existing);
    std::cout << "Backup создан: " << filename + ".bac" << "\n";  
}

std::string removeAfterChar(const std::string& str, char ch) {
    // Ищем позицию первого вхождения символа ch
    size_t pos = str.find(ch);

    // Если символ найден, мы создаем новую строку до него
    if (pos != std::string::npos) {
        return str.substr(0, pos); // Обрезаем строку до найденного символа
    }

    // Если символ не найден, возвращаем оригинальную строку
    return str;
}

void ParserIni::processLines() {
    try {
        for (int i = 0; i < processedLines.size() - 1;++i) {
            // Удаление комментариев
            std::string line = processedLines[i];
            line = removeAfterChar(line, ';');
            processedLines[i] = line;
            // Удаление пробелов в начале и конце строки
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); }));
            line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), line.end());

            // Если строка пустая после удаления комментариев и пробелов, пропускаем ее
            if (line.empty()) {
                continue;
            }

            // Если строка содержит '=', обрабатываем дальше
            if (line.find('=') != std::string::npos) {
                size_t equalsPos = line.find('=');
                std::string varName = line.substr(0, equalsPos);
                std::string varValue = line.substr(equalsPos + 1);

                // Удаляем пробелы вокруг имени переменной и значения
                varName.erase(varName.find_last_not_of(' ') + 1);
                varName.erase(0, varName.find_first_not_of(' '));
                varValue.erase(varValue.find_last_not_of(' ') + 1);
                varValue.erase(0, varValue.find_first_not_of(' '));
                line = varName + "=" + varValue;
            }
        }

        // Удаление пустых строк (после обработки)
        processedLines.erase(
            std::remove_if(processedLines.begin(), processedLines.end(), [](const std::string& s) { return s.empty(); }),
            processedLines.end()
        );
    }
    catch (const std::exception& e) {
        std::cerr << "Обнаружено исключение в processLines: " << e.what() << "\n";
        throw;  // Переброс исключения, чтобы оно было замечено в основном коде
    }
    catch (...) {
        std::cerr << "Неизвестное исключение в processLines\n";
        throw;
    }
}



void ParserIni::transferToConfig() {
    std::string currentSection;

    for (const auto& line : processedLines) {
        // Проверяем, является ли строка секцией
        if (!line.empty() && line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
            //std::cout << "Определен раздел: " << currentSection << "\n";
            // Добавляем секцию, если она не существует
            if (!config.getSections().count(currentSection)) {
                config.addSection(currentSection);
                //std::cout << "Добавлен раздел: " << currentSection << "\n";  // Отладочное сообщение
            }
        }
        // Если строка содержит переменную
        else if (!line.empty()) {
            size_t equPos = line.find('=');
            if (equPos != std::string::npos) {
                std::string varName = line.substr(0, equPos);
                std::string varValue = line.substr(equPos + 1);

                // Удаляем пробелы вокруг имени переменной и значения
                varName.erase(varName.find_last_not_of(' ') + 1);
                varName.erase(0, varName.find_first_not_of(' '));
                varValue.erase(varValue.find_last_not_of(' ') + 1);
                varValue.erase(0, varValue.find_first_not_of(' '));

                // Убедимся, что секция существует
                if (!currentSection.empty() && config.getSections().count(currentSection)) {
                    // Проверка на существование переменной
                    if (!config.getSections().at(currentSection).count(varName)) {
                        config.addVariable(currentSection, varName);
                        //std::cout << "Добавление переменной: " << varName << " в разделе: " << currentSection << "\n";  // Отладочное сообщение
                    }

                    // Переприсвоение значения переменной
                    config.assignValue(currentSection, varName, removeAfterChar(varValue, ';')); 
                    //std::cout << "Присвоение значения переменной: " << varName << " значения: " << varValue << " в разделе: " << currentSection << "\n";  // Отладочное сообщение
                }
                else {
                    //std::cerr << "Ошибка: Раздел " << currentSection << " Не найден.\n";
                }
            }
            else {
                //std::cerr << "Ошибка: Не верный формат строки (не найден '='): " << line << "\n";
            }
        }
    }
}


void ParserIni::printConfigData(const Config& config) {
    const auto& sections = config.getSections();
    for (const auto& [section, variables] : sections) {
        std::cout << "[" << section << "]\n";
        for (const auto& [variable, valuePair] : variables) {
            std::cout << variable << " = " << valuePair.first << "\n";
        }
        std::cout << "\n";
    }
}

void ParserIni::printProcessedLines() const {
    for (const auto& line : processedLines) {
        std::cout << line << "\n";
    }
}