#ifndef LISTNODE_H
#define LISTNODE_H

#include "PCB.h"

class ProcessList;

class ListNode{
private:
    PCB data;
    ListNode* next;
public:
    ListNode(PCB data, ListNode* next = nullptr): data(data), next(next) {}
    ~ListNode() {};

    friend class ProcessList;
};

#endif