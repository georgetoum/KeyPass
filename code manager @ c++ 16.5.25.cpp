#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>		//nik
#include <stdexcept>	//nik gia catch elegxo eisagwghs
#include <string>
#include <limits>
#include <cstdlib>  	// Xrisi system("cls")
#include <windows.h>  	// cursor


using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int getChoice(int min, int max) {
    int c;
    while (true) {
        if (cin >> c && c >= min && c <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return c;
        }
        cout << "Invalid choice. Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void clearBuff() {
	if (cin.peek() == '\n') 
		cin.get(); // yan exei eggrafei enter, clear buffer
    else {
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cin.get();
    }
}

class Password{
	private:
		string password;
		string passwordType;		// onomasia-typos kodikou
	public:
		string getPasswordType(){
		return passwordType;
		}
		string getPassword(){
		return password;
		}
		void setPasswordType(string tempPasswordType){
			passwordType=tempPasswordType;
		}
		void setPassword(string tempPassword){
			password=tempPassword;
		}
	
};

int serialSearch(Password passwords[10000],string passwordType,int passwordCount){
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
		string openFile(){
		string line;
		
		ifstream file ("passwords.txt");
		
		if(file.is_open()){
				
			stringstream buffer; //it's a string that u can add new things,but it doesn't read like string
			buffer << file.rdbuf();//read the whole text and returns it like buffer
			file.close();
			return buffer.str();
		
		}else{
			cout<<"creating password file";
			ofstream file;
			file.open("passwords.txt");
			file.close();
		}
	}
		
		string getFileName(){
			return fileName;
		}
		
		void saveToFile(Password passwords[10000],int passwordCount){
			
			ofstream file("passwords.txt");
			string line;
			
			if(file.is_open()){
				for(int i=0;i<passwordCount;i++){
					line=passwords[i].getPasswordType();
					line=line + ":";
					line=line + passwords[i].getPassword()+"\n";
					file<<line;
					
				}
				file.close();
			}else{
				cout<<"Unable to open file\n";
			}	
		}
};

class PasswordManager{
	private:
		Password passwords[10000];
		FileManager fileManager;
		int passwordCount;
		
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
			return;	//to count einai-1 otan den tous exei trabijei pote tous kodikous/gia na min ta janatrabaei
			}
			string line;
			string passwordType;
			string password;
			
			string fileText=fileManager.openFile();
			stringstream stream(fileText);
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
		
		void viewPasswords(){
		
			clearScreen();	
			parsePasswords();
			cout<<"Number of saved passwords: "<<passwordCount<<"\n\n"; //nik
			for(int i=0 ;i<passwordCount;i++)
			{	//cout<<"password number "<<i+1<<endl;				// evala +1 gia na ksekinaei apo 1 anti 0. dhmiourgei thema?
				cout<<i+1<<".   ";
				cout<<passwords[i].getPasswordType()<<":\t\t";
				cout<<passwords[i].getPassword()<<endl;
				cout<<"----------------------------------------------------------"<<endl;
			}
			cout<<"\n";		//nik
		}
		
		void createNewPassword(){
			
			string passwordType;
			string password;
			parsePasswords(); //gia na fortothoun oi kodikoi
			clearScreen();
			cout<<"2.Add new Password\n\nPassword name: ";		//nik name anti gia type
			cin>>passwordType;
			passwords[passwordCount].setPasswordType(passwordType);
			cout<<"Password: ";
			cin>>password;
			passwords[passwordCount].setPassword(password);
			passwordCount++;
						
			fileManager.saveToFile(passwords,passwordCount);
			cout<<"Password created sucessfully\n";
		}
				
		void generatePassword(){
			
			clearScreen();
			parsePasswords();
			string passwordType;
			string password="";
			int length;
			string charset;
			int charSize;
			int randomNum;
			string input; // nik
			
			cout<<"3.Generate new random Password\n\nPassword name: ";			
			cin>>passwordType;
			passwords[passwordCount].setPasswordType(passwordType);
							
			do 														//nik -> orio
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
		
			fileManager.saveToFile(passwords,passwordCount);
			cout<<"Password Generated sucessfully, new password:\n"<<password<<"\n";		//nik \n
		}	
		
		void editPassword(){
				
			parsePasswords();
			string passwordType;
			int pos/*,choice*/;
			string password;
			string charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";
			string input; 							// nik
			if(passwordCount==0){
				cout<<"there are no passwords\n";
				return; 
			}
			//viewPasswords();
			viewPasswordNames();
			cout<<"\nEnter the password name you want to edit:\n";  //  nik word name
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
					do{ 														//nik -> orio
						length= getChoice(8,20);
					}	while(length < 8 || length > 20);
					
			// Now the password generation code will be executed
  			// string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?";
    				
    				for (int i = 0; i < length; i++) 
      				{	charSize = charset.size();
        				randomNum = rand() % charSize;
        				password += charset[randomNum];
    				}
    		//passwords[passwordCount].setPassword(password);
    				passwords[pos].setPassword(password); // ������������ �� password ��� ���� pos
    		//passwordCount++;

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
			cout<<"3.Generate new random Password\n";	// nik random
			cout<<"4.Edit Password\n";
			cout<<"5.Delete Password\n";
			cout<<"6.Exit\n";
			cout<<"---------------------\n";
			cout<<"Enter your choice: ";
		}
	};

/*class Authentication{
	function encrypt password with ceasar and the key will be the password
	function for decrypt
	function for login(in the begining tha sigrine ton kodiko me hash, and idf the password was correct tha decrypt all the password -using the key as the password-)
};*/


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
