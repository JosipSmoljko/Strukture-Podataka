#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128

struct _poly;
typedef struct _poly* position;
typedef struct _poly
{
	int coeff;
	int expo;
	position next;
}poly;

int nameEntry(char* nameOfFile);
int readFile(char* nameOfFile, position head1, position head2);
int multiply(position head1, position head2, position headMultiply);
int add(position head1, position head2, position headSum);
int merge(position nakon, position new);
int DeleteAfter(position element);
int freeMemory(position head);
int print(position first);
int parseString(char* buffer, position head);
position createNew(int expo, int koef, position head);
int sortedInput(position head, position new);
int insertAfter(position after, position new);

int main()
{
	poly head1 = { .coeff = 0,.expo = 0,.next = NULL };
	poly head2 = { .coeff = 0,.expo = 0,.next = NULL };
	poly sum = { .coeff = 0,.expo = 0,.next = NULL };
	poly mul = { .coeff = 0,.expo = 0,.next = NULL };
	char file[MAX_SIZE] = { 0 };

	printf("Name of file: ");
	scanf(" %s", file);

	readFile(file, &head1, &head2);
	add(&head1,&head2,&sum);
	multiply(&head1, &head2, &mul);

	printf("\nSum od two polynomals:\n");
	print(sum.next);

	printf("\nTwo polynomials multiplied:\n");
	print(mul.next);

	freeMemory(&head1);
	freeMemory(&head2);
	freeMemory(&sum);
	freeMemory(&mul);

	return 0;
}

int readFile(char* nameOfFile, position head1, position head2)
{
	FILE* fp = fopen(nameOfFile, "r");
	char buffer[MAX_LINE] = { 0 };
	int status = 0;

	if (!fp)
	{
		perror("Can't open this file!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, fp);
	status = parseString(buffer, head1);
	if (status == 0)
	{
		fgets(buffer, MAX_LINE, pfile);
	}
	else return -1;

	fgets(buffer, MAX_LINE, fp);
	status = parseString(buffer, head2);
	if (status == 0)
	{
		fgets(buffer, MAX_LINE, pfile);
	}
	else return -1;

	fclose(fp);
	return EXIT_SUCCESS;
}

int parseString(char* buffer, position head)
{
	int status = 0, exponent = 0, coeff = 0, num = 0;
	position newElem = NULL;
	char* tempBuffer = buffer;
	while (strlen(tempBuffer) > 0)
	{
		status = sscanf(tempBuffer, " %d %d %n", &coeff, &exponent, &num);
		if (status == 2)
		{
			newElem = createNew(exponent, coeff, head);
		}
		else return -1;
		
		if (!new)
		{
			return -1;
		}

		tempBuffer = tempBuffer + num; 
	}
	return EXIT_SUCCESS;
}

int sortedInput(position head, position new)
{
	position temp = head;
	while (temp->next != NULL && (temp->next->expo) > (new->expo))
	{
		temp = temp->next;
	}

	merge(temp, new);

	return 0;
}
position create(int exponent, int coefficient, position head)
{
	position newElement = NULL; 
	newElement = (position)malloc(sizeof(poly));

	if (!newElement)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->expo = exponent; 
	newElement->coeff = coefficient;

	sortedInput(head, newElement);
	return newElement;
}
int insertAfter(position after, position new)
{
	new->next = after->next;
	after->next = new;

	return 0;
}
int add(position head1, position head2, position headSum)
{
	position first = head1->next;
	position second = head2->next;
	position result = headSum;
	position temp = NULL;
	position new = NULL;

	while (first != NULL && second != NULL)
	{
		if (first->expo == second->expo)
		{
			new=createNew(first->expo, first->coeff + second->coeff, result);
			if (!new)
			{
				return -1;
			}
		
			first = first->next;
			second = second->next;
		}
		else if (first->expo > second->expo)
		{
			new=createNew(second->expo, second->coeff, result);
		
			second = second->next;
		}
		else
		{
			new=createNew(first->expo, first->coeff, result);
	
			first = first->next;
		}
	}

	if (first == NULL)
	{
		temp = second;
	}

	if (second == NULL)
	{
		temp = first;
	}

	while (temp != NULL)
	{
		createNew(temp->expo, temp->coeff, result);
		temp = temp->next;
	}

	return 0;
}

int multiply(position head1,position head2,position headMultiply)
{
	position first = NULL;
	position second = NULL;
	position result = headMultiply;

	for (first = head1->next; first != NULL; first = first->next)
	{
		for (second = head2->next; second != NULL; second = second->next)
		{
			position new = createNew(first->expo + second->expo, first->coeff * second->coeff, result);
			if (!new)
			{
				return -1;
			}
		}
	}
	return 0;
}

int merge(position after,position new)
{
	if(after->next==NULL || after->next->expo!= new->expo)
	{
		insertAfter(after, new);
	}
	else
	{
		int coeff = after->next->coeff + new->coeff;
		if (coeff == 0)
		{
			DeleteAfter(after);
		}
		else
		{
			after->next->coeff = coeff;
		}
		free(new);
	}
	return 0;
}

int DeleteAfter(position element)
{
	position toDelete=element->next;
	element->next = toDelete->next;
	free(toDelete);

	return 0;
}
int freeMemory(position head)
{
	position temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}

int print(position first)
{
	position temp = first;
	printf("f(x) = ");
	while (temp!=NULL)
	{
		if (temp->next== NULL)
		{
			printf("%dx^(%d)", temp->koef, temp->expo);
		}
		else
		{
			printf("%dx^(%d)", temp->koef, temp->expo);
			printf("+");
		}
		temp = temp->next;
	}
	return 0;
}
