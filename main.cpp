#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <conio.h>
#include<limits>
#include<ctime>
using namespace std;
#define MAX_ID_LEN 5
#define MAX_NAME_LEN 20
#define MAX_TEST_LEN 11

// ADMIN-USER LOGIN
class Modules {
public:
    void choice();
    void admin();
    void user();
};

//class Files for file handling
class Files : public Modules { //resource class
//member functions for class Files
public:
    void pat_data();
    void pay_data();
    void phy_data();
    void add_pat_data();
    void test_data();
    void add_phy_data();
    void add_pay_data();
    void report_data();
    void enquiry();
    void rep_data();
    void add_rep_data();
    bool checkdate(int m, int d, int y);
}f1;

void Files::pat_data(){
    system("cls");
    fstream file1;
    file1.open("patient_data.txt", ios::in);
    if (!file1.is_open()) {
        cout << "Error while opening file." << endl;
    }
    string line;
    cout<<"****************************************************************************************************"<<endl;
    cout<<"PID  PATIENT NAME         PHONE       ADDRESS                     TEST      DATE     TIME"<<endl;
    cout<<"****************************************************************************************************"<<endl;
    while (file1.good()) {
        getline(file1, line,',');
        cout << line;
    }
    cout<<"****************************************************************************************************"<<endl;
    file1.close();
}

