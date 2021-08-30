#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct ListViolations
{
   string violat;
    ListViolations* next;
};

struct TreeNode
{

    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    int number;
    ListViolations* list;
};

void Push(ListViolations*& node, string &newStr)
{
    ListViolations* tmp = new ListViolations;
    tmp->violat = newStr;    
    tmp->next = NULL;

    if (node == NULL)
    {
        node = tmp;
    }
    else
    {
        tmp->next = node;
        node = tmp;
    }
}

void ClearList(ListViolations*& Head)
{
    ListViolations* curr = Head;
    while (curr)
    {
        ListViolations* temp = curr->next;
        curr = temp;
    }
}

void PrintList(ListViolations* Head)
{
    ListViolations* curr = Head;
    while (curr)
    {
        cout << curr->violat << endl;
        curr = curr->next;
    }
}

class database
{
private:
    int size;
    TreeNode* root;

public:
    database();
    ~database();
   
    void Add(TreeNode*& head, TreeNode* parent, int value, string str);
    void Add(int value, string str);
    void PrintAll(TreeNode* );
    void PrintNumber(int input);
    TreeNode* PrintNumber(TreeNode* root, int input);
    void PrintRangeNumber(TreeNode* node, int left, int right);
    void PrintRangeNumber(int left, int right);
    TreeNode* ReturnRoot();
    void DeleteAll(TreeNode* temp);
};

database::database()
{
    root = NULL;
    size = 0;
}

database::~database()
{
    DeleteAll(root);
}


TreeNode* database::ReturnRoot()
{
    return root;
}

void database::DeleteAll(TreeNode* temp)
{
    if (temp)
    {
        DeleteAll(temp->left);
        DeleteAll(temp->right);
        ClearList(temp->list);
        delete temp;
    }
}


void database::Add(TreeNode*& head, TreeNode* parent, int value, string str)
{
    TreeNode* temp = new TreeNode;
    temp->number = value;
    temp->list = NULL;
    temp->left = temp->right = temp->parent = NULL;
   
    if (!head)
    {
        head = temp;
        Push(head->list, str);
    }
    else
    {
        if (value == head->number)
            Push(head->list, str);
        else if (value < head->number)
            Add(head->left, head, value, str);
        else
            Add(head->right, head, value, str);
    }
}


void database::Add(int value, string str)
{
    Add(root, NULL, value, str);
}

//метод печати полной базы данных
void database::PrintAll(TreeNode* temp)
{
    if (temp)
    {
        PrintAll(temp->left);
        cout << "Номер машины: " << temp->number << endl;
        cout << "Нарушения: " << endl;
        PrintList(temp->list);
        PrintAll(temp->right);
    }
    cout << endl;
}


//Распечатка данных по заданному номеру.
TreeNode* database::PrintNumber(TreeNode* node, int input)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (input == node->number)
    {
        return node;
    }
    else if (input < node->number)
    {
        return  PrintNumber(node->left, input);
    }
    else
    {
        return  PrintNumber(node->right, input);
    }

}

void database::PrintNumber(int input)
{
    TreeNode* node = PrintNumber(root, input);
    if (node == NULL)
    {
        cout << "Not found." << endl;
    }
    else
    {
        cout << "Номер машины: " << node->number << endl;
        cout << "Нарушения: " << endl;
        PrintList(node->list);
    }
    cout << endl;
}
//¦ Распечатка данных по диапазону номеров.
void database::PrintRangeNumber(TreeNode* node, int min, int max)
{
    if (node == NULL)
    {
        return;
    }
    if (node->number > min)
    {
        PrintRangeNumber(node->left, min, max);
    }
    if (node->number >= min && node->number <= max)
    {
        cout << "Номер машины: " << node->number << endl;
        cout << "Нарушения: " << endl;
        PrintList(node->list);
    }
    if (node->number < max)
    {

        PrintRangeNumber(node->right, min, max);
    }

}
void database::PrintRangeNumber(int min, int max)
{
    PrintRangeNumber(root, min, max);
}



int main()
{
    setlocale(LC_ALL, "rus");

    database bd;

   
    bd.Add(9398, "Привышение скорости");
    bd.Add(9175, "Проезд на запрещающий знак");
    bd.Add(9175, "Отсутствие прав");
    bd.Add(4299, "Привышение скорости");
    bd.Add(1077, "Вождение в нетрезвом виде");
    bd.Add(9398, "Вождение в нетрезвом виде");
    bd.Add(9055, "Привышение скорости");
    bd.Add(9055, "Проезд на запрещающий знак");
     
    
    cout << "Полный список правонарушений" << endl;
    bd.PrintAll(bd.ReturnRoot());
    cout << endl << endl;
    cout << "Cписок правонарушений по номеру" << endl;
    bd.PrintNumber(9175);
    cout << endl << endl;
    cout << "Cписок правонарушений по диапозону номеров" << endl;
    bd.PrintRangeNumber(10, 2000);
    cout << endl << endl;
    return 0;

}