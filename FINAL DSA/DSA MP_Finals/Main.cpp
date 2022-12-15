#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
#include <unistd.h>
#include "Data.h"
using namespace std;
using namespace ns;

/*
 * PROGRAMMER LEADER: MARIEL TIBIO
 * PROGRAMMER 1: DARLA DAVID
 * PROGRAMMER 2: MARIANNE LOUISE BUAMA
 */

int mainMenu();
int customerMenu();

////////////////////////////////////////////

int main(int argc, char** argv)
{
    //main menu variables
    functionList execute;
    execute.loadMemory();		

	int ch;
	
    //customer menu variables
    int ch2;
    char ch3; 

    do
    {
		
        ch = mainMenu();

        if (ch == 1) //appending
        {
            cout << " << -- Add a New Movie -- >> " << endl << endl;
            
            int movieSize = movieList.size();
            movieSize += 101;
			  	
		  	cout << "Movie ID        : " << movieSize;
            mDetails.mid = movieSize;
            cout << endl << "Movie Title     : ";
            cin.ignore();
            getline(cin, mDetails.title);
            cout << "Genre           : ";
            getline(cin, mDetails.genre);
            cout << "Production      : ";
            getline(cin, mDetails.production);
            cout << "Copies          : ";
            cin >> mDetails.copy;
            cin.ignore();
            cout << "Poster Filename : ";
            cin >> mDetails.filename;
            movieSize++;
			cout << endl << "Movie has been successfully added!" << endl;
		
            execute.addNode();
            sleep (5); 
            system("cls"); 	
        } 

        else if (ch == 2) //deleting
        {	
        	
            cout << " << -- Rent a Movie -- >> " << endl << endl;
            
            cout << "Enter Customer ID        : ";
            cin >> cDetails.cid;
			cout << "Enter Movie ID           : ";
			cin >> mDetails.mid;
            
            execute.deleteNode();
            sleep (5);
            system("cls"); 
            
        }

        else if (ch == 3) //appending 
        {
            cout << " << -- Return a Movie -- >> " << endl << endl;
            
            cout << "Enter Customer ID        : ";
            cin >> cDetails.cid;
			cout << "Enter Movie ID           : ";
			cin >> mDetails.mid;
            
            execute.returnNode();
			sleep (5); 
            system("cls");
        }

        else if (ch == 4) //traversing
        {
            cout << " << -- Display Movie Details -- >> " << endl << endl;
            
			cout << "Enter Movie ID     : ";
			cin >> mDetails.mid;
            
            execute.displayList();
            sleep (5);
            system("cls");
        }

        else if (ch == 5) //traversing
        {
            cout << " << -- Show Movie List -- >> " << endl << endl;
            
            execute.showList();
            sleep (8);
            system("cls");

        }

        else if (ch == 6) //check node
        {
            cout << " << -- Check Movie Availability -- >> " << endl << endl;
            
			cout << "Enter Movie ID     : ";
			cin >> mDetails.mid;
            
            execute.checkNode();
            sleep (5);
            system("cls");
        }
		
        else if (ch == 7) //customer maintenance
        {	
			
			system("cls");
			
			do{
				ch2 = customerMenu();
				
				if(ch2 == 1)
				{					
					execute.newCustomer(); //appending
					sleep (5);
				}
				
				else if(ch2 == 2)
				{
					execute.displayCustomer(); //traversing
					sleep (5);
				}
				
				else if(ch2 == 3)
				{
					execute.listRented(); //traversing
					sleep (5);
				}
					
				else
				{
					cout << "Error. Incorrect Input!";
					cout << "\nDo you want to try again [Y/N]: ";
					cin >> ch3;	
				}
			} while(ch3 == 'Y' || ch3 == 'y'); 
		} 
		
    	else if (ch == 8) //saving
		{
			execute.updateSave();
			
			cout << "Thank you for using Git Git Aww Movie Rental Service!";
			return 0;
		}
		
		else
		{
			cout << "Error. Invalid input!";
		}
		
    } while (ch >= 1 && ch <= 8);
        
        return 0;
}

////////////////////////////////////////////

int mainMenu()
{
	int tempch;
    
    system("cls");
    system("Color E"); //yellow
    cout << "===================================" << endl
		 << " << -- GIT GIT AWW MAIN MENU -- >> " << endl
		 << "===================================" << endl
		 << "[1] Add Movie" << endl
		 << "[2] Rent Movie " << endl  
		 << "[3] Return Movie" << endl
		 << "[4] Display Movie Details  " << endl 
		 << "[5] Show All Movie" << endl
		 << "[6] Check Movie Availability" << endl
		 << "[7] Customer Maintenance" << endl
		 << "[8] Exit Program" << endl;  
    cout << "Enter Choice: ";
    cin >> tempch;
    cout << endl;
    
    return(tempch);
}

int customerMenu()
{
	int tempch;
	
    system("cls");
    system("Color A"); //green
    cout << "=======================================" << endl
		 << " << -- GIT_GIT_AWW CUSTOMER MENU -- >> " << endl
		 << "=======================================" << endl
		 << "[1] Add New Customer" << endl 
		 << "[2] Display Customer Details" << endl
		 << "[3] Show All Movies Rented by Customer" << endl;		
    cout << "Enter Choice: ";
    cin >> tempch;	
    cout << endl;
    
    return(tempch);
}
