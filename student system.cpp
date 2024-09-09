//用结构体来存储信息并形成链表，用类来管理结构体的增删查改等操作
//每一个类的实例都是一个单一链表,类的实例以头结点的指针来区分
#include<iostream>
#include <string> 
#include <cstring> // 用strcpy函数  

typedef struct student_list
{
    int student_number;
    std::string student_name;
    std::string student_gender;
    int phone_number;
    std::string student_address;

    struct student_list* next = nullptr;
    // 构造函数
    student_list(int num, std::string name, std::string gender, int phone, std::string address)
        : student_number(num), student_name(name), student_gender(gender), phone_number(phone), student_address(address) {};
    // 析构函数
    ~student_list() {};
} node;

class Student
{
private:
    node* head = NULL;//链表头节点
    node* tail = NULL;//链表尾节点
public:
    Student() : head(nullptr) {}
    Student(node* imput_head) :head(imput_head) {}
    ~Student();

    node* show_tail() { return tail; }//返回尾节点的值，方便外界访问

    void show() { show(head); }//显示函数，进行重载，如果没有传入参数就显示头结点的内容
    void show(node* current);//传入结构体指针就可以进行内容的显示
    void show_all();//从头结点开始显示各个节点的学生信息

    void tail_flash();//由于尾节点会随着链表长度边长而变化，所以每次新增节点或者删除节点都需要调用tail_flash这个函数来更新尾节点
    //如果懒得调理链表的结尾，直接调用这个函数即可，虽然影响性能，但是方便
    void new_student(int num, std::string name, std::string gender, int phone, std::string address);

    //新增一个学生信息，并将它接入到链表尾部
    void delete_by_sno(int sno);//通过学号删除
    void select_by_sno(int sno);//通过学号查找

};

Student::~Student()//类的析构函数
{
    if (head == nullptr) return;
    node* temp1 = head;
    node* temp2 = head->next;
    delete temp1;
    temp1 = temp2;
    while (temp1 != NULL)
    {
        temp2 = temp2->next;
        delete temp1;
        temp1 = temp2;
    }
}

void Student::show(node* current)
{
    if (current == nullptr) {
        std::cout << "no information!" << std::endl; return;
    }
    else {
        std::cout << "学号："  << current->student_number << std::endl;
        std::cout << "姓名：" << current->student_name << std::endl;
        std::cout << "性别：" << current->student_gender << std::endl;
        std::cout << "联系电话：" << current->phone_number << std::endl;
        std::cout << "地址：" << current->student_address << std::endl;
    }
}

void Student::show_all()
{
    if (head == nullptr) {
        std::cout << "no information!" << std::endl; return;
    }
    node* temp = head;
    while (temp != NULL)
    {
        show(temp);
        temp = temp->next;
    }
}

void Student::tail_flash()
{//刷新尾节点，尚未完善

    if (head==NULL)
    {
        tail = NULL;
        return;
    }
    if (head->next == NULL)
    {
        tail = head; return;
    }
    if (tail->next != NULL)
    {
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        return;
    }

}

void Student::new_student(int num, std::string name, std::string gender, int phone, std::string address)
{
    node* NewStudent = new student_list(num, name, gender, phone, address);
    if (head == nullptr)
    {
        head = NewStudent;
        tail_flash();
    }
    else
    {
        tail->next = NewStudent;
        tail_flash();
    }
}

void Student::delete_by_sno(int sno)
{
    if (head == nullptr)
    { 
        std::cout << "no information!" << std::endl; 
        return; 
    }
    node* temp = head;
    if (head->student_number == sno)
    {
        head = head->next;
        delete temp;
        std::cout << "学号为" << sno << "的学生的信息已删除" << std::endl;
        tail_flash();
        return;
    }
    while (temp != NULL)
    {
        if (temp->next == NULL) break;//出现这种情况，说明没有找到目标
        if (temp->next->student_number == sno)
        {
            node* ready = temp->next;
            if (ready == tail) { tail = temp; }
            temp->next = ready->next;
            delete ready;
            std::cout << "学号为" << sno << "的学生的信息已删除" << std::endl;
            return;
        }
        temp = temp->next;
    }

    if (temp->next == NULL) { std::cout << "学号为" << sno << "的学生不存在" << std::endl; }
}

void Student::select_by_sno(int sno)
{
    node* temp = head;
    while (temp != NULL)
    {
        if (temp->student_number == sno)
        {
            show(temp);
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL) { std::cout << "学号为" << sno << "的学生不存在" << std::endl; }
}

void insert_student(Student* stu)//传入指针才能对实例的本体进行操作
{
    int student_number;
    std::string student_name;
    std::string student_gender;
    int phone_number;
    std::string student_address;
    std::cout << "请按“学号 姓名 性别 联系电话 地址”的格式输入学生信息" << std::endl;
    std::cin >> student_number;
    std::cin >> student_name;
    std::cin >> student_gender;
    std::cin >> phone_number;
    std::cin >> student_address;

    stu->new_student(student_number, student_name, student_gender, phone_number, student_address);
    std::cout << "信息录入完成" << std::endl;
    return;
}
void show_student(Student* stu)
{
    int i = 1;
    std::cout << "输入数组选择查询方（默认为1）" << std::endl;
    std::cout << "1.查询全部学生信息  2.按学号查找学生信息" << std::endl;
    std::cin >> i;
    switch (i)
    {
    case 1:
        std::cout << "查询结果如下" << std::endl;
        std::cout << "___________________________________________" << std::endl;
        stu->show_all();
        break;
    case 2:
        int sno = 0;
        std::cout << "请输入学号：" << std::endl;
        std::cin >> sno;
        std::cout << "查询结果如下" << std::endl;
        std::cout << "___________________________________________" << std::endl;
        stu->select_by_sno(sno);
    }
    std::cout << "查询完毕" << std::endl;

}
void delete_student(Student* stu)
{
    int sno;
    std::cout << "请输入要删除的学生信息的学号" << std::endl;
    std::cin >> sno;
    stu->delete_by_sno(sno);
}
int main()
{
    Student first;
    int signal = 1;
    while (signal)
    {
        int i = 0;
        std::cout << "___________________________________________" << std::endl;
        std::cout << "输入相应数字选择要进行的操作" << std::endl;
        std::cout << "1.新增学生信息 2.查找学生信息 3.删除学生信息" << std::endl;
        std::cin >> i;
        switch (i)
        {
        case 1://进行 新增 操作
            insert_student(&first);
            break;
        case 2://进行 查找 操作
            show_student(&first);
            break;
        case 3:
            delete_student(&first);
            break;
        default:
            signal = 0;
            std::cout << "退出中" << std::endl;
            break;
        }
        std::cout << "___________________________________________" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cin.ignore();
    }
    system("pause");
}