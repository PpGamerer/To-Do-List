//ฟังก์ชันลบสิ่งที่จะทำจากลิสต์ Delete a To-do อยู่ใน case ที่ 3
#include<iostream>
#include<windows.h>
using namespace std;

void printTasks(string tasks[],int task_count){
    cout << "Tasks To Do " << endl;
    cout << "-------------" << endl;
    for(int i = 0; i < task_count; i++){
        cout << "Task " << i << " : " << tasks[i] << endl;
    }
    cout << "-------------" << endl;
}

int main(){
 string tasks[10] = {""}; // เลข 10 คือ จำนวน tasks ทั้งหมด กำหนดขึ้นมาเอง
 int task_count = 0;

 int option = -1;
 while (option != 0)
 {
    // สร้างเมนู
    cout << "||| To Do List |||" << endl;
    cout << "1-To Add New Task" << endl; // เพิ่ม Task ใหม่
    cout << "2-To View Tasks" << endl; // ดู Tasks
    cout << "3-Delete Tasks" << endl; // ลบ Tasks
    cout << "0-Terminate the program" << endl; // ยุติโปรแกรม
    cin >> option;

    switch (option)
    {
    case 1: // ถ้าจำนวน tasks มากกว่า 10 
    {
        if(task_count>9){
            cout << "Task List is full" << endl; 
        }else{
            cout << "Enter A New Task:";
            cin.ignore();
            getline(cin,tasks[task_count]);
            task_count++;
        } break;
    }
    case 2: // แสดงจำนวน Tasks ที่ได้พิมเข้ามา
    printTasks(tasks,task_count);
    break;

    case 3: // ลบ Task ออกจาก List
    {
        printTasks(tasks,task_count);
        int deleteTask = 0;
        cout << "Enter A task to delete:";
        cin >> deleteTask;

        if(deleteTask < 0 || deleteTask > 9){
            cout << "You entered Invaild Task No.";
            break;
        }
        for(int i = deleteTask; i < task_count; i++){
            tasks[i] = tasks[i+1];
        }
        task_count = task_count-1;
        break;
    }
    case 0:
    cout << "--Terminating the program--";
    break;

default: 
cout <<"You entered Invaild Value" << endl;
}
}
 
 return 0;
}

