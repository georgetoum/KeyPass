#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <conio.h>		
#include <stdexcept>	
#include <string>
#include <limits>
#include <cstdlib>  	//  functions  rand(), system("cls")
#include <windows.h>  	// feature hide the cursor


using namespace std;

void clearScreen() {
        system("cls");
}

void hideCursor() {						// Hide the console cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void showCursor() {						// Show the console cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int getChoice(int min, int max) {		 //user choice between min and max
   
    int c;
    while (true) {
        if (cin >> c && c >= min && c <= max) {	// Check if input is valid and within bounds
            cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear buffer
            return c;
        }
        cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void clearBuff() {					// Clear leftover input from buffer
	if (cin.peek() == '\n') 
		cin.get(); 					// If Enter is pressed, clear buffer
    else {
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cin.get();					
    }
}

class Password{
	private:
		string password;			// password
		string passwordType;		// name-type kodikou
	public:
		string getPasswordType(){	// Get password type
		return passwordType;		
		}
		string getPassword(){		// Get password
		return password;
		}
		void setPasswordType(string tempPasswordType){
			passwordType=tempPasswordType;
		}
		void setPassword(string tempPassword){
			password=tempPassword;
		}
	
};

int serialSearch(Password passwords[10000],string passwordType,int passwordCount){	// Search for password by type
	int i=0;
	while(i<passwordCount){
		if(passwords[i].getPasswordType()==passwordType){
		return i;
	}
		i++;
	}
	return -1;
	}
	
class FileManager{
	private:
		string fileName="passwords.txt";
		
	public:
		string openFile(){		// Read all contents from file
		string line;
		
		ifstream file ("passwords.txt");
		
		if(file.is_open()){
			stringstream buffer; //it's a string that u can add new things,but it doesn't read like string
			buffer << file.rdbuf();//read the whole text and returns it like buffer
			file.close();
			return buffer.str();		// Return all contents as string
		}else{
			cout<<"creating password file";		// If file doesn't exist, create one
			ofstream file;
			file.open("passwords.txt");
			file.close();
return "";		// Return empty string - xreiazotan sthn VSCode
		}
	}
		
		string getFileName(){
			return fileName;
		}
		// Save all passwords to file
		void saveToFile(Password passwords[10000],int passwordCount){
			
			ofstream file("passwords.txt");
			string line;
			
			if(file.is_open()){
				for(int i=0;i<passwordCount;i++){
					line=passwords[i].getPasswordType();
					line=line + ":";
					line=line + passwords[i].getPassword()+"\n";  // Format line
					file<<line;		// Write line to file
					
				}
				file.close();
			}else{
				cout<<"Unable to open file\n";
			}	
		}
};

class PasswordManager{		 // Class to manage passwords
	private:
		Password passwords[10000];
		FileManager fileManager;
		int passwordCount;		// Number of saved passwords
		
	public:
		void viewPasswordNames() {
 			clearScreen();
  			parsePasswords();
   			cout << "Saved password names:\n\n";
    		for (int i = 0; i < passwordCount; i++) {
        		cout << "- " << passwords[i].getPasswordType() << "\n";
    		}
		}
		
		PasswordManager ()
		{	passwordCount=-1;
		}
	
		void parsePasswords(){			//ftiaxtei ta passwords/ apo string parse tis grammes se type Password
			
			if(passwordCount!=-1)	{
			return;	//to count einai-1 otan den tous exei trabixei pote tous kodikous/gia na min ta xanatrabaei
			}
			string line;
			string passwordType;
			string password;
			
			string fileText=fileManager.openFile();		// Read file contents
			stringstream stream(fileText);				// Create string stream from text
			passwordCount=0;
			while(getline(stream,line))//with this getline we get the whole line
			{	if (line.empty()) continue; // agnoei kenh grammh
			int pos=line.find(":");
				passwordType=line.substr(0,pos);
				password=line.substr(pos+1);
				
				passwords[passwordCount].setPasswordType(passwordType);
				passwords[passwordCount].setPassword(password);
				passwordCount++;
			}				
		}
		
		void viewPasswords(){		// Show names of saved passwords
		
			clearScreen();	
			parsePasswords();
			cout<<"Number of saved passwords: "<<passwordCount<<"\n\n"; 
			for(int i=0 ;i<passwordCount;i++)
			{	//cout<<"password number "<<i+1<<endl;				// evala +1 gia na ksekinaei apo 1 anti 0
				cout<<i+1<<".   ";
				cout<<passwords[i].getPasswordType()<<":\t\t";
				cout<<passwords[i].getPassword()<<endl;
				cout<<"----------------------------------------------------------"<<endl;
			}
			cout<<"\n";		
		}
		
		void createNewPassword(){		 // Manually add a new password
			
			string passwordType;
			string password;
			parsePasswords(); 			//gia na fortothoun oi kodikoi
			clearScreen();
			cout<<"2.Add new Password\n\nPassword name: ";		
			cin>>passwordType;
			passwords[passwordCount].setPasswordType(passwordType);
			cout<<"Password: ";
			cin>>password;
			passwords[passwordCount].setPassword(password);
			passwordCount++;
						
			fileManager.saveToFile(passwords,passwordCount);	// Save to file
			cout<<"Password created sucessfully\n";
		}
				
		void generatePassword(){		// Generate a random password
			
			clearScreen();
			parsePasswords();
			string passwordType;
			string password="";
			int length;
			string charset;
			int charSize;
			int randomNum;
			string input; // 
			
			cout<<"3.Generate new random Password\n\nPassword name: ";			
			cin>>passwordType;
			passwords[passwordCount].setPasswordType(passwordType);
							
			do 														//thetei orio
			{	cout << "Enter the password length (8 - 20): ";
				length= getChoice(8, 20);
			}	while(length < 8 || length > 20);
			
			charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";
			
			for(int i=0;i<length;i++){
				charSize=charset.size();
				randomNum= rand()%charSize;
				password=password+charset[randomNum];
			}
			passwords[passwordCount].setPassword(password);
			passwordCount++;
		
			fileManager.saveToFile(passwords,passwordCount);	 // Save to file
			cout<<"Password Generated sucessfully, new password:\n"<<password<<"\n";		
		}	
		
		void editPassword(){
				
			parsePasswords();
			string passwordType;
			int pos;
			string password;
			string charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";
			string input; 						
			if(passwordCount==0){
				cout<<"there are no passwords\n";
				return; 
			}
			//viewPasswords();
			viewPasswordNames();
			cout<<"\nEnter the password name you want to edit:\n";  
			cin>>passwordType;
			
			pos= serialSearch(passwords,passwordType,passwordCount);
			
			if(pos==-1){
				cout<<"Invalid name of password\n";
			clearBuff();
			
			return;
			}
			
			cout<<"1.Custom input\n";
			cout<<"2.Generate\n";
			cout<<"3.Back\n";
			
			int choice =  getChoice(1, 3);
			cout << "\n";
		
			switch(choice){
				
				case 1:
					cout<<"Enter new password: ";
					cin>>password;
					passwords[pos].setPassword(password);
					fileManager.saveToFile(passwords,passwordCount);
					break;
				
				case 2:
					password="";
					int length;
					int charSize;
					int randomNum;
					do{ 														
						length= getChoice(8,20);
					}	while(length < 8 || length > 20);
					
    				
    				for (int i = 0; i < length; i++) 
      				{	charSize = charset.size();
        				randomNum = rand() % charSize;
        				password += charset[randomNum];
    				}
    	
    				passwords[pos].setPassword(password); 
    	
    				fileManager.saveToFile(passwords, passwordCount);
    				cout << "Password Generated successfully, new password:\n" << password << "\n";  //nik \n	
					break;

				case 3:
					return;
					break;		
			}
		}
		
		void deletePassword(){
			
			parsePasswords();
			string passwordType;
			int pos,i;
			if(passwordCount==0){
				cout<<"there are no passwords\n";
				return; 
			}
			//viewPasswords();
			viewPasswordNames();
					
			while (true) {
				cout << "\nEnter the password name you want to delete (or press ESC to cancel):\n";
				string tempInput = "";
				char ch;
				while ((ch = _getch()) != '\r') { // Enter key
					if (ch == 27) 
						return;				 // ESC key exits
					if (ch == '\b')			 // Backspace
					{ 
						if (!tempInput.empty()) {
							tempInput.pop_back();
							cout << "\b \b";
						}		
					}else {
						tempInput += ch;
						cout << ch;
					}
				}
				cout << "\n";

				passwordType = tempInput;
				pos = serialSearch(passwords, passwordType, passwordCount);
				if (pos != -1) break;
				cout << "Invalid password name. Try again or press ESC.\n";
				}	
			
			for(i=pos;i<passwordCount;i++){
				passwords[i]=passwords[i+1];
			}
			passwordCount--;
			//viewPasswords();
			fileManager.saveToFile(passwords,passwordCount);
			cout<<"\nPassword deleted succesfully\n";		
			//clearBuff();
			viewPasswordNames();			
		}
};		//end of class
	
class Menu{
	public:
		void show(){
			clearScreen();
			cout<<"PASSWORD MANAGER\n";
			cout<<"---------------------\n";
			cout<<"1.View Passwords\n";
			cout<<"2.Add new Password\n";
			cout<<"3.Generate new random Password\n";	
			cout<<"4.Edit Password\n";
			cout<<"5.Delete Password\n";
			cout<<"6.Exit\n";
			cout<<"---------------------\n";
			cout<<"Enter your choice: ";
		}
	};

int main() {
	hideCursor();
	srand(static_cast<unsigned int>(time(0)));
	int choice;
	PasswordManager passwordManager;
	Menu menu;
	
	do{
		menu.show();
		choice = getChoice(1, 6);
			switch(choice){
			case 1:	passwordManager.viewPasswords();		break;
			case 2:	passwordManager.createNewPassword();	break;
			case 3:	passwordManager.generatePassword();		break;
			case 4:	passwordManager.editPassword();			break;
			case 5:	passwordManager.deletePassword();		break;
			case 6: clearScreen(); cout << "Thank you for using password manager!\n"; 	break;				
			}
		if (choice != 6) {
            cout << "\nPress Enter to continue...\n";
            if (cin.peek() == '\n') cin.get(); // yparxei enter? clear
    		else {
        		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        		cin.get();
    			}
        	}
		}	while(choice != 6);
	return 0;
}
