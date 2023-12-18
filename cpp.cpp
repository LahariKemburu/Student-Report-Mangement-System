#include<bits/stdc++.h>
#include<fstream>
using namespace std;
vector<double>top;
const int MAX_STUDENTS = 100;
 class student
{
public:
 int rollno;
 char name[50];
 int p_marks, c_marks, m_marks, e_marks, cs_marks;
 double per;
 char grade;
 void calculate(); //function to calculate grade
public:
 void getdata(); //function to accept data from user
 void showdata() const; //function to show data on screen
 void show_tabular() const;
 int retrollno() const;
}; 
void delete_data()
{
	ofstream ptr;
	ptr.open("student.dat");
	ptr.close();
}
void student::calculate() //function to calculate grade
{
 per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
 if(per>=60)
 grade='A';
 else if(per>=50)
 grade='B';
 else if(per>=33)
 grade='C';
 else
 grade='F';
}

void student::getdata() {
    ifstream inFile("student.dat", ios::binary);
    bool rollExists = false;
    do {
        cout << "\nEnter The roll number of student: ";
        cin >> rollno;
        rollExists = false;
        student st;
        while (inFile.read(reinterpret_cast<char*>(&st), sizeof(student))) {
            if (st.rollno == rollno) {
                rollExists = true;
                break;
            }
        }
        inFile.clear();
        inFile.seekg(0, ios::beg);
        if (rollExists) {
            cout << "Student with roll number " << rollno << " already exists. Please choose a different roll number.\n";
        }

    } while (rollExists);
    inFile.close();
    cout << "\nEnter The Name of student: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter The marks in physics out of 100: ";
    cin >> p_marks;
    cout << "Enter The marks in chemistry out of 100: ";
    cin >> c_marks;
    cout << "Enter The marks in maths out of 100: ";
    cin >> m_marks;
    cout << "Enter The marks in english out of 100: ";
    cin >> e_marks;
    cout << "Enter The marks in computer science out of 100: ";
    cin >> cs_marks;
    calculate();
}

void student::showdata() const
{
 cout<<"\nRoll number of student : "<<rollno;
 cout<<"\nName of student : "<<name;
 cout<<"\nMarks in Physics : "<<p_marks;
 cout<<"\nMarks in Chemistry : "<<c_marks;
 cout<<"\nMarks in Maths : "<<m_marks;
 cout<<"\nMarks in English : "<<e_marks;
 cout<<"\nMarks in Computer Science :"<<cs_marks;
 cout<<"\nPercentage of student is  :"<<per;
 cout<<"\nGrade of student is :"<<grade;
}
void student::show_tabular() const
{
 cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
 <<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}
int  student::retrollno() const
{
 return rollno;
}

void write_student(); //write the record in binary file
void display_all(); //read all records from binary file
void display_sp(int); //accept rollno and read record from binary file
void modify_student(int); //accept rollno and update record of binary file
void delete_student(int); //accept rollno and delete selected records from binary file
void class_result(); //display all records in tabular format from binary file
void result(); //display result menu
void intro(); //display welcome screen
void entry_menu(); //display entry menu on screen



