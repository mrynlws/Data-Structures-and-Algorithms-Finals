#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <unistd.h> //sleep function
using namespace std;
namespace ns{
	
	struct movieInfo
	{
		string title, genre, production, filename;
		int mid, copy;
	}mDetails; //object 1
	
	struct customerInfo
	{
		string name, address; 
		int cid;
	}cDetails; //object 2
	
	struct customerRent
	{
		string rname, raddress, rtitle;
		int rcid, rmid;
	}rDetails; //object 3

/////////////////////////////////////////////

	list <movieInfo> movieList;
	list <movieInfo>::iterator mit;
	
	list <customerInfo> customerList;
	list <customerInfo>::iterator cit;
	
	list <customerRent> rentList;
	list <customerRent>::iterator rit;

////////////////////////////////////////////

class functionList
{   
    public:
    	//General Functions
    	void loadMemory();
    	void updateSave();
    	
    	//Movie Functions
        void addNode(); 
        void deleteNode();
        void returnNode();
        void displayList();
        bool movieSearch(int movieID);
        bool showPoster(int movieID);
        void showList();
        void checkNode();
		
		//Customer Functions
		void newCustomer();
		void displayCustomer();
		void listRented();
		
		// Customer Rent Functions
		bool rentSearch(int rentID);
		void movieRent();
};

////////////////////////////////////////////

void functionList::addNode() //Add a Movie
{	
	movieList.push_back(mDetails);
}

void functionList::deleteNode() //Rent a Movie
{
	bool csearch = false;
	
	for(cit = customerList.begin(); cit != customerList.end(); cit++)
	{
		if(cit->cid == cDetails.cid)
		{
			cDetails.name = cit->name;
			cDetails.address = cit->address;
			csearch = true;
		}

		else
		{
			continue;
		}
	}
	
	if(csearch == true)
    {
		
		for(mit = movieList.begin(); mit != movieList.end(); mit++)
	    {
	        if (mit->mid == mDetails.mid)
	        {
	        	
	        	if(mit->copy > 0)
	        	{
	        		cout << endl << "Movie Successfully Rented!" << endl;
			
					cout << "Movie ID        : " << mit->mid << endl
						 << "Movie Title     : " << mit->title << endl
						 << "Genre           : " << mit->genre << endl
						 << "Production      : " << mit->production << endl << endl
						 << "Updating number of copies..." << endl;
					
					mit->copy -= 1;
					cout << "Copies          : " << mit->copy << endl;
					
					mDetails.title = mit->title;
					movieRent();
					break;
				}
						
				else 
				{
					cout << "Error. No copies left!";
					break;
				}
			}
			
			else
			{
				continue;
			}
			
		}
	}
	
	else
	{
		cout << "Error. Invalid Customer/Movie ID!\n";
	}
}

void functionList::returnNode() //Return a Movie
{	
	bool rsearch = false;
	
	rDetails.rcid = cDetails.cid;

	for(rit = rentList.begin(); rit != rentList.end(); rit++)
	{
		if(rit->rcid == rDetails.rcid)
		{
			if (rit->rmid == rDetails.rmid)
			{	
				rentList.erase(rit);
				rsearch = true;
			}
			
			else
			{
				continue;
			}
		}

		else
		{
			continue;
		}
	}
	
	if (rsearch == true)
	{
		for(mit = movieList.begin(); mit != movieList.end(); mit++)
	    {
		
	        if (mit->mid == mDetails.mid)
	        {
	        	
	        	if(mit->copy > 0)
	        	{
	        		cout << endl << "Movie Successfully Returned!" << endl;
			
					cout << "Movie ID        : " << mit->mid << endl
						 << "Movie Title     : " << mit->title << endl
						 << "Genre           : " << mit->genre << endl
						 << "Production      : " << mit->production << endl << endl
						 << "Updating number of copies..." << endl;
					
					mit->copy += 1;
					cout << "Copies          : " << mit->copy << endl;
					
	        		break;
				}

				else
				{
					continue;
				}
			}

			else
			{
				continue;
			}
	    }
	}

	else
	{
		cout << "Error. Invalid Customer/Movie ID!";
	}
}

void functionList::displayList()
{	
	if (!movieSearch(mDetails.mid))
	{
		cout << "Error. The movie is not in the list!\n";
    }
    
    if (!showPoster(mDetails.mid))
	{
		cout << "Error. File not found!\n";
    }
}

bool functionList::movieSearch(int movieID)
{
	bool msearch = false;
	
	for(mit = movieList.begin(); mit != movieList.end(); mit++)
    {

	    if (mit->mid == movieID)
	    {
	    	msearch = true;
			cout << "Movie Title        : " << mit->title << endl;
			cout << "Genre              : " << mit->genre << endl;
			cout << "Production         : " << mit->production << endl;
			cout << "Copies             : " << mit->copy << endl;
	    	break;
		}
		
		else 
		{
			continue;
		}
	}
	return msearch;
}

bool functionList::showPoster(int movieID)
{
	bool msearch = false;
	
	for(mit = movieList.begin(); mit != movieList.end(); mit++)
	{
		if (mit->mid == movieID)
	    {
	    	msearch = true;
	    	//string poster = "C:\\darla\\images\\" + mit->filename; //darla
	    	
	    	string poster = "C:\\Users\\images\\" + mit->filename; //yannie path
			system(poster.c_str());
	    	break;
		}
		
		else 
		{
			continue;
		}
	}
	return msearch;
}

void functionList::showList() //Show All Movies in Table Form
{
	cout << "Movie ID\t"
		 << setw(40) << "Title\t"
		 << setw(40) << "Genre\t"
		 << setw(40) << "Production"
		 << setw(30) << "Number of Copies"
		 << endl;
			 			
	for(mit = movieList.begin(); mit != movieList.end(); mit++)
    {
        cout << endl
        	 << mit->mid
        	 << setw(50) << mit->title << "\t"
         	 << setw(40) << mit->genre << "\t"
         	 << setw(35) << mit->production
         	 << setw(20) << mit->copy << endl;
    }
}

void functionList::checkNode() //Check Availability
{
	
	cout << "-----------------------" << endl;
	
	if (!movieSearch(mDetails.mid))
	{
		cout << "Error. The movie is not on our list!\n";
    }
	
	//checks number of copies
    if (mit->copy > 0)
    {
    	cout << "Movie Status       : AVAILABLE" << endl;
	}
	
	else 
	{
		cout << "Movie Status       : NOT AVAILABLE" << endl;
	}
	
	if (!showPoster(mDetails.mid))
	{
		cout << "Error. File not found!\n";
    }
}

////////////////////////////////////////////

void functionList::newCustomer() //Add New Customer
{
	int customerSize = customerList.size();
	
  	cout << " << -- Add New Customer -- >> " << endl << endl;

  	customerSize++;
  	cin.ignore();
  	cout << "Customer ID   : " << customerSize << endl;
  	cDetails.cid = customerSize;
  	cout << "Name          : ";
  	getline(cin,cDetails.name);
  	cout << "Address       : ";
  	getline(cin,cDetails.address);

  	customerList.push_back(cDetails);
  	
  	cout << endl << "Customer has been successfully added!" << endl;
}

void functionList::displayCustomer() //Display Customer Details
{					
 	cout << " << -- Display Customer Details -- >> " << endl << endl;
 	
	cout << "Enter Customer ID   : ";
	cin >> cDetails.cid;

	for(cit = customerList.begin(); cit != customerList.end(); cit++)
	{
		if(cit->cid == cDetails.cid)
		{
			cout << "Name                : " << cit->name << endl
				 << "Address             : " << cit->address << endl;
		}
	}	
} 

void functionList::listRented() //Show Movies Rented by Customer
{
	cout << " << -- Show All Movies Rented by a Customer -- >> " << endl << endl;

	cout << "Enter Customer ID   : ";
	cin >> cDetails.cid;	
	
	if (!rentSearch(cDetails.cid))
	{
		cout << "Error. Customer not found!";
	}
}

////////////////////////////////////////////

bool functionList::rentSearch(int rentID) //found in showing movies rented by customer
{
	bool rsearch = false;
	
	for(rit = rentList.begin(); rit != rentList.end(); rit++)
    {

	    if (rit->rcid == rentID)
	    {
	    	rsearch = true;
			cout << "Name                : " << rit->rname << endl
				 << "Address             : " << rit->raddress << endl << endl;
			
			cout << "Movies Rented by Customer " << rit->rcid << " Sorted from First Rented Movie" << endl << endl;
			cout << "Movie ID\t"
			 	 << setw(40) << "Title\t";
			
			for(rit = rentList.begin(); rit != rentList.end(); rit++)
	    	{	
	        	cout << endl
	        	 	 << rit->rmid
	        	 	 << setw(50) << rit->rtitle << "\t"
	        	 	 << endl;
	    	}
	    	break;
		}
		
		else 
		{
			continue;
		}
	}
	return rsearch;
}
  
void functionList::movieRent() //Add Node
{
	rDetails.rcid = cDetails.cid;
	rDetails.rmid = mDetails.mid;
	rDetails.rname = cDetails.name;
	rDetails.raddress = cDetails.address;
	rDetails.rtitle = mDetails.title;
	
	rentList.push_back(rDetails);
}

/////////////////////////////////////////////

void functionList::loadMemory()
{
	string movieLine, customerLine, rentLine;
	int perLine;
	
	//load memory of movie
	//ifstream movieFile("F:\\darla\\Documents\\DSA MP_Finals\\customerMovie.txt"); //darla
	ifstream movieFile("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerMovie.txt"); //yannie path
	
	if (movieFile.is_open())
	{
		perLine = 0;
		
		while(getline(movieFile, movieLine))
		{
			switch(perLine)
			{
				case 0:
					mDetails.mid = atoi(movieLine.c_str());
					break;
				case 1: 
					mDetails.title = movieLine;
					break;
				case 2:
					mDetails.genre = movieLine;
					break;
				case 3:
					mDetails.production = movieLine;
					break;
				case 4:
					mDetails.copy = atoi(movieLine.c_str());
					break;
				case 5:
					mDetails.filename = movieLine;
					break;
				default:
					break;
			}
			
			if(perLine < 6)
			{
				perLine++;
			}
			
			else
			{
				perLine = 0;
				movieList.push_back(mDetails);
			}
		}
		
		movieFile.close();
	}
	
	else
	{
		cout << "Error. Movie File not found!";
	}
	
	//load memory of customer
	//ifstream customerFile("F:\\darla\\Documents\\DSA MP_Finals\\customerName.txt"); //darla
	
	ifstream customerFile("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerName.txt"); //yannie path
	
	if (customerFile.is_open())
	{
		perLine = 0;
		
		while(getline(customerFile, customerLine))
		{
			switch(perLine)
			{
				case 0:
					cDetails.cid = atoi(customerLine.c_str());
					break;
				case 1: 
					cDetails.name = customerLine;
					break;
				case 2:
					cDetails.address = customerLine;
					break;
				default:
					break;
			}
			
			if(perLine < 3)
			{
				perLine++;
			}
			
			else
			{
				perLine = 0;
				customerList.push_back(cDetails);
			}
		}
		
		customerFile.close();
	}
	
	else
	{
		cout << "Error. Customer File not found!";
	}
	
	//load memory of rent
	//ifstream rentFile("F:\\darla\\Documents\\DSA MP_Finals\\customerRent.txt"); //darla
	ifstream rentFile("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerRent.txt"); //yannie path
	
	if (rentFile.is_open())
	{
		perLine = 0;
		
		while(getline(rentFile, rentLine))
		{
			switch(perLine)
			{
				case 0:
					rDetails.rcid = atoi(rentLine.c_str());
					break;
				case 1: 
					rDetails.rmid = atoi(rentLine.c_str());
					break;
				default:
					break;
			}
			
			if(perLine < 2)
			{
				perLine++;
			}
			
			else
			{
				perLine = 0;
				rentList.push_back(rDetails);
			}
		}
		
		rentFile.close();
	}
	
	else
	{
		cout << "Error. Customer rent file not found!";
	}
}

void functionList::updateSave()
{
	//update movie text file
	ofstream movieFile;
	
	//movieFile.open("F:\\darla\\Documents\\DSA MP_Finals\\customerMovie.txt"); //darla
	movieFile.open("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerMovie.txt"); // yannie path
	
	for(mit = movieList.begin(); mit != movieList.end(); mit++)
	{
		movieFile << mit->mid << endl;
		movieFile << mit->title << endl;
		movieFile << mit->genre << endl;
		movieFile << mit->production << endl;
		movieFile << mit->copy << endl;
		movieFile << mit->filename << endl;
		movieFile << endl;
	}
	movieFile.close();
	
	//update customer name text file
	ofstream customerFile;
	
	//customerFile.open("F:\\darla\\Documents\\DSA MP_Finals\\customerName.txt"); //darla
	customerFile.open("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerName.txt"); //yannie path
	
	for(cit = customerList.begin(); cit != customerList.end(); cit++)
	{
		customerFile << cit->cid << endl;
		customerFile << cit->name << endl;
		customerFile << cit->address << endl;
		customerFile << endl;
	}
	customerFile.close();
	
	//update customer rent text file 
	ofstream rentFile;
	//rentFile.open("F:\\darla\\Documents\\DSA MP_Finals\\customerRent.txt"); //darla
	rentFile.open("C:\\Users\\ianne\\Desktop\\FINAL DSA\\DSA MP_Finals\\customerRent.txt"); //yannie path
	
	for(rit = rentList.begin(); rit != rentList.end(); rit++)
	{
		rentFile << rit->rcid << endl;
		rentFile << rit->rmid <<endl;
		rentFile << endl;

	}
	rentFile.close(); 
}
}

