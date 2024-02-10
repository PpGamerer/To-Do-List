#include<iostream>
#include<string>
using namespace std;


int main()
{
    //เพิ่มรายละเอียดเพิ่มเติม
    string Remarks;
    cout << "Add a Remarks? y/n : ";
    getline(cin,Remarks);
   
    for(int i = 0 ; i < 1000 ; i++)
    {
       
        if(Remarks == "yes" || Remarks == "y" || Remarks == "Y" || Remarks == "Yes")
        {
            cout << "Add a Remarks : ";
            getline(cin,Remarks);
            break;

        }
        else if (Remarks == "no" || Remarks == "n" || Remarks == "N" || Remarks == "No")
        {
            break;

        }
        else 
        {
             cout << "Add a Remarks? y/n : ";
            getline(cin,Remarks);
        }
        
    }



    


//เพิ่มวันที่มเดดไลน์
    string Date;
    cout << "Add a Due Date? y/n : ";
    getline(cin,Date);
   
    for(int j = 0 ; j < 1000 ; j++)
    {
       

        if(Date == "yes" || Date == "y" || Date == "Y" || Date == "Yes")
        {
            cout << "Add a Due Date (M/D/Y) : ";
            getline(cin,Date);
            break;

        }
        else if (Date == "no" || Date == "n" || Date == "N" || Date == "No")
        {
            break;

        }
        else 
        {
            cout << "Add a Due Date? y/n : ";
            getline(cin,Date);
        }
        
    }

}