#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Customer
{
  string name;
  int rankUnlocked;
  bool isCloser;
  int closerDay; //ONLY FOR CLOSERS
};

//if I'm inserting customers I should probably make a set? or some sort of insertable data structure

std :: vector<Customer> customersTotal; //total number of customers
std :: vector<Customer> customersAvailable;//customers available based on chefsRank,
std :: vector<Customer> Closers;//stores data into closer vectors
//could run the risk of duplicate customers
//replace whenever chefs rank increases and new customers are available

//string array to hold the days of the week
string days[7] = {"monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
int thisDay = 0;
int chefsRank = 1; //every chef starts out at rank 1
//increase rank
int increaseRank(int cRank)
{
  chefsRank += cRank;
  return chefsRank;
}
//increase the day by one
int nextDay(int currDay)
{
  currDay++;
  if(currDay > 6)
  {
    currDay = 0;
  }
  return currDay;
}

 //check for customers when the rank goes up
 void checkCustomers(Customer checkIt)
 {
     if(chefsRank >= checkIt.rankUnlocked)
     {
       customersAvailable.push_back(checkIt);
       cout << "Added customer: " << checkIt.name << endl;
     }
 }
 //sorts the closers based on day
 bool sortClosers(Customer closer, Customer closerComp)
 {
  //jojo is sunday, deano is monday, kahuna is tuesday, quinn wednesday, crystal thursday, radlynn friday, xolo saturday
   return (closer.closerDay < closerComp.closerDay);
 }

//I need to take customers from the vector at random, and insert them at random

//do a random hash to place random customers?
int myHash()
{

}

//return a vector? this returns an array now
Customer * generateDay(int thisDay, int customerLimit)
{
  //make sure to check if customers can be added

  Customer listDay[customerLimit+1];
  int count;
  //generate a day from customers available, MAKE SURE TO PUT THE CLOSER AT THE END
  for(auto daySim: customersAvailable)
  {
    if(count < customerLimit)
    {
    //puts closers at the end, need to randomly assign customers to array from vector
    if(daySim.isCloser == true && thisDay == daySim.closerDay)
    {
      //there's only one closer per day. I need to line up the closers with the correct day
      listDay[customerLimit] = daySim;
      count++;
    }
    else
    {
      //insert a random customer at any position aside from the end

    }
  }//checks to make sure the list thing doesn't go over the customer limit
}
  return listDay;
}

int main(void)
{
  //first, read in the customers
  Customer c;

  string nameIn, rankIn, closerIn;

  ifstream input("customers.txt");

  while(input >> nameIn >> rankIn >> closerIn)
  {
    c.name = nameIn;
    c.rankUnlocked = stoi(rankIn);
    if(closerIn == "true")
    {
        c.isCloser = true;
        //call this Papa's pastaria for this spaghetti code
        if(c.name == "jojo") c.closerDay = 6; //jojo is at the end
        if(c.name == "deano") c.closerDay = 0;
        if(c.name == "xolo") c.closerDay = 5;
        if(c.name == "quinn") c.closerDay = 2;
        if(c.name == "crystal") c.closerDay = 3;
        if(c.name == "kahuna") c.closerDay = 1;
        if(c.name == "radlynn") c.closerDay = 4;
        Closers.push_back(c);
    }
    else
    {
      c.isCloser = false;
    }
    customersTotal.push_back(c);
    checkCustomers(c);
  }
  //cout <<  customersTotal.size() << endl;
  input.close();
  sort(Closers.begin(),Closers.end(),sortClosers);
  //store customers currently available into the vector
  // currently checkCustomers can't be here by itself


  //testing printing out the total customers and the available customers
  cout << "all customers" <<endl;
  for(int i = 0; i<customersTotal.size(); i++)
  {
    cout << customersTotal[i].name << " " << customersTotal[i].rankUnlocked <<endl;
  }
  cout<< " " <<endl;
  cout << "customers currently available " <<endl;
  for(int i = 0; i<customersAvailable.size(); i++)
  {
    cout << customersAvailable[i].name << " " << customersAvailable[i].rankUnlocked << endl;
  }
  cout<< " " <<endl;
  cout << "Closers currently available "<<endl;
  for(int i = 0; i<Closers.size(); i++)
  {
    cout << Closers[i].name << endl;
  }

  string command;
  int rankUp;
  cout << "Welcome to the Papa Louie customer list simulator, type *help* to see the list of commands " << endl;
  while(1)
  {
    cin >> command;
    if (cin.eof()) break;

    if(command == "increaseRank")
    {
      //increase chef rank by user input.
      //check customer list to see if anyone can be added in to a possible day
     cout << "Your chef's rank was: " << chefsRank << " type the number of ranks you wish to level up your chef by " <<endl;
     cin >> rankUp;
     chefsRank = increaseRank(rankUp);
     cout << "Your chef's rank is now: " << chefsRank << endl;

     for(auto x: customersTotal)
     {
       checkCustomers(x);
     }

    }
    else if(command == "showDay")
    {
      //generates an average day at Papa Louie's restaurant
      //print out the day and customer of that day, start at monday
      cout << "Today is " << days[thisDay] << endl;
      cout << "Printing hypothetical customer list: " << endl;
    }
    else if(command == "nextDay")
    {
      //increase the day by 1, after day 7, loop back to day 1., day 1(monday) is at index 0
      //day 7(sunday) is on index 6
      thisDay = nextDay(thisDay);
      cout << "The day is now " << days[thisDay] << endl;
    }
    else if(command == "help")
    {
      cout << "type 'increaseRank' to increase the chef's rank, you can only increase the ranks, never decrease" << endl;
      cout << "type 'showDay' to generate a randomized customer order for the day, aside from the closer" <<endl;
      cout << "type 'nextDay' to move the day forward by 1" << endl;
      cout << "type 'quit' to exit the program" << endl;
    }
    else if(command == "quit")
    {
      break;
    }
    else
    {
      cout << "Unknown command, please type *help* to see a list of possible commands" << endl;
    }
    //based on papa's pastaria, depending on rank, customer count increases
  }
}
