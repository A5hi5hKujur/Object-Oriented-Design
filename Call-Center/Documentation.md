<h1>Problem Statement :</h1>

There is a call center in which there is a hierarchy of employees who can attend the call. Freshers should attend the call first, followed by leads and finally the manager. If the fresher wants to escalate the call he/she can escalate it to the leads. Also, a lead can escalate the call to the manager. We can suppose that there are many freshers, many leads, and only one manager. If at any point in time no employees are free to attend the call, the caller should wait in the queue. Once an employee is free he/she can take the call.

<h2>Classes :</h2>

1. Customer
2. Call
3. Employee
    - Fresher
    - Lead
    - Manager

<h3>Customer Class :</h3>

- Private Class Members :
1. **id :** Customer id to uniquely identify customer of a call center.
2. **name :** Customer name
3. **phone_no :** Customer phone

- Public Class Members :
1. **Customer(id, name, phone_no) :** Constructor that initializes the private members of the customer object.  
2. **getID() :** returns customer id (int).
3. **getName() :** returns customer name (string).
4. **getNumber() :** return customer phone number (string).
5. **displayInfo() :** display the private members of customer object.

<h3>Call Class :</h3>

- Private Class Members :
1. **id :** Call id to uniquely identify calls made to the call center. (int)
2. **location :** Location from which the call came from. (string)
3. **duration :** Time (in minutes) till which the call will last. (int)
4. **customer :** Stores the pointer to the customer who made the call. (Customer*)
5. **employee :** Stores the pointer to the employee who is attending to the customer (Employee*)
6. **call_status :** Status of the call can either be ONGOING, WAITING, TERMINATED. (CallStatus)
7. **call_taker :** Status of which employee is attending to the customer FRESHER, LEAD, MANAGER (CallTaker)

- Public Class Members :
1. **Call(id, location, duration, customer, employee) :** Constructor that initializes the private members of the call object.
2. **getID() :** returns id of the call. (int)
3. **getLocation() :** returns location from where the call came from. (string)
4. **getDuration() :** returns the duration of the call. (int)
5. **getCaller() :** returns the pointer to the customer's object who made the call. (Customer*)
6. **getStatus() :** returns call status. (CallStatus)
7. **getReciever() :** returns identity of the customer who is attending the call. (CallTaker)
8. **getRecieverInfo() :** returns the pointer to the Employee who is attending the customer's call. (Employee*)
9. **displayInfo() :** display the information of the call.
10. **setStatus(CallStatus) :** update call status.
11. **setReciever(CallTaker) :** update call taker's identity.
12. **setDuration(duration) :** update the duration of call.
13. **setRecieverInfo(employee) :** update the pointer to the employee who is attending the customer's call.

<h3>Employee Class :</h3>

- Private Class Members :
1. **id :** Employee id that uniquely identifies the employee. (int)
2. **name :** Employee name. (string)
3. **waiting_time :** Time in minutes till which the employee can attend a new call. (int)
4. **calls :** queue which stores the pointer to the calls that an employee as to attend. (queue<Call*>)

- Public Class Members :
1. **Employee() :** Default constructor, currently empty.
2. **Employee(id, name) :** Constructor to initialize new employee.
3. **getID() :** returns employee's id. (int)
4. **getName() :** returns employee's name. (string)
5. **getWaitTime() :** returns employee's wait time in minutes till the employee attends a new call. (int)
6. **displayInfo() :** displays information about an employee.
7. **isFree() :** checks if the employee is free to attend a new call. (bool)
8. **callsOnHold() :** returns the number of calls in queue. (int)
9. **getCurrentCall() :** returns the pointer to call the employee is attending at the momement (Call*)
10. **addCall(call) :** adds a new call to the employee's call queue by changing, adding into an employee's wait time.
If call queue is empty the call status is ONGOING otherwise it is WAITING.
11. **endCurrentCall() :** end the current call from top of the call queue. duration of the call is deduced from the waiting time of the employee, change status of the call and return true when this process is successful. False when it fails. (bool)

<h3>Manager Class :</h3>
- Private Class Members :

- Public Class Members :
1. **Manager(id, name) :** Calls the base class constructor of employee to initialize name and id.

<h3>Lead Class :</h3>

- Private Class Members :
1. **manager :** Stores pointer to the manager who supervises the lead.
2. **freshers :** Stores pointer to Freshers under the lead mapped to their id.

- Public Class Members :
1. **Lead(id, name, manager) :** Constructor that initializes name, id and manager info by calling the base constructor.
2. **getFresher(fresher_id) :** Get pointer to the Fresher working directly under lead. (Fresher*)
3. **getManager() :** Get pointer to the Manager working directly above lead (Manager*)
4. **transferCall(call_duration) :** Transfer's call to lead's manager with the new call_duration of the transferred call.
  - Store reference to the current call (call to transfer)
  - End current call
  - Update the duration of the call to transfer.
  - Update the information call to the manager.
  - Add call to the manager's queue.
5. **addFresher(fresher) :** A friend function which adds a new fresher to the freshers map of the manager object.

<h3 Fresher Class :</h3>

- Public Class Members :
1. **lead :** Stores the pointer to the lead directly above the fresher.

- Private Class Members :
1. **Fresher(id, name, lead) :** Constructor that initializes Fresher id, name by calling the base class constructor and assigning the lead as well as adding the fresher into the lead's map.
2. **transferCall(call_duration) :** Transfer's call to Fresher's lead with the new call_duration of the transferred call.
3. **getLead() :** get the pointer to the lead who supervises fresher.
4. **addFresher(fresher) :** A friend function which adds a new fresher to the freshers map of the manager object.
