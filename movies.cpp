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

    if (list.head == nullptr || list.head->next == nullptr)
    {
        return;
    }

    // Sort the nodes recursively
    list.head = mergeSortRecursive(list.head);

    // Re-anchor the tail pointer and clean up the head's prev pointer
    list.head->prev = nullptr;
    Node* current = list.head;
    while (current->next != nullptr) 
    {
        current = current->next;
    }
    list.tail = current;
    
}

//helper func for mergesort
static void splitList(Node* head, Node** front, Node** back)
{
    if (head == nullptr || head->next == nullptr)
    {
        *front = head;
        *back = nullptr;
        return;
    }

    Node* slow = head;
    Node* fast = head->next;

    //find midpoint of list
    while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
    *front = head;
    *back = slow->next;

    slow->next->prev = nullptr;
    slow->next = nullptr;
}

//helper func for mergesort
static Node* sortedMerge(Node* a, Node* b)
{
    if ( a == nullptr) return b;
    if (b == nullptr) return a;

    Node* result = nullptr;

    //make comparison
    if (comesBefore(a->data, b->data) || !comesBefore(b->data, a->data))
    {
        result = a;
        result->next = sortedMerge(a->next, b);
        if (result->next != nullptr)
        {
            result->next->prev = result;
        }
        result->prev = nullptr;
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next);
        if (result->next != nullptr)
        {
            result->next->prev = result;
        }
        result->prev = nullptr;
    }
    return result;
}

static Node* mergeSortRecursive(Node* head)
{
    //base case: list is empty
    if (head == nullptr || head->next == nullptr) 
    {
        return head;
    }

    Node* front = nullptr;
    Node* back = nullptr;

    //Split CURRENT list into two halves
    splitList(head, &front, &back);

    //Recursively sort both halves
    front = mergeSortRecursive(front);
    back = mergeSortRecursive(back);

    //Merge the sorted halves back together
    return sortedMerge(front, back);   
}


void removeDuplicates(MovieList& list) {
  //base case: return unedited list (0 or 1 element)
    if (list.head == nullptr || list.head->next == nullptr)
        return;

    Node* current = list.head;

    while (current->next != nullptr)
    {
        Node* nextNode = current->next;

        //compare all data fields to determine duplicates
         if (current->data.year == nextNode->data.year &&
            current->data.title == nextNode->data.title &&
            current->data.actor == nextNode->data.actor)
         {
            Node* dupe = nextNode;
            current->next = dupe->next;

             if (dupe->next != nullptr)
             {
                 dupe->next->prev = current;
             }
             else
             {
                 list.tail = current;
             }

             delete dupe;
             list.size--;
         }
         else
         {
             current = current->next;
         }
    }
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
