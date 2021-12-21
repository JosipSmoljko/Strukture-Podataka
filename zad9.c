#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct _cvor;
typedef struct _cvor* Position;
typedef struct _cvor
{
	int number;
	Position left;
	Position right;
}cvor;

struct _stog;
typedef struct _stog* stogPointer;
typedef struct _stog
{
	int element;
	stogPointer next;
}stog;

Position initializeBinaryTree(int elem);
Position addElement(int elem, Position root);
int replace(Position root);
int Insert(Position root);
int printInOrder(Position current);
int DeleteAll(Position current);
int PopStog(stogPointer head);
int PushStog(stogPointer head, int element);
int addToFile(stogPointer head,Position root,char*name);
int addToStog(stogPointer head, Position current);

int main()
{
      stog head = { .element = 0, .next = NULL};
	  Position root = NULL;

    root = addElement(2, root);
    root = addElement(5, root);
    root = addElement(7, root);
    root = addElement(8, root);
    root = addElement(11, root);
    root = addElement(1, root);
    root = addElement(4, root);
    root = addElement(2, root);
    root = addElement(3, root);
    root = addElement(7, root);

    printf("Pocetno stablo: \n");
    printInOrder(root);
    printf("\n");
    addToStog(&head, root);
    addToFile(&head, root, "datoteka.txt");


    replace(root);
    printf("Stablo nakon zamjene vrijednosti: ");
    printf("\n");
    printInOrder(root);
    printf("\n");
    addToStog(&head, root);
    addToFile(&head, root, "datoteka.txt");

    printf("Dodavanje random elementa u novo stablo: ");
    printf("\n");
    Insert(root);
    printf("\n");
    printInOrder(root);

	return 0;
}

int inorderPrint(Position root)
{
	if (root)
	{
		inorderPrint(root->left);
		printf("%d ", root->number);
		inorderPrint(root->right);
	}

	return 0;
}

Position initializeBinaryTree(int elem)
{
    Position newNode = (Position)malloc(sizeof(cvor));

    if(!newNode){
        perror("Can't allocate memory! \n");
        return NULL;
    }

    newNode->number = elem;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

Position addElement(int elem, Position root)
{
    if(!root)
        return initializeBinaryTree(elem);
    else if(elem < root->number)
        root->right = addElement(elem, root->right);
    else if(elem >= root->number)
        root->left = addElement(elem, root->left);
    return root;
}

int Insert(Position root)
{
    srand((unsigned) time(NULL));
    int element = 0;
    element = (rand() %(90 - 10 + 1)) + 10;
    printf("Random element is %d", element);
    root = addElement(element,root);
    return 0;
}

int replace(Position root)
{
    int element = 0;

    if(root == NULL)
        return 0;

    else if(root->left != NULL && root->right != NULL){
        element = root->number;
        root->number = replace(root->left) + replace(root->right);
        return root->number + element;
    }

    else if (root->left == NULL){
		  element = root->number;
		  root->number = replace(root->right);
		  return root->number + element;
	  }

	  else if (root->right == NULL){
		  element = root->number;
		  root->number = replace(root->left);
		  return root->number + element;
	  }

	  else{
      element = root->number;
      root->number = 0;
      return root->number;
	}
}

int printInOrder(Position current)
{
	if (!current)
		return 0;

	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);

	return 0;
}

int PopStog(stogPointer head)
{
	if (!head->next)
		return 0;

	stogPointer toDelete = head->next;
	head->next = toDelete->next;
	free(toDelete);

	return 0;
}
int PushStog(stogPointer head, int element)
{
	stogPointer new = NULL;
	new = (stogPointer)malloc(sizeof(stog));
	
  if (!new){
		perror("Failed allocation!\n");
		return -1;
	}

	new->element = element;
	new->next = head->next;
	head->next = new;

	return 0;
}

int addToStog(stogPointer head,Position root)
{
	if (NULL == root)
		return 0;

	addToStog(head, root->right);
	PushStog(head, root->number);
	addToStog(head, root->left);

	return 0;
}
int addToFile(stogPointer head, Position root, char* fileName)
{
	FILE* fp = NULL;

	fp = fopen(fileName, "a");

	while (head->next)
	{
		fprintf(fp, "%d ", head->next->element);
		PopStog(head);
	}

	fprintf(fp, "\n");
	fclose(fp);

	return 0;
}
