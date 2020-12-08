#include<iostream>
#include<iomanip>
#include<cctype>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;

class bank{
    long long acno;
    char name[20];
    char actype;
    long long mno;
    int amt;

    public:
    void create_acc();
    int dep_amt(int a); 
    int withdraw(int a);
    void modify();
    void show_acc();
    void showAll_acc();
    void del_acc();
    int retac();
    int retdep();
    int rettype();
};

void bank::create_acc(){
    cout<<"Enter the name: ";
    char name1[20];
    cin.ignore();
    cin.getline(name1,20);
    for(int i=0;i<20;i++)
        name[i]=' ';
    for(int i=0;name1[i]!='\0';i++)
        name[i]=name1[i];
    cout<<"Enter Account number: ";
    cin>>acno;
    cout<<"Enter account type(C/S): ";
    cin>>actype;
    actype=toupper(actype);
    cout<<"Enter Mobile number: ";
    cin>>mno;
    cout<<"Enter Initial Amount(>=500 for Savings and >=1000 for Current): ";
    cin>>amt;
    cout<<"Account created successfully"<<endl;
}

int bank::dep_amt(int a){
    amt+=a;
}

int bank::withdraw(int a){
    amt-=a;
}

void bank::modify(){
    cout<<"Account number: "<<acno<<endl;
    cout<<"Enter new name: ";
    char name1[20];
    cin.ignore();
    cin.getline(name1,20);
    for(int i=0;i<20;i++)
        name[i]=' ';
    for(int i=0;name1[i]!='\0';i++)
        name[i]=name1[i];
    cout<<"Enter new Phone Number: ";
    cin>>mno;
    cout<<"Enter new Account Type: ";
    cin>>actype;
    actype=toupper(actype);
}

void bank::show_acc(){
    cout<<"Account Number: "<<acno<<endl;
    cout<<"Name: ";
    cout<<name<<endl;
    cout<<"Phone Number: "<<mno<<endl;
    cout<<"Account Type: "<<actype<<endl;
    cout<<"Balance: "<<amt<<endl;
}

void bank::showAll_acc(){
    cout<<acno<<setw(14)<<" "<<name<<setw(10)<<" "<<mno<<setw(10)<<" "<<amt<<endl;
}

int bank::retac(){
    return acno;
}

int bank::retdep(){
    return amt;
}

int bank::rettype(){
    return actype;
}

void write();
void dep_with(int , int);
void modify_acc(int);
void show(int);
void show_all();
void delete_acc(int);

int main(){
    int i;
    int num;
    do{
        cout<<"\n\t MAIN MENU"<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposit Amount"<<endl;
        cout<<"3. Withdraw Amount"<<endl;
        cout<<"4. Modify Account"<<endl;
        cout<<"5. Show Account"<<endl;
        cout<<"6. Show All Account"<<endl;
        cout<<"7. Delete Account"<<endl;
        cout<<"8. Exit"<<endl;
        cout<<"Enter your choice(1-8): ";
        cin>>i;
        switch(i){
            case 1: cout<<"\t Create Account\n";
                    write();
                    break;
            case 2: cout<<"\t Deposit Amount"<<endl;
                    cout<<"Enter the account number: ";
                    cin>>num;
                    dep_with(num,1);
                    break;
            case 3: cout<<"\t Withdraw Amount"<<endl;
                    cout<<"Enter the account number: ";
                    cin>>num;
                    dep_with(num,2);
                    break;
            case 4: cout<<"\t Modify Account"<<endl;
                    cout<<"Enter the account number: ";
                    cin>>num;
                    modify_acc(num);
                    break;
            case 5: cout<<"\t Showing Account"<<endl; 
                    cout<<"Enter the account number: ";
                    cin>>num;
                    show(num);
                    break;
            case 6: show_all();
                    break;
            case 7: cout<<"\t Delete Account"<<endl;
                    cout<<"Enter the account number: ";
                    cin>>num;
                    delete_acc(num);
                    break;
            case 8: cout<<"\t Exited";
                    break; 
            default: cout<<"Invalid Choice";
                     break;
        }
    }while(i!=8);
    return 0;
}

void write(){
    bank b;
    ofstream o;
    o.open("account.dat",ios::binary|ios::app);
    b.create_acc();
    o.write(reinterpret_cast<char *>(&b),sizeof(bank));
    o.close();
}

void dep_with(int num, int a){
    bank b;
    int n;
    bool found=false;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"File not found";
        return;
    }
    while(!file.eof() && found==false){
        file.read(reinterpret_cast<char *> (&b),sizeof(bank));
        if(num==b.retac()){
            b.show_acc();
            if(a==1){
                cout<<"Enter the amount to be deposited: ";
                cin>>n;
                b.dep_amt(n);
            }
            if(a==2){
                cout<<"Enter the amount to be withdrawn: ";
                cin>>n;
                int left=b.retdep()-n;
                if((left<500 && b.rettype()=='S') || (left<1000 && b.rettype()=='C'))
                cout<<"Not enough balance";
                else b.withdraw(n);
            }
            int position=(-1)*static_cast<int>(sizeof(b));
            file.seekp(position,ios::cur);
            file.write(reinterpret_cast<char *>(&b),sizeof(bank));
            cout<<"\n\tAccount Updated";
            found=true;
        }
    }
    file.close();
    if(found==false)
    cout<<"Account not found";
}

void modify_acc(int num){
    bool found=false;
    bank b;
    fstream file;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"File could not be opened";
        return;
    }
    while(!file.eof() && found==false){
        file.read(reinterpret_cast<char*> (&b),sizeof(bank));
        if(b.retac()==num){
            b.show_acc();
            cout<<"\n\t\tEnter new details of the account\n"<<endl;
            b.modify();
            int position=(-1)*static_cast<int>(sizeof(bank));
            file.seekp(position,ios::cur);
            file.write(reinterpret_cast<char *> (&b), sizeof(bank));
            cout<<"\n\tAccount modified";
            found=true;
        }
    }
    file.close();
    if(found==false)
    cout<<"Account not found";
}

void delete_acc(int num){
    bank b;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"File could not be opened";
        return;
    }
    outfile.open("Temp.dat",ios::binary);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char *> (&b), sizeof(bank))){
        if(b.retac()!=num){
            outfile.write(reinterpret_cast<char *> (&b), sizeof(bank));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    cout<<"\n\tAccount deleted";
    rename("Temp.dat","account.dat");
}

void show(int num){
    bank b;
    bool found=false;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"File could not be opened";
        return;
    }
    cout<<"\n--------Account Datails---------\n";
    while(infile.read(reinterpret_cast<char *> (&b), sizeof(bank))){
        if(b.retac()==num){
            b.show_acc();
            found=true;
        }
    }
    infile.close();
    if(found==false)
    cout<<"\n\t Account does not exist";
}

void show_all(){
    bank b;
    ifstream infile;
    infile.open("account.dat",ios::binary);
    if(!infile){
        cout<<"File could not be open";
        return;
    }
    cout<<"\n\n\t\t\t\t\t[ACCOUNT LIST]\n\n";
    cout<<"================================================================================================\n";
    cout<<"A/c no.           Name               Type        Mobile              Balance\n";
    cout<<"================================================================================================\n";
    while(infile.read(reinterpret_cast<char *> (&b), sizeof(bank))){
        b.showAll_acc();
    }
    infile.close();
}