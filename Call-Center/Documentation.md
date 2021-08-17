<h1>Problem Statement :</h1>

There is a call center in which there is a hierarchy of employees who can attend the call. Freshers should attend the call first, followed by leads and finally the manager. If the fresher wants to escalate the call he/she can escalate it to the leads. Also, a lead can escalate the call to the manager. We can suppose that there are many freshers, many leads, and only one manager. If at any point in time no employees are free to attend the call, the caller should wait in the queue. Once an employee is free he/she can take the call.


<h2>Constraints and assumptions :</h2>

What levels of employees are in the call center?
Fresher, Lead, Manager

Can we assume freshers always get the initial calls?
<p>Yes</p>

If there is no available freshers does the call go on waiting?
<p>Yes</p>

If the fresher can't handle the call, does the call go to the lead?
<p>Yes</p>

If there is no available lead, does the call go on waiting?
<p>Yes</p>

If the lead can't handle the call, does the call go to the manager?
<p>Yes</p>

Can we assume the managers can handle all calls?
<p>Yes</p>

What happens if nobody can answer the call?
<p>It gets queued</p>

Do we need to handle 'VIP' calls where we put someone to the front of the line?
<p>No</p>

Can we assume inputs are valid or do we have to validate them?
<p>Assume they are valid inputs</p>


<h2>Classes :</h2>

1. Customer
2. Call
3. Employee
    - Fresher
    - Lead
    - Manager

<h3>Customer Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>id</td>
    <td>Customer id to uniquely identify customer of a call center.</td>
  </tr>
  <tr>
    <td>name</td>
    <td>Customer name</td>
  </tr>
  <tr>
    <td>phone_no</td>
    <td>Customer phone</td>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Customer(id, name, phone_no)</td>
    <td>Constructor that initializes the private members of the customer object. </td>
  </tr>
  <tr>
    <td>getID()</td>
    <td>returns customer id (int).</td>
  </tr>
  <tr>
    <td>getName()</td>
    <td>returns customer name (string).</td>
  </tr>
   <tr>
    <td>getNumber()</td>
    <td>return customer phone number (string).</td>
  </tr>
    <tr>
    <td>displayInfo()</td>
    <td>display the private members of customer object.</td>
  </tr>
</table>

<h3>Call Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>id</td>
    <td>Call id to uniquely identify calls made to the call center. (int)</td>
  </tr>
  <tr>
    <td>location</td>
    <td>Location from which the call came from. (string)</td>
  </tr>
  <tr>
    <td>duration</td>
    <td>Time (in minutes) till which the call will last. (int)</td>
  </tr>
    <tr>
    <td>customer</td>
    <td>Stores the pointer to the customer who made the call. (Customer*)</td>
  </tr>
    <tr>
    <td>employee</td>
    <td>Stores the pointer to the employee who is attending to the customer (Employee*)</td>
  </tr>
    <tr>
    <td>call_status</td>
    <td>Status of the call can either be ONGOING, WAITING, TERMINATED. (CallStatus)</td>
  </tr>
    <tr>
    <td>call_taker</td>
    <td>Status of which employee is attending to the customer FRESHER, LEAD, MANAGER (CallTaker)</td>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Call(id, location, duration, customer, employee)</td>
    <td>Constructor that initializes the private members of the call object.</td>
  </tr>
  <tr>
    <td>getID()</td>
    <td>returns id of the call. (int)</td>
  </tr>
  <tr>
    <td>getLocation()</td>
    <td>returns location from where the call came from. (string)</td>
  </tr>
    <tr>
    <td>getDuration()</td>
    <td>returns the duration of the call. (int)</td>
  </tr>
  <tr>
    <td>getCaller()</td>
    <td>returns the pointer to the customer's object who made the call. (Customer*)</td>
  </tr>
    <tr>
    <td>getStatus()</td>
    <td>returns call status. (CallStatus)</td>
  </tr>
  <tr>
    <td>getReciever()</td>
    <td>returns identity of the customer who is attending the call. (CallTaker)</td>
  </tr>
  <tr>
    <td>getRecieverInfo()</td>
    <td>returns the pointer to the Employee who is attending the customer's call. (Employee*)</td>
  </tr>
  <tr>
    <td>displayInfo()</td>
    <td>display the information of the call.</td>
  </tr>
    <tr>
    <td>setStatus(CallStatus)</td>
    <td>update call status.</td>
  </tr>
  <tr>
    <td>setReciever(CallTaker)</td>
    <td>update call taker's identity.</td>
  </tr>
    <tr>
    <td>setDuration(duration)</td>
    <td>update the duration of call.</td>
  </tr>
  <tr>
    <td>setRecieverInfo(employee) </td>
    <td>update the pointer to the employee who is attending the customer's call.</td>
  </tr>
</table>

