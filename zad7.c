#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024

struct _cvor;
typedef struct _cvor* position;
typedef struct _cvor
{
	char name[MAX_SIZE];
	position sibling;
	position child;
}cvor;

struct _stog;
typedef struct _stog* StogPosition;
typedef struct _stog
{
	position VanjskiDirektorij;
	StogPosition next;
}stog;

position MakeDirectory(char*, position );
position InsertDirectory(position, position);
int PushToStog(StogPosition, position);
int PopFromStog(StogPosition);
StogPosition FindLast(StogPosition);
StogPosition FindBefore(StogPosition);
position ChangeDirectory(StogPosition, position, char*);
int DisplayInformation(position);
int Exit(position);
int PrintCurrentDirectories(StogPosition);
int Menu(position, StogPosition);

int main()
{
	cvor root;
	stog head;

	strcpy(root.name, "C:");
	root.child = NULL;
	root.sibling = NULL;

	head.VanjskiDirektorij = NULL;
	head.next = NULL;

	PushToStog(&head, &root);
	Menu(&root, &head);

	return 0;

}
int Menu(position curr, StogPosition head)
{
	position first = curr;
	char name[MAX_LINE] = { 0 };
	char command[MAX_LINE] = { 0 };
	char line[MAX_LINE] = { 0 };
	PrintCurrentDirectories(head);

	while (1)
	{
		fgets(line, MAX_LINE, stdin);
		sscanf(line, "%s %s", command, name);

		if (!strcmp(command, "md"))
		{
			curr = MakeDirectory(name, curr);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "cd.."))
		{
			PopFromStog(head);
			PrintCurrentDirectories(head);
		}
		else if(!strcmp(command, "cd"))
		{
			curr = ChangeDirectory(head, curr, name);
			PrintCurrentDirectories(head);
		}
		else if (!strcmp(command, "dir"))
		{
			DisplayInformation(curr);
			PrintCurrentDirectories(head);
		}
		else
		{
			PrintCurrentDirectories(head);
		}
	}
	return 0;
}

position MakeDirectory(char* name, position curr)
{
	position new = NULL;
	new = (position)malloc(sizeof(cvor));
	if (!new)
	{
		perror("Failed allocation!\n");
		return NULL;
	}

	strcpy(new->name, name);
	new->child = NULL;
	new->sibling = NULL;

	curr->child=InsertDirectory(curr->child, new);

	return curr;
}

int PushToStog(StogPosition head,position VanjskiDirektorij)
{
	StogPosition new = NULL;
	new = (StogPosition)malloc(sizeof(stog));
	if (!new)
	{
		perror("Failed allocation of memmory!\n");
		return -1;
	}
	StogPosition last = FindLast(head);

	new->next = last->next;
	last->next = new;
	new->VanjskiDirektorij = VanjskiDirektorij;

	return 0;
}

position InsertDirectory(position curr, position new)
{
	if (curr == NULL)
		return new;

	else if (strcmp(curr->name, new->name) > 0)
	{
		new->sibling = curr;
		return new;
	}
	else if (strcmp(curr->name, new->name) < 0)
	{
		curr->sibling = InsertDirectory(curr->sibling, new);
	}
	else
	{
		printf("There is already direcotry with same name!\n");
		free(new);
	}
	return curr;
}

StogPosition FindLast(StogPosition head)
{
	StogPosition temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}
StogPosition FindBefore(StogPosition head)
{
	StogPosition temp = head;
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

int PopFromStog(StogPosition head)
{
	if (!head->next)
		return 0;

	StogPosition before = FindBefore(head);
	StogPosition toDelete = NULL;

	toDelete = before->next;
	before->next = toDelete->next;
	free(toDelete);

	return 0;
}

position ChangeDirectory(StogPosition head,position curr,char* name)
{
	if (NULL == curr->child)
	{
		printf("The system cannot find the path specified.\n");
		return curr;
	}
	else
	{
		position temp = curr->child;
		while (temp != NULL && strcmp(temp->name,name)!=0)
			temp = temp->sibling;

		if (temp == NULL)
		{
			printf("The system cannot find the path specified.\n");
			return curr;
		}
		else
		{
			PushToStog(head,curr->child);
			return curr->child;
		}
	}
}

int DisplayInformation(position curr)
{
	if (NULL == curr->child)
	{
		printf("Directory is empty.\n");
	}
	else
	{
		position temp = curr->child;
		while (temp != NULL)
		{
			printf("<DIR>\t\t %s\n", temp->name);
			temp = temp->sibling;
		}
	}
	return 0;
}
int Exit(position curr)
{
	if (curr == NULL)
	{
		return 0;
	}

	Exit(curr->sibling);
	Exit(curr->child);
	Exit(curr->sibling);

	free(curr);

	return 0;
}
int PrintCurrentDirectories(StogPosition head)
{
	StogPosition temp = head->next;
	char line[MAX_LINE] = { 0 };

	while (temp!=NULL)
	{
		strcat(line, temp->VanjskiDirektorij->name);
		strcat(line,"/");
		temp = temp->next;
	}
	strcat(line, ">");

	printf("%s ", line);

	return 0;
}