void Files::add_pat_data() {
    system("cls");

    fstream file2;
    file2.open("patient_data.txt", ios::out | ios::app);
    if (!file2.is_open()) {
        cout << "Error while opening file." << endl;
    }
    char pid[5], pname[25], phone[12], add[25];
    int dd, mm, yyyy, hrs, minutes, apm, test;
x:  cout<<"Adding a patient record..."<<endl;

p:
    fflush(stdin);
    cout << "Enter Patient ID:";    cin.getline(pid, 5); cout << endl;
    int alnum = 0, nalnum = 0;
    for(int i = 0; pid[i] != '\0'; i++){
        if(isalnum(pid[i])){
            alnum++;
        } else {
            nalnum++;
        }
    }
    if(nalnum != 0){
        cout<<"You have entered INVALID value for this field!"<<endl;
        goto p;
    }
    file2<<left<<setw(MAX_ID_LEN)<< pid <<',';
    x1:
    fflush(stdin);
    cout << "Enter Patient Name:";  cin.getline(pname, MAX_NAME_LEN); cout << endl;
    int alpha=0, nalpha=0;
    for(int i =0; pname[i] != '\0'; i++){

        if(isalpha(pname[i]) || pname[i]==32 || pname[i] == 46){
            alpha++;
        } else {
            nalpha++;
        }
    }
    if(nalpha !=0){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x1;
    }
    file2<<left<<setw(MAX_NAME_LEN)<< pname<<',';


x2: fflush(stdin);
    cout << "Enter Patient's Phone number:"; cin.getline(phone, 15); cout << endl;
    int d=0, nd=0, countx = 0;
    for(int i =0;phone[i] != '\0'; i++){

        if(isdigit(phone[i])){
            d++;
        } else {
            nd++;
        }
        countx++;
    }
    if(nd !=0 || countx != 10){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x2;
    }
    file2<< setw(11) <<phone<<',' ;


x3: fflush(stdin);
    cout << "Enter Patient's Address:"; cin.getline(add, 40); cout << endl;
    int alpha1=0, nalpha1=0;
    for(int i =0; add[i] != '\0'; i++){

        if(isalnum(add[i]) || add[i]==32){
            alpha1++;
        } else {
            nalpha1++;
        }
    }
    if(nalpha1 !=0){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x3;
    }
    file2<<left<<setw(28)<< add <<',';

x4: fflush(stdin);
    cout<<"Press an appropriate button for the following TEST options:-"<<endl;
    cout<<"1 - BP"<<endl<<"2 - SUGAR"<<endl<<"3 - CT SCAN"<<endl<<"4 - ULTRASOUND"<<endl<<"5 - COVID"<<endl<<"6 - MRI"<<endl<<"7 - BLOOD"<<endl<<"8 - URINE"<<endl;
    int count1 = 0;
    cout<<"Select a Test:";
    cin>>test;
    switch(test){
        case 1: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"BP"<<',';    break;
        case 2: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"SUGAR"<<','; break;
        case 3: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"CT SCAN"<<',';   break;
        case 4: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"ULTRASOUND"<<',';    break;
        case 5: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"COVID"<<','; break;
        case 6: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"MRI"<<',';   break;
        case 7: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"BLOOD"<<','; break;
        case 8: file2<<' '<<left<<setw(MAX_TEST_LEN)<<"URINE"<<','; break;
        default: count1++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count1 != 0){
        goto x4;
    }

    fflush(stdin);
    cout << "Enter Date settled for appointment" << endl;
    zi:
    fflush(stdin);
    time_t now = time(0); // get current date and time
    tm* ltm = localtime(&now);
    int year = 1900 + ltm->tm_year ;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    cout<<"Enter date (dd-mm-yyyy):";
        cin>>dd;
        if(cin.get() != '-'){
            cout<<"\nERROR:Expected '-'";
            //return 1;
        } cin>>mm;
        if(cin.get() != '-'){
            cout<<"\nERROR:Expected '-'";
           // return 1;
        } cin>>yyyy;
        if(dd> 31 || dd<1){
            cout<<"ERROR:INVALID DAY OF DATE (DD)"<<endl;
            goto zi;
        }
        if(mm> 12 || mm < 1){
            cout<<"ERROR:INVALID MONTH OF DATE (MM)"<<endl;
            goto zi;
        }
        if(yyyy != 2023){
            cout<<"ERROR:INVALID YEAR OF DATE (YYYY)"<<endl;
            goto zi;
        }
        if(mm == 1 && dd <7){
            cout<<"ERROR:INVALID - no appointments for today can be booked!"<<endl;
            goto zi;
        }
        if(dd <= day && yyyy <= year && mm <= month){
            cout<<"ATTENTION:Can only book slot for after today!"<<endl;
            goto zi;
        }
    file2<<dd<<'-'<<mm<<'-'<<yyyy<<',';


    fflush(stdin);
    cout << "Enter Time settled for appointment:"; cout << endl;    x8:
    cout << "Enter Time (hrs:minutes):";
    cin>>hrs;
        if(cin.get() != ':'){
            cout<<"\nERROR:Expected ':'";
            //return 1;
        } cin>>minutes;

    if(hrs > 24 || hrs < 0){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x8;
    }
    if(minutes > 60 || minutes < 0){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x8;
    }
    file2<<' '<< hrs<<':'<<minutes;
    if(hrs <= 24 && hrs >= 12 ){
        file2<<"PM"<<','<<endl;
    } else {
        file2<<"AM"<<','<<endl;
    }


    cout << "1 Record inserted successfully" << endl;
    int n1;
    cout<< "Do you want to add another record?:";
    while(!(cin >> n1)){
        cout<<"Error: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout<< "Do you want to add another record?:";
    }

    if(n1 == 1){
        system("cls");
        goto x;
    }

    file2.close();

}

void Files::pay_data(){
    system("cls");
    fstream file3;
    file3.open("payment_data.txt", ios::in);
    if (!file3.is_open()) {
        cout << "Error while opening file." << endl;
    }
    string line;
    cout<<"****************************************************************************************"<<endl;
    cout<<"Pid    Patient Name          Test     Pay_ST      Pay_Met"<<endl;
    cout<<"****************************************************************************************"<<endl;
    while (file3.good()) {
        getline(file3, line, ',');
        cout << line;
    }
    cout<<"****************************************************************************************"<<endl;
    file3.close();
}

