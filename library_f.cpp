//C13- Library Management System(c/c++)
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// ...

 
using namespace std;

 
 class library{

	public:
	string ID; //Managment ID
	string sID; //student ID
	string BId; //book ID
	string sname ,bname,aname; //book name, author name, Student name
	int Idate; //Issue date
	int Rdate; //return date
	int dd,mm,yy; //date
	int m,n; // entry exit input
	bool available=true;


	void libm(){ //Welcome Lib (function declaration)
		cout<<"\t\t\t\t\tLIBRARY __ MANAGMEN ";
		cout<<"\n\n";

		cout<<"\t\tEnter ID : "; // ID from user
		cin>>ID;
		json logg;
		nlohmann::json j;
		j["ID"]=ID;
		ifstream myfile("lib_data.json"); // Create file to save data
  		if (myfile.is_open())
		{	try{
				myfile >> logg;
				cout<<logg;
			}
			catch(const nlohmann::json::parse_error& e){
				// Handle the case where the file is empty or has a parsing error
				logg=nlohmann::json::array();
			}
		// 
			myfile.close();
		}
		else
			logg=nlohmann::json::array();
    	// Add the new book data to the existing data
    		logg.push_back(j);


			// Write the updated data back to the file
    	ofstream outFile("lib_data.json");
    	if (outFile.is_open()) {
			cout<<logg;
        outFile << logg.dump(4);  // 4 is the number of spaces for indentation
        outFile.close();
    	}
		else
		{	// Handle the case where the file couldn't be opened for writing
		cout<<"for can not open the file";
		}
		
		p2();
	}

	void display(){   // display saved file 5.
		string line;
		nlohmann:: json j;

		cout<<">>>>>>     Display     <<<<<< \n";
		ifstream f("students.json");          //read data and display
		 j = json::parse(f);
		cout<< j.dump(4)<<endl;
		f.close();

		
	}

	int lib(){  //display ADMIN LOG 4.
		

		cout<<">>>>>>     ADMIN LOG     <<<<<< \n";
		ifstream f("lib_data.json");
		json data = json::parse(f);
		
		cout<<data.dump(1)<<endl;
		f.close();

		cout<<"For Menu press 1  :";
		cin>>n;
		if (n==1)
		{
			p2();
		}
		return 0;
	}

	
	void p2(){      //main menu(function) P2 is page 2
		cout<<"\t\t1. update new stock  ";
		cout<<"\t\t2. New issue  ";
		cout<<"\t\t3. Book Return ";
		cout<<"\t\t4. Admin login ";
		cout<<"\t\t5. Display ";
        cout<<"\t\t( Press Any other Key to Exit )";
		cout<<"\n\t\t Choose Option : ";

		cin>>n;
		switch (n) // switch case 
		{
		case 1:
			pn();
			break;
		case 2:
			pb();
			break;
		case 3:
			pr();
			break;
		case 4:
			lib();
			break;
		case 5:
			display();	
		default:
			ex();
			break;
		}
		
	}
	int ex(){      //exit function declared
		return 0;
	}

	int Date(){    // date function for input date
		cin>>dd;
		cin.get();
		cin>>mm;
		cin.get();
		cin>>yy;
		cin.get();
		return 0;
	}

	void pn(){     //Update new book Stock
		cout<<"Enter Book Name  :";
		getline(cin>>ws,bname);
		cout<<"Enter Author name :"; 
		getline(cin,aname);
		cout<<"Date (DD/MM/YYYY) :";
		Date();
		cout<<"Enter Book ID  :"; 
		getline(cin,BId);

		book(bname,BId); //update in fie


		cout<<"For Menu press 1  :";
		cin>>n;
		if (n==1)
		{
			p2();
		}
		
	}

	void pb(){ //update Book issue 
        cout<<"Enter Student Name   :";
        getline(cin>>ws,sname);
		cout<<"Enter Student ID  :";
		getline(cin,sID);
		cout<<"Enter Book Name  :";
		getline(cin,bname);
		cout<<"Enter Book ID  :";
		getline(cin,BId);
		cout<<"Issue Date (DD/MM/YYYY) :";
		Date();

		book_issue(bname,BId,sID); //update in file

		cout<<"For Menu press 1  :";
		cin>>n;
		if (n==1)
		{
			p2();
		}
		
	}

	void pr(){     //book return
		cout<<"Enter Student ID  :";
		cin>> sID;
        cout<<"Enter Book Name   :";
        getline(cin>>ws,bname);
		cout<<"Enter Book ID  :";
		getline(cin,BId);
		cout<<"Book Return Date (DD/MM/YYYY) :";
		Date();

		book_Return(sID,bname,BId); //update in file

		cout<<"For Menu press 1  :";
		cin>>n;
		if (n==1)
		{
			p2();
		}
		
	}

	
	void book(string bname, string BId) {    // stores update new stock in students.json 1
    // Create a JSON object for the book data
    nlohmann::json bookData;
    bookData["BookName"] = bname;
    bookData["BookID"] = BId;
	bookData["Available"] = available;

    // Read existing data from the file
    nlohmann::json existingData;
    ifstream file("students.json");
    if (file.is_open()) {
		try
		{
        file >> existingData;
			
		}
		catch(const nlohmann::json::parse_error& e){
			// Handle the case where the file is empty or has a parsing error
			existingData=nlohmann::json::array();
		}
		
        file.close();
    }
	else
	// Handle the case where the file couldn't be opened
			existingData=nlohmann::json::array();

    // Add the new book data to the existing data
    existingData.push_back(bookData);

    // Write the updated data back to the file
    ofstream outFile("students.json");
    if (outFile.is_open()) {
        outFile << existingData.dump(4);  // 4 is the number of spaces for indentation
        outFile.close();
    }
	else
	{	// Handle the case where the file couldn't be opened for writing
		cout<<"for can not open the file";
	}
    }
	
	
	void book_issue(const string& bname,const string& BId,const string& sID){  // Issue book 2
		// Read existing data from file.

    nlohmann::json existingData;
	ifstream file("students.json");  //search in existingData
	if (file.is_open()){
		try
		{
			file>>existingData;
		}
		catch(const nlohmann::json::parse_error& e){
			// Handle the case where the file is empty or has a parsing error
			existingData=nlohmann::json::array();
		}
		 file.close();
		
		bool bookFound = false;
		for (auto& entry:existingData){
			if(entry["BookName"] == bname && entry["BookID"] == BId && entry["Available"] == true ){
				bookFound = true;
				entry["Available"] = false;
				entry["StudentID"] = sID;
				break;
			}
		}
		
        if (bookFound) {
            // The book is available, proceed with issuing it
            // Add your logic for issuing the book here
			ofstream outFile("students.json");
			if(outFile.is_open()){
				outFile<<existingData.dump(4);
				outFile.close();
            	cout << "Book issued successfully!\n";
			}
			else{
				cout<<"Error opening file for writing.\n";
			}

        } else {
            cout << "Book not found or not available for issue.\n";
        }
	}else{
		// Handle the case where the file couldn't be opened
        cout << "Error opening file for reading.\n";
	}
	}

	
	void book_Return(string& sID,string& bname,string& BId){   //return book to students.json 3
		// Read existing data from file.

		nlohmann::json existingData;
		ifstream file("students.json"); //Read existing data
		if(file.is_open()){
			try
			{
			file>>existingData;	
			}
			catch(const nlohmann::json::parse_error& e){
			// Handle the case where the file is empty or has a parsing error
			existingData=nlohmann::json::array();
			}
			file.clear();

		bool bookFound = false;
		for (auto& entry:existingData){
			if (entry["Available"]==false && entry["BookID"] == BId && entry["StudentID"] == sID ){
				bookFound = true;
				entry["StudentID"]= NULL;
				entry["Available"]= true;
				break;
			}	
		}

		if (bookFound)
		{
			ofstream outFile("students.json");
			if(outFile.is_open()){
			outFile<<existingData.dump(4);
			outFile.close();
			cout<<" Book Returned suuccessfully!\n";
			}else{
				cout<<"Error opening file for writing.\n";
			}
		}else {
            cout << "Book not found or not available for return.\n";
        }

		}else{
		// Handle the case where the file couldn't be opened
        cout << "Error opening file for reading.\n";
	}
		
	}

 };

 int main(){
	library library1;
	library1.libm();
	
 }