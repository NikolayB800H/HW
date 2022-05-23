#pragma once

#include <fstream>
#include <list>
#include <string>

class FileSystem {
public:
    class File {
    public:
        File();
        File(std::string const &file_name, size_t creation_date);
        ~File();
        std::string const &getName() const;
        size_t getDate() const;
        size_t getCount() const;
        friend std::ostream &operator<<(std::ostream &os, File const &file);
    private:
        std::string name;
        size_t creation_date;
        size_t touches_count;
        friend FileSystem;
    };
    FileSystem();
    ~FileSystem();
    File &touch(std::string const &file_name);
    File &add(File const &file);
    void erase(size_t too_old);
    File &getMostPopular();
    friend std::ostream &operator<<(std::ostream &os, FileSystem const &file_system);
private:
    std::list<File> files;
};