void Files::add_pay_data(){
    system("cls");
    char pid[5], pname[25];
    int test, pay_st, pay_met;

    fstream file4;
    file4.open("payment_data.txt", ios::out | ios::app);

    if (!file4.is_open()) {
        cout << "Error while opening file." << endl;
    }

y:  cout<<"Adding a Payment record..."<<endl;

x4:
    fflush(stdin);
    cout<<"Enter Patient ID:";  cin.getline(pid, MAX_ID_LEN);  cout<<endl;
    int alnum = 0, nalnum = 0;
    for(int i = 0; pid[i] != '\0'; i++){
        if(isalnum(pid[i])){
            alnum++;
        } else {
            nalnum++;
        }
    }
    if(nalnum != 0){
        cout<<"You have entered INVALID value for this field!"<<endl;
        goto x4;
    }
    file4<<left<<setw(MAX_ID_LEN)<<pid<<',';

x:  fflush(stdin);
    cout<<"Enter Patient Name:";  cin.getline(pname, MAX_NAME_LEN);  cout<<endl;
    int alpha=0, nalpha=0;
    for(int i =0; pname[i] != '\0'; i++){

        if(isalpha(pname[i]) || pname[i]==32 || pname[i] == 46){
            alpha++;
        } else {
            nalpha++;
        }
    }
    if(nalpha !=0){
        cout<<"You have entered an invalid value for this field!"<<endl;
        goto x;
    }
    file4<<left<<setw(MAX_NAME_LEN)<<pname<<',';

    fflush(stdin);
    cout<<"Press an appropriate button for the following TEST options:-"<<endl;
    cout<<"1 - BP"<<endl<<"2 - SUGAR"<<endl<<"3 - CT SCAN"<<endl<<"4 - ULTRASOUND"<<endl<<"5 - COVID"<<endl<<"6 - MRI"<<endl<<"7 - BLOOD"<<endl<<"8 - URINE"<<endl;
    int count = 0;
x1: cout<<"Select Test:";
    while(!(cin >> test)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<<"Select Test:";
    }
    cout<<endl;
    switch(test){
        case 1: file4<<left<<setw(MAX_TEST_LEN)<<"BP"<<',';    break;
        case 2: file4<<left<<setw(MAX_TEST_LEN)<<"SUGAR"<<','; break;
        case 3: file4<<left<<setw(MAX_TEST_LEN)<<"CT SCAN"<<',';   break;
        case 4: file4<<left<<setw(MAX_TEST_LEN)<<"ULTRASOUND"<<',';    break;
        case 5: file4<<left<<setw(MAX_TEST_LEN)<<"COVID"<<','; break;
        case 6: file4<<left<<setw(MAX_TEST_LEN)<<"MRI"<<',';   break;
        case 7: file4<<left<<setw(MAX_TEST_LEN)<<"BLOOD"<<','; break;
        case 8: file4<<left<<setw(MAX_TEST_LEN)<<"URINE"<<','; break;
        default: count++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count != 0){
        goto x1;
    }
    cout<<endl;

x2: fflush(stdin);
    cout<<"Press an appropriate button for the following PAYMENT STATUS options:-"<<endl;
    cout<<"1 - PAID"<<endl<<"2 - NOT PAID"<<endl;
    int count1 = 0;
    cout<<"Enter Payment Status:";
    while(!(cin >> pay_st)){
        cout<<"Error: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout<<"Select Payment Status:";
    }
    switch(pay_st){
        case 1: file4<<left<<setw(9)<<"PAID"<<',';    break;
        case 2: file4<<left<<setw(9)<<"NOT PAID"<<','; break;
        default: count1++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count1 != 0){
        goto x2;
    }
    cout<<endl;


x3: fflush(stdin);
    cout<<"Press an appropriate button for the following SHIFT options:-"<<endl;
    cout<<"1 - CASH"<<endl<<"2 - UPI"<<endl<<"3 - NET BANKING"<<endl<<"4 - CARD"<<endl<<"5 - NULL"<<endl;
    int count2 = 0;
    cout<<"Enter Payment Method:";
    while(!(cin >> pay_met)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<<"Select Payment Method:";
    }
    switch(pay_met){
        case 1: file4<<left<<setw(12)<<"CASH"<<','<<endl;    break;
        case 2: file4<<left<<setw(12)<<"UPI"<<','<<endl; break;
        case 3: file4<<left<<setw(12)<<"NET BANKING"<<','<<endl; break;
        case 4: file4<<left<<setw(12)<<"CARD"<<','<<endl; break;
        case 5: file4<<left<<setw(12)<<"NULL"<<','<<endl; break;
        default: count2++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count2 != 0){
        goto x3;
    }
    cout<<endl;

    int n;
    cout<< "Do you want to add another record?[0-NO/1-YES]";
    while(!(cin >> n)){
        cout<<"Error: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout<< "Do you want to add another record?";
    }
    cout<<endl;
    if(n == 1){
        system("cls");
        goto y;
    }
    file4.close();
}

