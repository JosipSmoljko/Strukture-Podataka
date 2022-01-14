#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct _List;
typedef struct _List* ListPos;
typedef struct _List
{
    int brojStan;
    char grad[MAX_LINE];
    ListPos next;
}List;

struct _Tree;
typedef struct _Tree* TreePos;
typedef struct _Tree{
    char drzava[MAX_LINE];
    ListPos head;
    TreePos left;
    TreePos right;
}Tree;


TreePos CitajIzDatoteke(char *nameOfFile, TreePos root);
int GradoviIzDatoteke(char* nameOfFile, ListPos head);
ListPos KreirajNovi(char* ime, int brStanovnika);
int SortiraniUnosListe(ListPos new, ListPos head);
int UnosIza(ListPos temp, ListPos new);
ListPos PronadiIspred(ListPos find, ListPos head);
TreePos SortiraniUnosDrzavaUStablo(TreePos current, TreePos temp );
ListPos InitializeList();
int IspisiListu(ListPos head);
int IspisiStablo(TreePos current);
int PronadiGradove(char* drzava, int broj, TreePos root);
TreePos PronadiDrzavu(char* drzava, TreePos current);

int main()
{
    TreePos root = NULL;
    char drzava[MAX_LINE] = { 0 };
    int broj = 0;
    root = CitajIzDatoteke("drzave.txt", root);
    IspisiStablo(root);

    printf("Odaberite drzavu: ");
    scanf("%s", drzava);
    printf("Unesite broj: ");
    scanf("%d", &broj);
    PronadiGradove(drzava, broj, root);

    return 0;
}

TreePos CitajIzDatoteke(char *nameOfFile, TreePos root)
{
    char buffer[MAX_LINE] = { 0 };
    char fileCity[MAX_LINE] = { 0 };
    FILE *fp;
    fp=fopen(nameOfFile, "r");

    TreePos tempTree = NULL;

    if(!fp)
    {
        perror("Greska pri otvaranju datoteke\n");
		return NULL;
    }

    while(!feof(fp))
    {
        tempTree = NULL;
        tempTree = (Tree*)malloc(sizeof(Tree));
        tempTree->left= NULL;
        tempTree->right=NULL;
        tempTree->head = InitializeList();

        fgets(buffer, MAX_LINE, fp);

        if(sscanf(buffer, " %s %s",  tempTree->drzava, fileCity) == 2)
        {
            GradoviIzDatoteke(fileCity, tempTree->head);

            root = SortiraniUnosDrzavaUStablo(root, tempTree);
        }
    }

    fclose(fp);

    return root;
}

int GradoviIzDatoteke(char* nameOfFile, ListPos head)
{

    char buffer[MAX_LINE] = { 0 };
    char ime[MAX_LINE] = { 0 };
    int brojStanovnika = 0;
    FILE *fp;
    fp=fopen(nameOfFile, "r");

    ListPos newElem = NULL;

    if(!fp)
    {
        perror("Greska pri otvaranju datoteke\n");
		return -1;
    }

    while(!feof(fp))
    {
        newElem= NULL;
        fgets(buffer, MAX_LINE, fp);
        if(sscanf(buffer, " %s %d", ime, &brojStanovnika) == 2)
        {
            newElem = KreirajNovi(ime, brojStanovnika);
            SortiraniUnosListe(newElem, head);
        }
    }

    fclose(fp);

}

ListPos KreirajNovi(char* ime, int brStanovnika)
{
    ListPos newElem = NULL;

    newElem = (List*)malloc(sizeof(List));

    strcpy(newElem->grad,ime);
    newElem->brojStan = brStanovnika;
    newElem->next = NULL;

    return newElem;
}

int SortiraniUnosListe(ListPos newElem, ListPos head)
{

    ListPos temp = head;

    while(temp->next!=NULL && temp->next->brojStan < newElem->brojStan)
    {
        temp = temp->next;
    }

    if(temp->next == NULL || temp->next->brojStan != newElem->brojStan)
    {
        UnosIza(temp, newElem);
    }

    else if(temp->next->brojStan == newElem->brojStan)
    {
        if(strcmp(temp->next->grad, newElem->grad) < 0)
            UnosIza(temp->next, newElem);
        else if(strcmp(temp->next->grad, newElem->grad) > 0)
            UnosIza(temp, newElem);
    }

    else
        free(temp);

    return EXIT_SUCCESS;
}

int UnosIza(ListPos temp, ListPos newElem)
{
    newElem->next = temp->next;
    temp->next = newElem;
    return EXIT_SUCCESS;
}

ListPos PronadiIspred(ListPos find, ListPos head)
{
    ListPos temp = head;

    while(temp->next != NULL && temp->next != find)
        temp=temp->next;

    return temp;
}

TreePos SortiraniUnosDrzavaUStablo(TreePos current, TreePos temp)
{
    if(current == NULL)
    {
        current = (Tree*)malloc(sizeof(Tree));
        strcpy(current->drzava, temp->drzava);
        current->head = temp->head;
        current->left = NULL;
        current->right = NULL;
    }
    else if(strcmp(temp->drzava, current->drzava) < 0)
        current->left = SortiraniUnosDrzavaUStablo(current->left, temp);

    else if(strcmp(temp->drzava, current->drzava) > 0)
        current->right = SortiraniUnosDrzavaUStablo(current->right, temp);

    return current;
}

ListPos InitializeList()
{
    ListPos newElem = NULL;
    newElem = (List*)malloc(sizeof(List));
    newElem->brojStan = 0;
    strcpy(newElem->grad ,  "");
    newElem->next = NULL;

    return newElem;
}

int IspisiStablo(TreePos current)
{
    if(current == NULL)
        return 0;

    IspisiStablo(current->left);
    printf("\n%s\n", current->drzava);
    IspisiListu(current->head);
    IspisiStablo(current->right);

    return 0;
}

int IspisiListu(ListPos head)
{
    ListPos temp = head->next;
    while (temp != NULL)
    {
        printf("\t%s %d\n", temp->grad, temp->brojStan );
        temp= temp->next;
    }
    return 0;
}

int PronadiGradove(char* drzava, int broj, TreePos root)
{

    TreePos odabranaDrzava = NULL;
    odabranaDrzava = PronadiDrzavu(drzava, root);
    if(odabranaDrzava == NULL)
    {
        printf("Drzava %s nije pronadena.\n", drzava);
        return -1;
    }
    ListPos odab_drz = odabranaDrzava->head;
    while(odab_drz->next != NULL && odab_drz->next->brojStan < broj)
        odab_drz = odab_drz->next;
    if(odab_drz->next == NULL)
    {
        printf("Nisu pronadeni gradovi u %s koji imaju vise od %d stanovnika.\n", drzava, broj);
        return -2;
    }
    printf("\nGradovi s vise stanovnika:\n", drzava, broj);
    IspisiListu(odab_drz);
    return 0;

}

TreePos PronadiDrzavu(char* drzava, TreePos current)
{
    TreePos temp1 = NULL;
    TreePos temp2 = NULL;

    if(current == NULL)
        return NULL;

    else if(strcmp(current->drzava, drzava) == 0)
        return current;

    temp1 = PronadiDrzavu(drzava, current->left);
    temp2 = PronadiDrzavu(drzava, current->right);

    if(temp1!=NULL)
        current = temp1;

    else if(temp2!=NULL)
        current = temp2;

    else
        current = NULL;
    return current;
}
