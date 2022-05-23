#include <fstream>
#include <list>
#include <string>

#include "FileSystem.hpp"

FileSystem::FileSystem() {
}

FileSystem::~FileSystem() {
}

FileSystem::File &FileSystem::touch(std::string const &file_name) {
    for (auto &i : files) {
        if (i.getName() == file_name) {
            ++(i.touches_count);
            return i;
        }
    }
    throw std::string("Файл не найден");
}

FileSystem::File &FileSystem::add(File const &file) {
    files.push_back(file);
    return files.back();
}

void FileSystem::erase(size_t too_old) {
    for (std::list<File>::iterator i = files.begin(); i != files.end();) {
        if (i->getDate() < too_old) {
            files.erase(i);
            i = files.begin();
        } else {
            ++i;
        }
    }
}

FileSystem::File &FileSystem::getMostPopular() {
    File *max = &files.front();
    for (auto &i : files) {
        if (i.getCount() > max->getCount()) {
            max = &i;
        }
    }
    return *max;
}

std::ostream &operator<<(std::ostream &os, FileSystem const &file_system) {
    for (auto &i : file_system.files) {
        os << i << std::endl;
    }
    return os;
}

FileSystem::File::File() : name(""), creation_date(0), touches_count(0) {
}

FileSystem::File::File(std::string const &file_name, size_t creation_date)
    : name(file_name)
    , creation_date(creation_date)
    , touches_count(0) {
}

FileSystem::File::~File() {
}

std::string const &FileSystem::File::getName() const {
    return name;
}

size_t FileSystem::File::getDate() const {
    return creation_date;
}

size_t FileSystem::File::getCount() const {
    return touches_count;
}

std::ostream &operator<<(std::ostream &os, FileSystem::File const &file) {
    os << file.name << '\t' << file.creation_date << '\t' << file.touches_count;
    return os;
}
