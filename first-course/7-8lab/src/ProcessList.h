#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <iostream>
#include <string>
#include "ListNode.h"

class ProcessList {
private:
    ListNode* head;

public:
    ProcessList();

    bool insert(const PCB& newPCB);
    bool remove(int pid);
    void printList() const;

    ~ProcessList();
};

#endif