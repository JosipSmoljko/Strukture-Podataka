#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
    char name[50];
    char surname[50];
    int birthYear;
    Position next;
}Person;

Position createPerson(char* name, char* surname, int birthYear);
Position findLast(Position head);
Position findLast(Position head);
Position findBefore(Position head, char* surname);
int insertAfter(Position _position, Position newPerson);
int prependList(Position head, char* name, char* surname, int birhYear);
int appendList(Position head, char* name, char* surname, int birthYear);
int findByLastName(Position first, char* surname);
int printList(Position first);
int deleteElement(Position head, char* surname);

int main(int argc, char** argv)
{
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    Position p = &head;
    Position temp = NULL;

    Position p1, p2, p3;

    p1 = createPerson("name1", "surname1", 0001);
    p2 = createPerson("name2", "surname2", 0002);
    p3 = createPerson("name3", "surname3", 0003);

    insertAfter(p, p1);
    insertAfter(p1, p2);
    insertAfter(p2, p3);

    prependList(p, "name4", "surname4", 0004);
    appendList(p, "name5", "surname5", 0005);
    printList(p->next);
    printf("\n");

    temp = findByLastName(p->next, "surname5");
    printList(temp);
    printf("\n");

    deleteElement(p, "surname2");
    printList(p->next);

    return EXIT_SUCCESS;
}


int insertAfter(Position _position, Position newPerson)
{
    newPerson->next = _position->next;
    _position->next = newPerson;

    return EXIT_SUCCESS;
}

Position createPerson(char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson) {
        perror("Can't allocate memory! \n");
        return -1;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

Position findLast(Position head)
{
    Position temp = NULL;
    temp = head;

    while (temp->next!=NULL)
    {
        temp = temp->next;
    }
    return temp;
}

int prependList(Position head, char* name, char* surname, int birhYear)
{
    Position newPerson = NULL;
    newPerson = createPerson(name, surname, birhYear);
    if (!newPerson) {
        return -1;
    }
    insertAfter(head, newPerson);

    return EXIT_SUCCESS;
}

int appendList(Position head, char* name, char* surname, int birthYear)
{
    Position newPerson = NULL;
    Position last = NULL;
    newPerson = createPerson(name, surname, birthYear);
    if (!newPerson) {
        return -1;
    }
    last = findLast(head);
    insertAfter(last, newPerson);

    return EXIT_SUCCESS;
}

int findByLastName(Position first, char* surname)
{
    Position temp = first;

    while (temp)
    {
        if (strcmp(temp->surname, surname) == 0) {

            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

int printList(Position first)
{
    Position temp = first;

    while(temp)
    {
        printf("Name: %s, Last name: %s, Birth year: %d \n",
             temp->name, temp->surname, temp->birthYear);
        temp=temp->next;
    }

    return EXIT_SUCCESS;
}

Position findBefore(Position head, char* surname)
{
    Position before = head;

    while (before->next != NULL && strcmp(before->next->surname, surname) != 0) {

        before = before->next;
    }

    if(before->next != NULL)
        return before;
    else return NULL;
}
int deleteElement(Position head, char* surname)
{
    Position toDelete = head;
    Position before = findBefore(toDelete, surname);

    if (before == NULL)
    {
        perror("There is no person with this surname! \n");
        return -1;
    }
    else{
        toDelete = before->next;
        before->next = toDelete->next;
        free(toDelete);
    }
    return EXIT_SUCCESS;
}



