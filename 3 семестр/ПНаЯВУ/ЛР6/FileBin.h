#ifndef FILEBIN_H
#define FILEBIN_H

#include "File.h"
#include "List.cpp"
#include "FileExp.h"
#include "Human.h"

template <class T>
class FileBin : public File
{
public:
    FileBin(const std::string& name);
    void writeLinkedList(const List<T>& list);
    void readLinkedList(List<T>& list);
    FileBin<T>& operator<<(const List<T>& list);
    FileBin<T>& operator>>(List<T>& list);
};


#endif

