#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <utility>
#include <vector>

class Config {
public:
    
    // Добавить раздел
    void addSection(const std::string& sectionName);

    // Добавить переменную в раздел
    void addVariable(const std::string& sectionName, const std::string& variableName);

    // Добавить значение для переменной в разделе и установить флаг false
    void addValue(const std::string& sectionName, const std::string& variableName, const std::string& value);

    // Сменить флаг
    void toggleFlag(const std::string& sectionName, const std::string& variableName);

    // Переименовать раздел
    void renameSection(const std::string& oldName, const std::string& newName);

    // Переименовать переменную
    void renameVariable(const std::string& sectionName, const std::string& oldName, const std::string& newName);

    // Присвоить значение для переменной и установить флаг true
    void assignValue(const std::string& sectionName, const std::string& variableName, const std::string& value);

    // Найти раздел и вывести список переменных
    std::string findSection(const std::string& sectionName) const;

    // Найти переменную
    std::string findVariable(const std::string& variableName) const;

    // Найти данные
    std::string findData(const std::string& query) const;

    // Установить все флаги
    void setAllFlags(bool flag);

    // Получить имя раздела
    std::string getSection(const std::string& sectionName) const;

    // Получить значение переменной в конкретном разделе
    std::string getVariable(const std::string& sectionName, const std::string& variableName) const;


    // Для сохранения инкапсуляци
    const std::map<std::string, std::map<std::string, std::pair<std::string, bool>>>& getSections() const {
        return configData;
    }
    ~Config() {}
private:
    std::map<std::string, std::map<std::string, std::pair<std::string, bool>>> configData;
};

#endif // CONFIG_H
