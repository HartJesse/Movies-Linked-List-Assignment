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

//create a new node with passed in value(Movie),
//add it to the END of the current linked list, keep track of current list size
void appendNode(MovieList& list, const Movie& m) {

    Node* newNode = new Node;
    newNode->data = m;
    newNode->next = nullptr;
    newNode->prev = nullptr;
        
    //case 1: append to empty list
    if (list.head == nullptr)
    {
        list.head = newNode;
        list.tail = newNode;
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

/*compare two node's data
  sorting by year is priority 1
  else we sort by title of film (alphabetical) priority 2
  else we sort by name of actor (alphabetical) priority 3*/
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

/*helper func for mergesort, */
static void splitList(Node* head, Node** front, Node** back)
{
    //case 1: no list to be split (zero or one node(s))
    if (head == nullptr || head->next == nullptr)
    {
        *front = head; //dereference pointer to access original pointer passed in, point it at head
        *back = nullptr;
        return;
    }

    Node* current = head;
    Node* runner = head->next;

    //find midpoint of list by traversing with two pointers 
    //one moving twice as fast as the other
    while (runner != nullptr)
        {
            runner = runner->next;
            if (runner != nullptr)
            {
                current = current->next;
                runner = runner->next;
            }
        }
    *front = head;
    *back = current->next;

    current->next->prev = nullptr;
    current->next = nullptr;
}

//helper func for mergesort
static Node* sortedMerge(Node* leftSide, Node* rightSide)
{
    if ( leftSide == nullptr) return rightSide;
    if (rightSide == nullptr) return leftSide;

    Node* result = nullptr;

    //make comparison must handle duplicate case here during soring sorting
    if (comesBefore(leftSide->data, rightSide->data) || !comesBefore(rightSide->data, leftSide->data))
    {
        result = leftSide;
        result->next = sortedMerge(leftSide->next, rightSide);
        if (result->next != nullptr)
        {
            result->next->prev = result;
        }
        result->prev = nullptr;
    }
    else
    {
        result = rightSide;
        result->next = sortedMerge(leftSide, rightSide->next);
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

//sorting handled via mergesort helpers, clean up head and tail pointers 
//after returning from sorting
void sortList(MovieList& list) {

    if (list.head == nullptr || list.head->next == nullptr)
    {
        return;
    }

    // Sort the nodes recursively via mergesort
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
    Node* current = list.head;
    while (current != nullptr) 
    {
        std::cout << current->data.year << " | " 
                  << current->data.title << " | " 
                  << current->data.actor << "\n";
        current = current->next;
    }
}

void printFiltered(const MovieList& list, int year, const std::string& actor,
                   const std::string& title) 
{
    Node* current = list.head;
    int matchCount = 0;

    //traverse list find films matching filter
    while (current != nullptr)
    {
        bool match = false;

        //check if current movie lands on any of the possible filters
        if (year != 0 && current->data.year == year)
        {
            match = true;
        }
        else if (!actor.empty() && current->data.actor == actor)
        {
            match = true;
        }
        else if (!title.empty() && current->data.title == title)
        {
            match = true;        
        }
        
        //print the match we find
        if (match)
        {
            std::cout << current->data.year << " | " 
                      << current->data.title << " | " 
                      << current->data.actor << "\n";
            matchCount++;
        }

        current = current->next;
    }

    //filter produced zero results
    if (matchCount == 0)
    {
        std::cout << "No results\n";
    }
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
