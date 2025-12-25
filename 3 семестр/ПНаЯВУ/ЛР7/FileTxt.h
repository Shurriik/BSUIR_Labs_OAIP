#ifndef FILETXT_H
#define FILETXT_H

#include "File.h"
#include "List.h"
#include "List.cpp"
#include "FileExp.h"
#include "Human.h"

template <class T>
class FileTxt : public File
{
public:
    FileTxt(const std::string& name) : File(name) {};
    void writeLinkedList(const List<T>& list);
    void readLinkedList(List<T>& list);
    FileTxt<T>& operator<<(const List<T>& list);
    FileTxt<T>& operator>>(List<T>& list);
};


#endif