int main()
{
 char ch;
 intro();
 do
 {
 system("cls");   //clear the console screen
 cout<<"\n\n\n\tMAIN MENU";
 char ch;
 int rno;
 int num;
 system("cls");
 cout<<"\n\n\n\tRESULT MENU";
cout<<"\n\n\t1. CLASS RESULT";
 cout<<"\n\n\t2. DISPLAY A PARTICULAR STUDENT RECORD";
 cout<<"\n\n\n\tENTRY/EDIT MENU";
 cout<<"\n\n\t3. ADDITION OF NEW STUDENT RECORD";
 cout<<"\n\n\t4. DISPLAY ALL STUDENTS RECORD";
 cout<<"\n\n\t5. SEARCH STUDENT RECORD";
 cout<<"\n\n\t6. MODIFY A STUDENT RECORD";
 cout<<"\n\n\t7. DELETE A STUDENT RECORD";
 cout<<"\n\n\n\t8. DISPLAY TOP 3";
 cout<<"\n\n\n\t9. DELETE CLASS DATA";
 cout<<"\n\n\t10.TO EXIT PRESS e";
 cout<<"\n\n\n\tEnter Choice? ";
 cin>>ch;
 system("cls");

 switch(ch)
 {
 //writeStudentToFile("student.dat", "output.txt");
 case '1' : class_result(); break;
 case '2' : cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
 display_sp(rno); break;
 case '3': write_student(); break;
 case '4': display_all(); break;
 case '5': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 display_sp(num); break;
 case '6': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 modify_student(num);break;
 case '7': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 delete_student(num);break;
 case '8':toppers();
 break;
 case '9':delete_data();
 break;
 case 'e': exit(1);
 break;
 default: cout<<"\a";
 } 
 cout<<"";
}while(ch!='9');
 return 0;
}

void write_student()
{
 student st;
 ofstream outFile;
 outFile.open("student.dat",ios::binary|ios::app);   // treated as a binary file  and  data will be written at the end of the file
 st.getdata();
 top.push_back(st.per);
 outFile.write(reinterpret_cast<char *> (&st), sizeof(student));//is used to convert the address of st to a char pointer
 outFile.close();
     cout<<"\n\nStudent record Has Been Created ";
 cin.ignore();
 cin.get();
}

void display_all()
{
 student st;
 ifstream inFile; 
 inFile.open("student.dat",ios::binary); 
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
 while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
 {
 st.showdata();
 cout<<"\n\n***********************************\n";
 }
 inFile.close();
 cin.ignore();
 cin.get();
}

void display_sp(int n)
{
 student st;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 bool flag=false;
 while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
 {
 if(st.retrollno()==n)
 {
     st.showdata();
  flag=true;
 }
 }
 inFile.close();
 if(flag==false)
 cout<<"\n\nrecord not exist";
 cin.ignore();
 cin.get();
}
void modify_student(int n)
{
 bool found=false;
 student st;
 fstream File;
 File.open("student.dat",ios::binary|ios::in|ios::out);
 if(!File)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
     while(!File.eof() && found==false)
 {

 File.read(reinterpret_cast<char *> (&st), sizeof(student));
 if(st.retrollno()==n)
 {
 st.showdata();
 cout<<"\n\nPlease Enter The New Details of student"<<endl;
 st.getdata();
      int pos=(-1)*static_cast<int>(sizeof(st));
      File.seekp(pos,ios::cur);
      File.write(reinterpret_cast<char *> (&st), sizeof(student));
      cout<<"\n\n\t Record Updated";
      found=true;
 }
 }
 File.close();
 if(found==false)
 cout<<"\n\n Record Not Found ";
 cin.ignore();
cin.get();
}
void delete_student(int n)
{
 student st;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 ofstream outFile;
 outFile.open("Temp.dat",ios::out);
 inFile.seekg(0,ios::beg);
 while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
 {
 if(st.retrollno()!=n)
 {
 outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
 }
 }
 outFile.close();
 inFile.close();
 remove("student.dat");
 rename("Temp.dat","student.dat");
 cout<<"\n\n\tRecord Deleted ..";
 cin.ignore();
 cin.get();
}
void class_result()
{
 student st;
 ifstream inFile;   
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
 cout<<"==========================================================\n";
 cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
cout<<"==========================================================\n";
 while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student))) //It's used to reinterpret or convert the pointer obtained from &st into a pointer to a character (char). 
 {
 st.show_tabular();
 }
 cin.ignore();
 cin.get();
 inFile.close();
}
void intro()
{
 cout<<"\n\n\n\t\t WELCOME TO SRM STUDENT REPORT MANAGEMENT SYSTEM";
 cout<<"\n\n\n\tPress Enter To Continue\n\n";
 cin.get();
}

