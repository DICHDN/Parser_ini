#include "Lib_ini.h"
#include <sstream>
#include <iostream>

// Добавить раздел
void Config::addSection(const std::string& sectionName) {
    configData[sectionName]; // просто инициализируем новый раздел, если его нет
}

// Добавить переменную в раздел
void Config::addVariable(const std::string& sectionName, const std::string& variableName) {
    if (configData.find(sectionName) != configData.end()) {
        configData[sectionName][variableName] = std::make_pair("", false);
    }
}

// Добавить значение для переменной в разделе и установить флаг false
void Config::addValue(const std::string& sectionName, const std::string& variableName, const std::string& value) {
    if (configData.find(sectionName) != configData.end() &&
        configData[sectionName].find(variableName) != configData[sectionName].end()) {
        configData[sectionName][variableName] = std::make_pair(value, false);
    }
}

// Сменить флаг
void Config::toggleFlag(const std::string& sectionName, const std::string& variableName) {
    if (configData.find(sectionName) != configData.end() &&
        configData[sectionName].find(variableName) != configData[sectionName].end()) {
        configData[sectionName][variableName].second = !configData[sectionName][variableName].second;
    }
}

// Переименовать раздел
void Config::renameSection(const std::string& oldName, const std::string& newName) {
    if (configData.find(oldName) != configData.end()) {
        configData[newName] = std::move(configData[oldName]);
        configData.erase(oldName);
    }
}

// Переименовать переменную
void Config::renameVariable(const std::string& sectionName, const std::string& oldName, const std::string& newName) {
    if (configData.find(sectionName) != configData.end() &&
        configData[sectionName].find(oldName) != configData[sectionName].end()) {
        configData[sectionName][newName] = std::move(configData[sectionName][oldName]);
        configData[sectionName].erase(oldName);
    }
}

// Присвоить значение для переменной и установить флаг true
void Config::assignValue(const std::string& sectionName, const std::string& variableName, const std::string& value) {
    if (configData.find(sectionName) != configData.end() &&
        configData[sectionName].find(variableName) != configData[sectionName].end()) {
        configData[sectionName][variableName] = std::make_pair(value, true);
    }
}

// Найти раздел и вывести список переменных
std::string Config::findSection(const std::string& sectionName) const {
    std::ostringstream result;
    if (configData.find(sectionName) != configData.end()) {
        result << "Раздел: " << sectionName << "\n";
        for (const auto& [variable, _] : configData.at(sectionName)) {
            result << "  Переменная: " << variable << "\n";
        }
    }
    else {
        result << "Данные не обнаружены\n";
    }
    return result.str();
}

// Найти переменную
std::string Config::findVariable(const std::string& variableName) const {
    std::ostringstream result;
    bool found = false;
    for (const auto& [section, variables] : configData) {
        if (variables.find(variableName) != variables.end()) {
            result << section << " -> " << variableName << "\n";
            found = true;
        }
    }
    if (!found) {
        result << "Данные не обнаружены\n";
    }
    return result.str();
}

// Найти данные
std::string Config::findData(const std::string& query) const {
    std::ostringstream result;
    bool found = false;

    for (const auto& [section, variables] : configData) {
        bool sectionPrinted = false; // Флаг для проверки, выведен ли раздел

        if (section.find(query) != std::string::npos) {
            result << "Секция: " << section << ".\n";
            found = true;
            sectionPrinted = true; // Помечаем, что раздел уже выведен
        }

        for (const auto& [variable, valuePair] : variables) {
            if (variable.find(query) != std::string::npos || valuePair.first.find(query) != std::string::npos) {
                if (!sectionPrinted) {
                    result << "Секция: " << section << "\n";
                    sectionPrinted = true;
                }
                result << "  Переменная: " << variable << " = " << valuePair.first << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        result << "Данные не обнаружены\n";
    }

    return result.str();
}

// Установить все флаги
void Config::setAllFlags(bool flag) {
    for (auto& [section, variables] : configData) {
        for (auto& [variable, valuePair] : variables) {
            valuePair.second = flag;
        }
    }
}

// Получить имя раздела
std::string Config::getSection(const std::string& sectionName) const {
    if (configData.find(sectionName) != configData.end()) {
        return sectionName;
    }
    else {
        return "Раздел не найден";
    }
}

// Получить значение переменной в конкретном разделе
std::string Config::getVariable(const std::string& sectionName, const std::string& variableName) const {
    if (configData.find(sectionName) != configData.end() &&
        configData.at(sectionName).find(variableName) != configData.at(sectionName).end()) {
        return configData.at(sectionName).at(variableName).first;
    }
    else {
        return "Переменная не найдена";
    }
}

void populateConfig(Config& config) {
    config.addSection("Пример Секции");
    config.addVariable("Пример Секции", "Пример_переменной");
    config.assignValue("Пример Секции", "Пример_переменной", "пример значения");
    std::cout << "Добавлено: 'Пример Секции' с переменной 'Пример_переменной' и присвоение значения 'пример значения'.\n";
}


