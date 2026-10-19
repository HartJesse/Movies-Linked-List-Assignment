// movies.cpp
//
// Implement every function declared in movies.h in this file. Each function's
// required behavior is described in Section 2.3 of the handout.
//
// You may add helper functions in this file (for example, a merge function for
// merge sort). Mark each one `static` and define it above the function that
// uses it. Do not add anything to movies.h.
//
// Allowed headers: <string>, <iostream>, <fstream>, <sstream>,
// <cstring>, <cstdlib>, and "movies.h".

#include <iostream>
#include <string>
#include "movies.h"

void appendNode(MovieList& list, const Movie& m) {

    Node* newNode = new Node;
    newNode->data = m;
    newNode->next = nullptr;
    newNode->prev = nullptr;
        
    //case 1: append to empty list
    if (list.head == nullptr)
    {
        list.head = newNode;
        list.tail = newNode
    }
    else
    {
        //case 2: append to end of current list
        list.tail->next = newNode;
        newNode->prev = list.tail;
        list.tail = newNode;
    }
    list.size++;
}

bool comesBefore(const Movie& a, const Movie& b) 
{
    //check if year is correct
    if (a.year != b.year) 
    {
        return a.year < b.year;
    }
    if (a.title != b.title) 
    {
        return a.title < b.title;
    }
    return a.actor < b.actor;
 }

void sortList(MovieList& list) {

    
}

void removeDuplicates(MovieList& list) {
    // TODO
    (void)list;
}

void printList(const MovieList& list) {
    // TODO
    (void)list;
}

void printFiltered(const MovieList& list, int year, const std::string& actor,
                   const std::string& title) 
{
    // TODO
    (void)list;
    (void)year;
    (void)actor;
    (void)title;
}

void clearList(MovieList& list) 
{
    //traverse list using fresh pointers and delete all nodes 
    Node* current = list.head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;    
    }

    //reset list pointers
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}