<h3>Employee Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>id</td>
    <td>Employee id that uniquely identifies the employee. (int)</td>
  </tr>
  <tr>
    <td>name</td>
    <td>Employee name. (string)</td>
  </tr>
  <tr>
    <td>waiting_time</td>
    <td>Time in minutes till which the employee can attend a new call. (int)</td>
  </tr>
  <tr>
    <td>calls</td>
    <td>queue which stores the pointer to the calls that an employee as to attend. (queue<Call*>)</td>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Employee()</td>
    <td> Default constructor, currently empty.</td>
  </tr>
  <tr>
    <td>Employee(id, name)</td>
    <td>Constructor to initialize new employee.</td>
  </tr>
  <tr>
    <td>getID()</td>
    <td>returns employee's id. (int)</td>
  </tr>
  <tr>
    <td>getName()</td>
    <td>returns employee's name. (string)</td>
  </tr>
   <tr>
    <td>getWaitTime()</td>
    <td> returns employee's wait time in minutes till the employee attends a new call. (int)</td>
  </tr>
  <tr>
    <td>displayInfo()</td>
    <td>displays information about an employee.</td>
  </tr>
  <tr>
    <td>isFree()</td>
    <td>checks if the employee is free to attend a new call. (bool)</td>
  </tr>
  <tr>
    <td>callsOnHold()</td>
    <td>returns the number of calls in queue. (int)</td>
  </tr>
  <tr>
    <td>getCurrentCall()</td>
    <td>returns the pointer to call the employee is attending at the momement (Call*)</td>
  </tr>
  <tr>
    <td>addCall(call)</td>
    <td>If call queue is empty the call status is ONGOING otherwise it is WAITING.</td>
  </tr>
  <tr>
    <td>endCurrentCall()</td>
    <td>end the current call from top of the call queue. duration of the call is deduced from the waiting time of the employee, change status of the call and return true when this process is successful. False when it fails. (bool)</td>
  </tr>
</table>

<h3>Manager Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Manager(id, name)</td>
    <td> Calls the base class constructor of employee to initialize name and id.</td>
  </tr>
</table>

<h3>Lead Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>manager</td>
    <td>Stores pointer to the manager who supervises the lead.</td>
  </tr>
  <tr>
    <td>freshers</td>
    <td>Stores pointer to Freshers under the lead mapped to their id.</td>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Lead(id, name, manager)</td>
    <td>Constructor that initializes name, id and manager info by calling the base constructor.</td>
  </tr>
  <tr>
    <td>getFresher(fresher_id)</td>
    <td>Get pointer to the Fresher working directly under lead. (Fresher*)</td>
  </tr>
  <tr>
    <td>getManager()</td>
    <td>Get pointer to the Manager working directly above lead (Manager*)</td>
  </tr>
  <tr>
    <td>transferCall(call_duration)</td>
    <td>Transfer's call to lead's manager with the new call_duration of the transferred call.</td>
  </tr>
   <tr>
    <td>addFresher(fresher)</td>
    <td>A friend function which adds a new fresher to the freshers map of the manager object.</td>
  </tr>
</table>

<h3> Fresher Class :</h3>

<table>
  <tr>
    <th>Private Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>lead</td>
    <td> Stores the pointer to the lead directly above the fresher.</td>
  </tr>
</table>

<table>
  <tr>
    <th>Public Class Members</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>Fresher(id, name, lead)</td>
    <td>Constructor that initializes Fresher id, name by calling the base class constructor and assigning the lead as well as adding the fresher into the lead's map.</td>
  </tr>
  <tr>
    <td>transferCall(call_duration) </td>
    <td>Transfer's call to Fresher's lead with the new call_duration of the transferred call.</td>
  </tr>
  <tr>
    <td>getLead()</td>
    <td>get the pointer to the lead who supervises fresher.</td>
  </tr>
  <tr>
    <td>addFresher(fresher)</td>
    <td>A friend function which adds a new fresher to the freshers map of the manager object.</td>
  </tr>
</table>

<h2> Object Oriented Concepts used : </h2>

<h3>1. Classes :</h3>
To encapsulate data into represent real world objects with abstraction to the private data memebers of the object. Here the system consists of 3 major objects that interact with each other:

<ul>
    <li>The employee</li>
    <li>The customer</li>
    <li>The call made by customer to an employee</li>
</ul>

Each entity of this system consist of properties and behavior to faciliate a call center.

<h3>2. Inheritance :</h3>
The employee of the call centers are divided into a hierarchy of supervisory roles where a fresher is at the bottom of that heirarchy who might have a single lead to whome he works under. A lead who supervises more than one freshers and a single manager who supervises multiple lead. With this heirarchy in place a fresher may not directly enguage with the manager nor the manager directly interacts with the fresher.

All employees have some basic traits that they all share among each other, for example : id, name, call queue, they can pick calls, they can end calls etc. These base traits are represented in a base class (Employee) to promote reusibility.

<h3>3. Base Constructor calling from derived class :</h3>
There is no such thing as super keyword in C++, each derived class constructor always calls a base constructor while initializing base attributes.

<h3>4. Friend Function Implimentation :</h3>
The feature to add a new fresher to the system involves pushing the fresher in the lead's fresher map which involves accessing the private memebers of Lead class and Fresher class which may not be possible to define as a class memeber of the lead class since even if canonically, fresher class is defined earlier than lead class it would still throw an invalid access to private members of the lead class since the lead class definition would be incomplete at the time addFresher() member function is encounted. Therefor we make addFresher as a friend of both Fresher and Lead class to access private memebers of both. The function is defined outside the class after both class definition are complete.

<h3>5. Base class pointer to refer derived class objects :</h3>

The call object has a private memeber which stores the refrence to the employee who is attending to the customer, since the employee can either be among the fresher, lead or the manager it seems best to use the base pointer to refer all these employees since derived class objects can be refered by base class pointers.