void Files::phy_data(){
    system("cls");
    fstream file5;
    file5.open("physician_data.txt", ios::in);
    if (!file5.is_open()) {
        cout << "Error while opening file." << endl;
    }
    string line;
    cout<<"****************************************************************************************************"<<endl;
    cout<<"PhyID   Phy_NAME          SPEC      PPD WH   SHIFT SALARY"<<endl;
    cout<<"****************************************************************************************************"<<endl;
    while (file5.good()) {
        getline(file5, line, ',');
        cout << line;
    }
    cout<<"****************************************************************************************************"<<endl;
    file5.close();
}

void Files::add_phy_data(){

    system("cls");

    char phy_id[5], phy_name[20], sal[9], ppd[4]; //wh[4];
    int spec, shift, wh;
    fstream file6;
    file6.open("physician_data.txt", ios::out | ios::app);
    if (!file6.is_open()) {
        cout << "Error while opening file." << endl;
    }
z:
    cout<<"Adding a new Physician record..."<<endl;
x6:
    fflush(stdin);
    cout<<"Enter Physician ID:";    cin.getline(phy_id, 6);  cout<<endl;
    int alnum = 0, nalnum = 0;
    for(int i = 0; phy_id[i] != '\0'; i++){
        if(isalnum(phy_id[i])){
            alnum++;
        } else {
            nalnum++;
        }
    }
    if(nalnum != 0){
        cout<<"You have entered INVALID value for this field!"<<endl;
        goto x6;
    }
    file6<<setw(MAX_ID_LEN)<<phy_id<<','<<' ';
x:
    fflush(stdin);
    cout<<"Enter Physician Name:";    cin.getline(phy_name, MAX_NAME_LEN);  cout<<endl;
    int alpha=0, nalpha=0;
    for(int i =0;phy_name[i] != '\0'; i++){

        if(isalpha(phy_name[i]) || phy_name[i]==32 || phy_name[i] == 46){
            alpha++;

        } else {
            nalpha++;
        }
    }
    if(nalpha !=0){
        cout<<"You have entered non-alphabetic value:"<<endl;
        goto x;
    }
    file6<<left<<setw(MAX_NAME_LEN)<<phy_name<<',';


x1:
    fflush(stdin);
    cout<<"Specializations available:"<<endl;
    cout<<"1 - BP"<<endl<<"2 - SUGAR"<<endl<<"3 - CT SCAN"<<endl<<"4 - ULTRASOUND"<<endl<<"5 - COVID"<<endl<<"6 - MRI"<<endl<<"7 - BLOOD"<<endl<<"8 - URINE"<<endl;
    int count = 0;
    cout<<"Select Specialization:";
    while(!(cin >> spec)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<<"Select Specialization:";
    }
    cout<<endl;
    switch(spec){
        case 1: file6<<left<<setw(MAX_TEST_LEN)<<"BP"<<',';    break;
        case 2: file6<<left<<setw(MAX_TEST_LEN)<<"SUGAR"<<','; break;
        case 3: file6<<left<<setw(MAX_TEST_LEN)<<"CT SCAN"<<',';   break;
        case 4: file6<<left<<setw(MAX_TEST_LEN)<<"ULTRASOUND"<<',';    break;
        case 5: file6<<left<<setw(MAX_TEST_LEN)<<"COVID"<<','; break;
        case 6: file6<<left<<setw(MAX_TEST_LEN)<<"MRI"<<',';   break;
        case 7: file6<<left<<setw(MAX_TEST_LEN)<<"BLOOD"<<','; break;
        case 8: file6<<left<<setw(MAX_TEST_LEN)<<"URINE"<<','; break;
        default: count++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count != 0){
        goto x1;
    }

x7:
    fflush(stdin);
    cout<<"Enter Patients attending per day:";
    cin.getline(ppd, 4);
    int d5 = 0, nd5 = 0;
    for(int i =0; ppd[i] != '\0'; i++){

        if(isdigit(ppd[i])){
            d5++;
        } else {
            nd5++;
        }
    }
    if(nd5 != 0){
        cout<<"ERROR:INVALID ENTRY!"<<endl;
        goto x7;
    }
    file6<<setw(4)<<ppd<<',';

x3:
    fflush(stdin);
    bool ok;
    cout<<"Enter no. of Working Hours:";
    cin>>wh;

    while(!ok){
            //cout<<"Enter no. of Working Hours:";
            cin>>wh;
        if(!cin.fail() && (cin.peek() == EOF || cin.peek() == '\n')){
            ok = true;
        } else {
            cout<<"ERROR: INVALID!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
    if(wh > 16 || wh <= 0){
        cout<<"ERROR: INVALID!"<<endl;
        goto x3;
    }
    file6<<setw(4)<<wh<<',';

x4:
    fflush(stdin);
    cout<<"Press an appropriate button for the following TEST options:-"<<endl;
    cout<<"1 - DAY"<<endl<<"2 - NIGHT"<<endl;
    int count1 = 0;
    cout<<"Select Shift:";
    while(!(cin >> shift)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<<"Select Shift:";
    }
    cout<<endl;
    switch(shift){
        case 1: file6<<' '<<left<<setw(6)<<"DAY"<<',';    break;
        case 2: file6<<' '<<left<<setw(6)<<"NIGHT"<<','; break;
        default: count1++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count1 != 0){
        goto x4;
    }


x5:
    fflush(stdin);
    cout<<"Enter Physician's Salary:";    cin.getline(sal, 7);  cout<<endl;
    int d3 = 0, nd3 = 0;
    for(int i =0;sal[i] != '\0'; i++){

        if(isdigit(sal[i])){
            d3++;
        } else {
            nd3++;
        }
    }
    if(nd3 !=0){
        cout<<"You have entered non-numeric value:"<<endl;
        goto x5;
    }
    file6<<setw(9)<<sal<<','<<endl;


    int n;
    cout<< "Do you want to add another record?";
    while(!(cin >> n)){
        cout<<"Error: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout<< "Do you want to add another record?";
    }
    cout<<endl;
    if(n == 1){
        system("cls");
        goto z;
    }

    file6.close();
}

void Files::enquiry(){
    system("cls");
    ifstream file7;
    file7.open("enquiry.txt", ios::in);
    if (!file7.is_open()) {
        cout << "Error while opening file." << endl;
    }
    string line;
    while (file7.good()) {
        getline(file7, line, ',');
        cout << line;
    }
    file7.close();
}

void Files::rep_data(){
    system("cls");
    fstream file8;
    file8.open("report_data.txt", ios::in);
    if (!file8.is_open()) {
        cout << "Error while opening file." << endl;
    }
    string line;
    cout<<"****************************************************************************************************"<<endl;
    cout<<"RID   PID   PATIENT NAME        TEST       REP_ST"<<endl;
    cout<<"****************************************************************************************************"<<endl;
    while (file8.good()) {
        getline(file8, line, ',');
        cout << line;
    }
    cout<<"****************************************************************************************************"<<endl;
    file8.close();
}

void Files::add_rep_data(){

    system("cls");

    char rid[5], pid[5], pname[25];
    int test, rep_st;

    fstream file9;
    file9.open("report_data.txt", ios::out | ios::app);
    if (!file9.is_open()) {
        cout << "Error while opening file." << endl;
    }
y:
    cout<<"Entering a Report Record..."<<endl;

x3:
    fflush(stdin);
    cout<<"Enter Report ID:";   cin.getline(rid, MAX_ID_LEN);  cout<<endl;
    int alnum = 0, nalnum = 0;
    for(int i = 0; rid[i] != '\0'; i++){
        if(isalnum(rid[i])){
            alnum++;
        } else {
            nalnum++;
        }
    }
    if(nalnum != 0){
        cout<<"You have entered INVALID value for this field!"<<endl;
        goto x3;
    }
    file9<<left<<setw(MAX_ID_LEN)<<rid<<',';

x4:
    fflush(stdin);
    cout<<"Enter Patient ID:";  cin.getline(pid, MAX_ID_LEN);  cout<<endl;
    int alnum1 = 0, nalnum1 = 0;
    for(int i = 0; pid[i] != '\0'; i++){
        if(isalnum(pid[i])){
            alnum1++;
        } else {
            nalnum1++;
        }
    }
    if(nalnum1 != 0){
        cout<<"You have entered INVALID value for this field!"<<endl;
        goto x4;
    }
    file9<<left<<setw(MAX_ID_LEN)<<pid<<',';

x:
    fflush(stdin);
    cout<<"Enter Patient Name:";  cin.getline(pname, MAX_NAME_LEN);  cout<<endl;
    int alpha=0, nalpha=0;
    for(int i =0;pname[i] != '\0'; i++){

        if(isalpha(pname[i]) || pname[i]==32 || pname[i] == 46){
            alpha++;

        } else {
            nalpha++;

        }
    }
    if(nalpha !=0){
        cout<<"You have entered non-alphabetic value:"<<endl;
        goto x;
    }
    file9<<left<<setw(MAX_NAME_LEN)<<pname<<',';

x1:
    fflush(stdin);
    cout<<"Press an appropriate button for the following TEST options:-"<<endl;

    cout<<"1 - BP"<<endl<<"2 - SUGAR"<<endl<<"3 - CT SCAN"<<endl<<"4 - ULTRASOUND"<<endl<<"5 - COVID"<<endl<<"6 - MRI"<<endl<<"7 - BLOOD"<<endl<<"8 - URINE"<<endl;
    int count = 0;
    cout<<"Select Test:";
    while(!(cin >> test)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<<"Select Test:";
    }
    cout<<endl;
    switch(test){
        case 1: file9<<left<<setw(MAX_TEST_LEN)<<"BP"<<',';    break;
        case 2: file9<<left<<setw(MAX_TEST_LEN)<<"SUGAR"<<','; break;
        case 3: file9<<left<<setw(MAX_TEST_LEN)<<"CT SCAN"<<',';   break;
        case 4: file9<<left<<setw(MAX_TEST_LEN)<<"ULTRASOUND"<<',';    break;
        case 5: file9<<left<<setw(MAX_TEST_LEN)<<"COVID"<<','; break;
        case 6: file9<<left<<setw(MAX_TEST_LEN)<<"MRI"<<',';   break;
        case 7: file9<<left<<setw(MAX_TEST_LEN)<<"BLOOD"<<','; break;
        case 8: file9<<left<<setw(MAX_TEST_LEN)<<"URINE"<<','; break;
        default: count++; cout<<"An INVALID option selected!"<<endl;
    }
    if(count != 0){
        goto x1;
    }


x2:
    fflush(stdin);
    cout<<"Press an appropriate button for selecting an option:-"<<endl;
    cout<<"1 - Collected"<<endl<<"2 - Pending"<<endl;
    cout<<"Select Report Status:";
    while(!(cin >> rep_st)){
     cout<<"Error: Only a number must be entered!"<<endl;

     cin.clear();

     cin.ignore(123, '\n');
     cout<< "Do you want to add another record?:";
}
    cout<<endl;
    int wr=0;
    switch(rep_st){
        case 1: file9<<left<<setw(10)<<"Collected"<<','<<endl; break;
        case 2: file9<<left<<setw(10)<<"Pending"<<','<<endl; break;
        default:    wr++; cout<<"INVALID option selected!"<<endl;
    }
    if(wr != 0){
        goto x2;
    }

    int n;
    cout<< "Do you want to add another record?";
    while(!(cin >> n)){
        cout<<"Error: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout<< "Do you want to add another record?";
    }
    cout<<endl;
    if(n == 1){
        system("cls");
        goto y;
    }

    file9.close();
}

void Files::test_data(){
    system("cls");
    fstream filex;
    filex.open("test_data.txt", ios::in);
    string line;
    if (!filex.is_open()) {
        cout << "Error while opening file." << endl;
    }
    while (filex.good())
    {
        getline(filex, line, ',');
        cout << line;
    }
    filex.close();
}


//Function definition of a member function of class Modules
void Modules::admin() {
    system("cls");

    int c2, c5; x4:
    cout << "\t\t\t\t\t=========================================================================" << endl;
    cout << "\t\t\t\t\t|\t\t\tADMIN MODE MENU\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t=========================================================================" << endl;
    cout << "\t\t\t\t\t| 1 - View Patient's Data\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t-------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t| 2 - View Payment's Data\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t-------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t| 3 - View Physician's Data\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t-------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t| 4 - View Test Report's Data\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t-------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t| 5 - Add to Physician's Data\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t=========================================================================" << endl;
    cout << "\t\t\t\t\tPress an appropriate button for selecting an option: ";
    cin >> c2;
    switch (c2) {
    case 0: system("cls"); choice(); break;
    case 1: cout << "Patients Data Selected!" << endl;
        f1.pat_data();
        break;
    case 2: cout << "Payment Data Selected!" << endl;
        f1.pay_data();
        break;
    case 3: cout << "Physicians Data Selected!" << endl;
        f1.phy_data();
        break;
    case 4: cout << "Tests Data Selected!" << endl;
        f1.test_data();
        break;
    case 5: cout << "Adding the Physicians data!" << endl;
        f1.add_phy_data();
        break;
    default: cout << "An inappropriate button entered!" << endl;
        goto x4;
    }
    cout << endl << "Return back to select a different option - Press 0 for 'NO' or 1 for 'Yes':";
    cin >> c5;
    switch (c5) {
    case 0: cout << "Exiting from ADMIN MODE..."; break;
    case 1:  system("cls"); goto x4; break;
    default: cout << "An INVALID button pressed!" << endl;
    }
}

//Function definition of a member function of class Modules
void Modules::user() { //user mode function of void type
    system("cls");
    cout<<endl<<endl<<endl;
    int c3, c4;
x6:
    cout << "\t\t\t\t================================================================================================" << endl;
    cout << "\t\t\t\t\t\t\t\t\tUSER MODE MENU"<<endl;
    cout << "\t\t\t\t================================================================================================" << endl;
    cout << "\t\t\t\t 1 - Add to Patient's Data" << endl;
    cout << "\t\t\t\t=-----------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 2 - View Patient's Data" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 3 - View Enquiry Pointers" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 4 - View Tests Data" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 5 - Add to Payment's Data" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 6 - View Payment's Data" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 7 - Add to Test Reports Data" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t 8 - View Test Reports Data" << endl;
    cout << "\t\t\t\t================================================================================================" << endl;
    cout << "\t\t\t\tPress an appropriate button for selecting an option: ";
    while(!(cin >> c3)){
        cout<<"\t\t\t\t\tError: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout << "\t\t\t\tPress an appropriate button for selecting an option: ";
    }

    switch (c3) {
    case 0: system("cls"); choice(); break;
    case 1: cout << "Adding Patients selected!" << endl;
        f1.add_pat_data();
        break;
    case 2: cout << "Patients Data Selected!" << endl;
        f1.pat_data();
        break;
    case 3: cout << "Enquiry pointers Selected!" << endl;
        f1.enquiry();
        break;
    case 4: cout << "Tests Data Selected." << endl;
        f1.test_data();
        break;
    case 5: cout << "Adding records to payment's data" << endl;
        f1.add_pay_data();
        break;
    case 6: cout << "Payment Data Selected!" << endl;
        f1.pay_data();
        break;
    case 7: cout << "Adding records to Test Reports Data Selected!" << endl;
        f1.add_rep_data();
        break;
    case 8: cout << "Test Reports Data Selected!" << endl;
        f1.rep_data();
        break;
    default: cout << "An INVALID button pressed!" << endl;
        goto x6;
    }
    cout << endl << endl;
    cout << "Return back to select a different option - Press 0 for 'NO' or 1 for 'Yes':";
    while(!(cin >> c4)){
        cout<<"\t\t\t\t\tError: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout << "\t\t\tReturn back to select a different option - Press 0 for 'NO' or 1 for 'Yes':";
    }
    switch (c4) {
    case 0: cout << "Exiting from USER MODE..."; break;
    case 1: system("cls");  goto x6; break;
    default: cout << "An INVALID button pressed!" << endl;
    }
}

void Modules::choice() { //choice function of void type to choose between admin mode and user mode
    int c1;
    xx:
    //designing
    cout<<"\n\n\n\n";
    cout << "\t\t\t\t\t|=======================================================================|";
    cout << endl << "\t\t\t\t\t|\t\t\tSAHIL PATHOLOGY LABORATORY\t\t\t|" << endl;
    cout << "\t\t\t\t\t|=======================================================================|";
    cout << endl << "\t\t\t\t\t|   1 - ADMIN MODE\t\t\t\t\t\t\t|" << endl;
    cout << "\t\t\t\t\t|-----------------------------------------------------------------------|";
    cout << endl << "\t\t\t\t\t|   2 - USER MODE\t\t\t\t\t\t\t|" << endl ;
    cout << "\t\t\t\t\t|=======================================================================|" << endl<<endl;
x3: cout << "\t\t\t\t\tChoose the type of user via pressing an appropriate button:";
    while(!(cin >> c1)){
        cout<<"\t\t\t\t\tError: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout << "\t\t\t\t\tChoose the type of user via pressing an appropriate button:";
    }
    cout << endl<<endl;
    string admin_id, admin_password;
    admin_id = "admin";
    admin_password = "admin";
    string user_id = "user";
    string user_password = "user";
    //LOGIC
    string a_id;
    char a_pswd[20];
    char ch;
    string u_id;
    char u_pswd[20];
    char ch2;
    if (c1 == 1) {
        cout << "\tADMIN MODE selected:" << endl;     xy:
        cout << "\tEnter admin id:"; cin >> a_id;
    x1:  cout << endl << "\tEnter admin password:";
    int o = 0;
    while(ch = getch()){
    //ch = getch();
    if(ch == 13){
        a_pswd[o] = '\0';
        break;
    } else {
        a_pswd[o++] = ch;
        cout<<"*";
    }
    }

     if (a_id == admin_id && a_pswd == admin_password) {
        admin();    //calling admin function for void type
    }
    else if(a_id != admin_id && a_pswd != admin_password) {
        cout << "\tBoth username and password are incorrect!" << endl;
        goto xy;
    }
    else if (a_id != admin_id) {
            cout << "\tIncorrect username!" << endl;;
            goto xy;
    }
    else if (a_pswd != admin_password) {
        cout << "\tIncorrect password!" << endl;
        goto x1;
    }
    }
    else if (c1 == 2) {
        cout << "\tUser MODE selected:" << endl;
    xz: cout << "\tEnter user id:"; cin >> u_id;
    x2: cout << endl << "\tEnter user password:";
        int r = 0;
        while(ch2 = getch()){
        if(ch2 == 13){
            u_pswd[r] = '\0';
            break;
        } else {
            u_pswd[r++] = ch2;
            cout<<"*";
        }
        }
        if (u_id == user_id && u_pswd == user_password) {
            user();
        }
        if (u_id != user_id) {
            cout << "\nIncorrect username!" << endl;;
            goto xz;
        }
        if (u_pswd != user_password) {
            cout << "\nIncorrect password!" << endl;
            goto x2;
        }
    }
    else {
        cout << "\tInvalid button pressed!" << endl;
        goto x3;
    }

    int cx;
    cout << "\tWant to change between ADMIN or USER MODES?" << endl;
    cout << "\tPress 0 - No or 1 for Yes:";
    while(!(cin >> cx)){
        cout<<"\t\t\t\t\tError: Only a number must be entered!"<<endl;

        cin.clear();

        cin.ignore(123, '\n');
        cout << "\t\t\t\t\tWant to change between ADMIN or USER MODES?" << endl;
        cout << "\t\t\t\t\tPress 0 - No or 1 for Yes:";
    }
    if (cx == 1) {
        system("cls");
        goto xx;
    }
    else {
        exit(0);
    }
}

int main()
{
    system("Color 0F");
    Modules m;
    m.choice();
    return 0;
}
