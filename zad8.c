#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _Tree;
typedef struct _Tree* Position;
typedef struct _Tree{
    int element;
    Position Left;
    Position Right;
}Tree;

Position newElement(int elem, Position root);
Position insertElement(Position root, Position q);
int inOrderPrint(Position root);
int postorderPrint(Position root);
Position FindMin(Position root);
Position findElement(int element, Position root);
Position DeleteElement(int element, Position root);
int preOrderPrint(Position root);
int levelOrder(Position root);


int main()
{
	Position root = NULL, temp = NULL;;
	int i = 0;
	int choice = 0, num = 0;

	do{
        	printf("Choose your option: \n1 - add new element\n"
        	"2 - delete element\n"
        	"3 - inorder print\n"
        	"4 - preorder print\n"
        	"5 - postorder print\n"
        	"6 - level order print\n"
        	"7 - find element\n"
        	"8 - stop\n");

        	scanf("%d", &choice);

       	 	switch (choice)
			{
			case 1:
				printf("What number you want to add to binary tree? \n");
				scanf("%d", &num);
				root = newElement(num, root);
				break;
			case 2:
		    		printf("Enter number you want to delete:\n");
				scanf("%d", &num);
				root = DeleteElement(num, root);
				break;
			case 3:
		    		inOrderPrint(root);
				break;
			case 4:
				preOrderPrint(root);
				break;
			case 5:
                postOrderPrint(root);
				break;
			case 6:
				levelOrder(root);
				break;
			case 7:
				printf("What number you are searching for?\n");
				scanf("%d", &num);
				temp = findElement(num, root);
				break;
            case 8:
				break;
			default:
				printf("Wrong input!\n");
			}

	}while(choice != 8);

	return 0;
}

Position newElement(int elem, Position root)
{
    Position newNode = (Position)malloc(sizeof(Tree));

    if(!newNode){
        perror("Can't allocate memory! \n");
        return NULL;
    }

    newNode->element = elem;
    newNode->Right = NULL;
    newNode->Left = NULL;
    newNode = insertElement(root, newNode);

    return newNode;
}

Position insertElement(Position current, Position q)
{
    if (current == NULL)
		return q;

	else if (current->element < q->element)
		current->Right = insertElement(current->Right, q);

	else if (current->element > q->element)
		current->Left = insertElement(current->Left, q);

	else
		free(q);

	return current;
}

int inOrderPrint(Position root)
{
	if (root)
	{
		inOrderPrint(root->Left);
		printf("%d \n", root->element);
		inOrderPrint(root->Right);
	}
	return 0;
}

int postOrderPrint(Position root)
{
	if (root)
	{
		postOrderPrint(root->Left);
		postOrderPrint(root->Right);
		printf("%d \n", root->element);
	}
	return 0;
}
int preOrderPrint(Position root)
{
	if (root)
	{
		printf("%d \n", root->element);
		preOrderPrint(root->Left);
		preOrderPrint(root->Right);
	}
	return 0;
}

int levelOrder(Position root)
{

}

Position FindMin(Position root)
{
	while (root->Left)
		root = root->Left;

	return root;
}

Position findElement(int element, Position root)
{
	if (!root)
		return root;

    else if (element > root->element)
		return findElement(element, root->Right);

	else if (element < root->element)
		return findElement(element, root->Left);

	else
		return root;
}

Position DeleteElement(int element, Position root)
{
	Position temp;
	if (!root){
        printf("There is no that element! \n");
        return root;
	}
	else if (element < root->element)
		root->Left = DeleteElement(element, root->Left);

	else if (element > root->element)
		root->Right = DeleteElement(element, root->Right);

	else
	{
		if (root->Left && root->Right)
		{
			temp = FindMin(root->Right);
			root->element = temp->element;
			root->Right = DeleteElement(temp->element, root->Right);
		}
		else
		{
			temp = root;
			if (!root->Left)
				root = root->Right;
			else if (!root->Right)
				root = root->Left;
			free(temp);
		}
	}
	return root;
}
