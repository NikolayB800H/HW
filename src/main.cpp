#include <iostream>

#include "FileSystem.hpp"

constexpr size_t MAIN_CHOICES_CNT = 6;

static int choiceMenu(int cnt, char const **choices) {
    std::cout << "============== Выбор действия ==============\n";
    for (int itt = 0; itt < cnt; ++itt) {
        std::cout << ' ' << itt + 1 << " - " << choices[itt] << '\n';
    }
    std::cout << ">> Для выбора операции введите число от 1 до "
              << cnt << "\n<< ";
    int resp;
    std::cin >> resp;
    std::cin.clear();
    std::cin.ignore(1, '\n');
    return resp;
}

static bool formOk(std::string const &date) {
    if (date.size() != 8 || (date[2] != '.' || date[5] != '.')) {
        return false;
    }
    for (int8_t i = 0; i < 3; ++i) {
        for (int8_t j = 0; j < 2; ++j) {
            if (!isdigit(date[i * 3 + j])) {
                return false;
            }
        }
    }
    return true;
}

static void addFileDialog(FileSystem &fs) {
    std::string name;
    std::string date;
    std::cout << ">> Пожалуйста, введите имя создания нового файла:\n<< ";
    getline(std::cin, name, '\n');
    std::cout << ">> Теперь введите дату (YY.MM.DD):\n<< ";
    std::cin >> date;
    if (!formOk(date)) {
        std::cout << ">> Формат введённой даты ошибочен, отмена операции.\n";
        return;
    }
    fs.add(FileSystem::File(name, date));
}

static void printFilesDialog(FileSystem &fs) {
    std::cout << ">> Все файлы:\n" << fs << std::endl;
}

static void touchFileDialog(FileSystem &fs) {
    std::string name;
    std::cout << ">> Пожалуйста, введите имя искомого файла:\n<< ";
    std::cin >> name;
    try {
        std::cout << fs.touch(name) << std::endl;
    } catch(std::string e) {
        std::cout << e << std::endl;
    }
}

static void deleteFilesDialog(FileSystem &fs) {
    std::string date;
    std::cout << ">> Пожалуйста, введите дату устаревания (YY.MM.DD):\n<< ";
    std::cin >> date;
    fs.erase(date);
}

static void printPopularDialog(FileSystem &fs) {
    std::cout << ">> " << fs.getMostPopular() << std::endl;
}

int main() {
    FileSystem fs;
    static char const *mainChoices[] = {
        "добавление файла",
        "вывод списка файлов",
        "доступ к файлу по имени",
        "удаление старых файлов",
        "вывод популярного файла",
        "заврешение работы"
    };
    bool continueRun = true;
    while (continueRun) { 
        switch (choiceMenu(MAIN_CHOICES_CNT, mainChoices)) {
            case 1: addFileDialog(fs); break;
            case 2: printFilesDialog(fs); break;
            case 3: touchFileDialog(fs); break;
            case 4: deleteFilesDialog(fs); break;
            case 5: printPopularDialog(fs); break;
            case 6: continueRun = false; break;
            default: std::cout << ">> Недопустимый номер операции"
                               << std::endl;
        }
    }
    return 0;
}
