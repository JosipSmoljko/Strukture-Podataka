#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX_LENGTH (50)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	double number;
	Position next;
}Element;

Position CreateElement(double number);
int InputFileName(char* nameOfFile);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int DeleteAll(Position position);
int Push(Position head, double number);
int Pop(double* Resultdestination, Position head);
int PerformOperation(Position head, char operation);
char* ReadFromFile(char *nameOfFile);
int CalculatePostfixFromFile(double* Resultdestination, char* nameOfFile);

int main(int argc, char* argv[])
{
	char nameOfFile[MAX_LENGTH] = { 0 };
	double postfixResult = 0;
	int status = 0;

	InputFileName(nameOfFile);

	status = CalculatePostfixFromFile(&postfixResult,nameOfFile);

    if(!status)
    {
        printf("Result: %.1lf",postfixResult);
    }

    return EXIT_SUCCESS;
}
Position CreateElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Element));
	if (!newElement)
	{
		perror("Can't allocate memory! \n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);
	if (!newElement)
		return -1;

	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;
	if (!temp)
		return -1;

	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* destination, Position head)
{
	Position first = head->next;
	if (!first)
	{
		printf("Postfix not valid! Please check your file.\n");
		return -1;
	}

	*destination = first->number;

	DeleteAfter(head);
	return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation)
{
	double operand2 = 0;
	double operand1 = 0;

	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;
	double result = 0;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operation)
	{
	case '+':
	{
		result = operand1 + operand2;
		break;
	}
	case '-':
	{
		result = operand1 - operand2;
		break;
	}
	case '*':
	{
		result = operand1 * operand2;
		break;
	}
	case '/':
	{
		if (operand2 == 0)
		{
			printf("Cannot divide with zero\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	}
	default:
	{
		printf("This operation is not supported yet \n");
		return -4;
	}
	}

	Push(head, result);

	return EXIT_SUCCESS;
}

char* ReadFromFile(char *nameOfFile)
{
    FILE *fp = NULL;
    int fileLength;
    char *buffer = NULL;

    fp = fopen(nameOfFile, "rb");

    if(!fp){
        perror("Can't open file!\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    fileLength = ftell(fp);
    buffer = (char*)calloc(fileLength+1, sizeof(char));

    if(!buffer){
        perror("Can't allocate memory!\n");
        return NULL;
    }
    rewind(fp);

    fread(buffer, sizeof(char), fileLength, fp);
    printf("buffer: %s\n", buffer);
    fclose(fp);
    return buffer;
}

int CalculatePostfixFromFile(double* destination, char* nameOfFile)
{
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	char operation = 0;
	double number = 0;
	int status = 0;
	Element head = { .number = 0, .next = NULL };

	buffer = ReadFromFile(nameOfFile);
    if(!buffer){
        return -1;
    }
    currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);

		if (status == 1)
		{
			Push(&head, number);
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);

				while (head.next != NULL)
					DeleteAfter(&head);

				return -1;
			}
			currentBuffer += numBytes;
		}
	}
	free(buffer);

	if (head.next->next)
	{
		printf("Postfix not valid! Please check your file.\n");
		return EXIT_FAILURE;
	}

	Pop(destination, &head);

	return EXIT_SUCCESS;
}

int InputFileName(char* nameOfFile)
{
	printf("Enter the file name: \n");
	scanf(" %s", nameOfFile);

	return EXIT_SUCCESS;
}
