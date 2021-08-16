#include <bits/stdc++.h>
using namespace std;
class Fresher;
class Employee;
class Lead;
enum CallStatus {ONGOING, WAITING, TERMINATED};
enum CallTaker {FRESHER, LEAD, MANAGER};

class Customer
{
    private :
        int id;
        string name;
        string phone_no;

    public :
        Customer(int id, string name, string phone_no)
        {
            this -> id = id;
            this -> name = name;
            this -> phone_no = phone_no;
        }

        int getID(){ return id; }
        string getName(){ return name; }
        string getNumber(){ return phone_no; }
        void displayInfo()
        {
            cout << "ID : " << id << "\n";
            cout << "Name : " << name << "\n";
            cout << "Phone Number : " << phone_no << " \n";
        }
};
class Call
{
    private :
        int id;
        string location;
        int duration;
        Customer* customer;
        Employee* employee;
        CallStatus call_status;
        CallTaker call_taker;

    public :
        Call(int id, string location, int duration, Customer* customer, Employee* employee)
        {
            this -> id = id;
            this -> location = location;
            this -> duration = duration;
            this -> customer = customer;
            this -> employee = employee;
            call_status = WAITING;
            call_taker = FRESHER;
        }
        int getID(){ return id; }
        string getLocation(){ return location; }
        int getDuration(){ return duration; }
        Customer* getCaller(){ return customer; }
        int getStatus(){ return call_status; }
        int getReciver(){ return call_taker; }
        Employee* getReciverInfo(){ return employee; }
        void displayInfo()
        {
            cout << "ID : " << id << "\n";
            cout << "Location : " << location << "\n";
            cout << "Duration : " << duration << "\n";
            cout << "Number : " << customer -> getNumber() << "\n";
            cout << "Call Status : ";
            switch(call_status)
            {
                case ONGOING : cout << "Ongoing\n";
                             break;
                case WAITING : cout << "Waiting\n";
                            break;
                case TERMINATED : cout << "Terminated\n";
                            break;
            }
            cout << "Reciever : ";
            switch(call_taker)
            {
                case FRESHER : cout << "Fresher\n";
                             break;
                case LEAD : cout << "Lead\n";
                            break;
                case MANAGER : cout << "Manager\n";
                            break;
            }
        }
        void setStatus(CallStatus status)
        {
            call_status = status;
        }
        void setReciever(CallTaker reciever)
        {
            call_taker = reciever;
        }
        void setDuration(int duration)
        {
            this -> duration = duration;
        }
        void setRecieverInfo(Employee* employee)
        {
            this -> employee = employee;
        }
};
class Employee
{
    private :
        int id;
        string name;
        int waiting_time = 0;
        queue<Call*> calls;

    public :
        Employee()
        {

        }
        Employee(int id, string name)
        {
            this -> id = id;
            this -> name = name;
        }
        int getID(){ return id; }
        string getName(){ return name; }
        int getWaitTime(){ return waiting_time; }
        void displayInfo()
        {
            cout << "ID : " << id << "\n";
            cout << "Name : " << name << "\n";
            cout << "Waiting Time : " << waiting_time << " minutes.\n";
        }

        bool isFree(){ return calls.size() == 0; }
        int callsOnHold(){ return calls.size(); }
        Call* getCurrentCall(){ return calls.front(); }
        void addCall(Call* call)
        {
            if(!calls.size())
                call -> setStatus(ONGOING);
            else
                call -> setStatus(WAITING);

            calls.push(call);
            waiting_time += call -> getDuration();
        }
        bool endCurrentCall()
        {
            if(!calls.size()) return false;
            waiting_time -= calls.front() -> getDuration();
            calls.front() -> setStatus(TERMINATED);
            calls.pop();
            if(calls.size())
                calls.front() -> setStatus(ONGOING);
            return true;
        }

};
class Manager : public Employee
{
    private :

    public :
        Manager(int id, string name) : Employee(id, name){ }

};
class Lead : public Employee
{
    private :
        Manager* manager;
        map<int, Fresher*> freshers;

    public :
        Lead(int id, string name, Manager* manager) : Employee(id, name)
        {
            this -> manager = manager;
        }
        Fresher* getFresher(int fresher_id)
        {
            if(!freshers.count(fresher_id)) return NULL;
            return freshers[fresher_id];
        }
        Manager* getManager()
        {
            return manager;
        }
        void transferCall(int call_duration) // new call duration of after transferCall to supervisor.
        {
            Call *current_call = getCurrentCall();
            endCurrentCall();
            current_call -> setDuration(call_duration);
            current_call -> setReciever(MANAGER);
            current_call -> setRecieverInfo(manager);
            manager -> addCall(current_call);
        }
        friend void addFresher(Fresher* fresher);
};
class Fresher : public Employee
{
    private :
        Lead* lead;

    public :
        Fresher(int id, string name, Lead* lead) : Employee(id, name)
        {
            this -> lead = lead;
            addFresher(this);
        }
        void transferCall(int call_duration)
        {
            Call *current_call = getCurrentCall();
            endCurrentCall();
            current_call -> setDuration(call_duration);
            current_call -> setReciever(LEAD);
            current_call -> setRecieverInfo(lead);
            lead -> addCall(current_call);
        }
        Lead* getLead()
        {
            return lead;
        }
        friend void addFresher(Fresher*);
};
void addFresher(Fresher* fresher)
{
    Lead* lead = fresher -> lead;
    lead -> freshers.insert({fresher -> getID(), fresher});
}
int main()
{
    // Create atleast 1 customer, manager, lead, fresher and Call made by Customer.
    Customer customer_1(1, "Customer", "9876543210");
    Manager manager(0, "Manager");
    Lead lead_1(1, "Lead", &manager);
    Fresher fresher_1(2, "Ashish", &lead_1);
    Call call_1(1, "India", 20, &customer_1, &fresher_1);

    // Assign call to the fresher
    fresher_1.addCall(&call_1);
    cout << "Call Status : \n";
    call_1.displayInfo();
    cout << "\n";
    cout << "Fresher Status : \n";
    fresher_1.displayInfo();

    // Forward the call to Lead
    cout << "\n Transferring call to Lead...\n";
    fresher_1.transferCall(10);
    cout << "Call Status : \n";
    call_1.displayInfo();
    cout << "\n";
    fresher_1.displayInfo();

    Employee* reciever = call_1.getReciverInfo();
    cout << "\n";
    reciever -> displayInfo();
    return 0;
}
