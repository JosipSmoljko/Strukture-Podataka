#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE (1024)

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
Position findByLastName(Position first, char* surname);
Position findBefore(Position head, char* surname);
int insertAfter(Position _position, Position newPerson);
int prependList(Position head, char* name, char* surname, int birhYear);
int appendList(Position head, char* name, char* surname, int birthYear);
int printList(Position first);
int deleteElement(Position head, char* surname);
int insertAfterElement(char* sur, Position head, char* name,char* surname,int birthYear);
int insertBeforeElement(char* sur, Position head, char* name, char* surname,int birthYear);
int sortInput(Position head, Position newPerson);
int addToFile(Position head, char* nameOfFile);
int readFromFIle(Position head, char* nameOfFIle);

int main(int argc, char** argv)
{
    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
    Position p = &head;
    Position temp = NULL;

    Position p1, p2, p3;

    p1 = createPerson("name1", "zsurname1", 1);
    p2 = createPerson("name2", "bsurname2", 2);
    p3 = createPerson("name3", "asurname3", 3);

    sortInput(p, p1);
    sortInput(p, p2);
    sortInput(p, p3);
    printList(p->next);
    printf("\n");

    temp = findByLastName(p->next, "zsurname1");
    printList(temp);
    printf("\n");

    addToFile(p, "list.txt");
    readFromFIle(p, "newList.txt");
    printList(p->next);
    printf("\n");

    insertAfterElement("asurname3", p->next,"name6", "surname6", 6);
    deleteElement(p, "bsurname2");
    insertBeforeElement("zsurname1", p, "name7", "surname7", 7);
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

Position findByLastName(Position first, char* surname)
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
int insertAfterElement(char* sur, Position head, char* name,char* surname,int birthYear)
{
    Position givenElement = NULL;
    Position newPerson = NULL;

    givenElement = findByLastName(head, sur);
    if(!givenElement){
        printf("There is no given surname in the list");
        return -1;
    }

    newPerson = createPerson(name, surname, birthYear);
    if(!newPerson){
            perror("Greska");
            return -1;
        }
    else{
            insertAfter(givenElement, newPerson);
        }

    return EXIT_SUCCESS;
}

int insertBeforeElement(char* sur, Position head, char* name, char* surname,int birthYear)
{
    Position newPerson = NULL;
    Position prev = NULL;
    Position temp = NULL;
    temp = head;

    prev = findBefore(temp, sur);
    if(!prev){
        return -1;
    }

    newPerson = createPerson(name, surname, birthYear);
    if(!newPerson){
        perror("error");
        return -1;
    }

    insertAfter(prev, newPerson);
    return EXIT_SUCCESS;
}

int sortInput(Position head, Position newPerson)
{
    Position temp = NULL;
    temp = head;

    if(!temp){
        perror("greska");
        return -1;
    }

	while (temp->next != NULL && strcmp(temp->next->surname, newPerson->surname) < 0)
		temp = temp->next;

	insertAfter(temp, newPerson);
	return EXIT_SUCCESS;
}

int addToFile(Position head, char* nameOfFile)
{
    FILE* fp = NULL;
    Position temp = NULL;
    temp = head;

    fp = fopen(nameOfFile, "w");
    if(!fp){
        perror("Can't open file");
        return -1;
    }
    while(temp->next != NULL){
        fprintf(fp, "%s %s %d\n", temp->next->name, temp->next->surname, temp->next->birthYear);
		temp = temp->next;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int readFromFIle(Position head, char* nameOfFile)
{
    char buff[MAX_LINE] = {0};
    char name[50] = {0};
	char surname[50] = {0};
	int birthYear = 0;
    FILE* fp = NULL;
    Position newPerson = NULL;
    Position temp = head;

    fp = fopen(nameOfFile, "r");
    if(!fp){
        perror("Greska");
        return -1;
    }
    while(feof(fp)==0){

		fgets(buff, MAX_LINE, fp);
		if (sscanf(buff, " %s %s %d", name, surname, &birthYear) == 3)
		{
            newPerson = createPerson(name, surname, birthYear);
			sortInput(head, newPerson);
			temp = temp->next;
		}
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
