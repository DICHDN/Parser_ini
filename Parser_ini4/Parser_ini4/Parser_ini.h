#ifndef PARSER_INI_H
#define PARSER_INI_H

#include <vector>
#include <string>
#include "Lib_ini.h"

class ParserIni {
public:
    // Конструктор
    ParserIni(const std::string& filename);

    // Чтение файла
    void readFile();

    // Сохранение файла с расширением .bac
    void backupFile() const;

    // Вывод обработанных строк
    void printProcessedLines() const;

    // Для обработки и последующего хранения обработанных данных
    void processLines();

    // Перенос данных в Config
    void transferToConfig();

    //Для вывода данных хранящихся в Config
    void printConfigData(const Config& config);

    // для сохранения инкапсуляции
    Config& getConfig() {
        return config;
    }
    std::string getFilename() const {
        return filename;
    }
    
    ~ParserIni() {}
private:
    std::string filename;
    std::vector<std::string> processedLines;
    Config config;
};

#endif // PARSER_INI_H