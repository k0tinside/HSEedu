#include "ProcessList.h"

ProcessList::ProcessList() : head(nullptr) {}

ProcessList::~ProcessList() {
    ListNode* cur = head;
    while (cur != nullptr) {
        ListNode* nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }
    head = nullptr;
}

bool ProcessList::insert(const PCB& newPCB) {

    ListNode* newNode = new ListNode(newPCB);
    if (head == nullptr) {
        head = newNode;
        return true;
    } else if (head->data.processID > newPCB.processID) {
        newNode->next = head;
        head = newNode;
        return true;
    } else if (head->data.processID == newPCB.processID) {
        delete newNode;
        return false;
    }


    ListNode* cur = head;

    while (cur->next != nullptr) {

        if (cur->next->data.processID == newPCB.processID) {
            
            delete newNode;
            return false;
        }

        if (cur->next->data.processID > newPCB.processID) {
            break;
        }

        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
    return true;
        
}

bool ProcessList::remove(int pid) {
    ListNode* cur = head;
    if (head == nullptr) {
        return false;
    }

    if (head->data.processID == pid) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }

    while (cur->next != nullptr && cur->next->data.processID != pid) {
        cur = cur->next;
    }

    if (cur->next == nullptr) {
        return false;

    } else {
        ListNode* toDelete = cur->next;
        cur->next = cur->next->next;
        delete toDelete;
        return true;
    }

}

void ProcessList::printList() const {
    if (head == nullptr) {
        std::cout << "Список процессов пуст." << std::endl;
        return;
    }

    ListNode* cur = head;
    std::cout << "-----Список активных процессов-----\n";
    
    while (cur != nullptr) {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "ID процесса: " << cur->data.processID << std::endl;
        std::cout << "Имя процесса: " << cur->data.processName << std::endl;
        std::cout << "Состояние процесса: " << cur->data.processStatus << std::endl;
        
        cur = cur->next;
    }
    std::cout << "---------------------------------------" << std::endl;
}