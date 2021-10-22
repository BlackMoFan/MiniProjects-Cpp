//                                           *************************************************************************   									//   
//													 	  Final Project in Computer Programming 1 (cc202) 													//
//											 *************************************************************************										//
//                                             Submitted to:																								//
//													Sir Frank Elijorde																						//
//																				Submitted by:																//
//																					Rod Lester Angusto Moreno BSCS 1-B										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <conio.h> //for getch
#include <Windows.h> //for time delay
#include <string>
#include <sstream>

using namespace std;

string filename;

ifstream in_account; //main storage, input and output fstream
ofstream out_account;
ifstream database_in; //for the feature 2 of the program:  Show List of Registered Students
ofstream database_out;

//FUNCTION DECLARATIONS
void SystemMain();//The Main function
void Main_display();//To display the Welcome note
void ExitConfirmation();//Confirmation to exit from the Main display
void RepeatOption();//The main display of Options to choose from; this will pop up every time a session ends with each and every feature
char wait(); //This provides a 30-second timeout feature when choosing from the RepeatOption() ; when 30 seconds have passed, the display on the screen will go back to SystemMain()
void create_append_file(ofstream& out_account); //This is for creating a file when Option 1 was chosen.  i.e. To Register New Student Account
void place_password(); //This prompts you for a password for your account.  This is needed when you choose to modify or delete your account
void Register(); //Register function
void database_file(char FName[100], char MName[100], char LName[100], char Course[100], string Section); //This outputs student data into a database file that will be used to display for Option 2
void view_database(ifstream& instream); //This displays the data inside the database file onto the screen
void search_student(ifstream& in_s); //This is to display the student data
void grade_calculator(int totalMark); //This calculates the total grade and mark of the student
string operator+(string const &a, int b);
void Modify_account(); //This runs when the user has chosen Option 4:  Modify Student Account; Account password is needed
void Modify(); //This is the same as of the Register() function but this doesn't append the student data into the database file
void Delete_account(); //This actually moves the file deleted into a folder 'deletedaccounts' inside the database directory; Account password is needed


//BOOL TO CHECK IF THE DATABASE FILE IS EMPTY, FOR INITIAL FILE CREATION
bool is_empty(ifstream& File)
{
    return File.peek() == ifstream::traits_type::eof();
}

//STRUCT FOR STUDENT PROFILE INFO
struct stud_p{ 
	char FName[100]; //First name
	char LName[100]; //Last name
	char MName[100];//Middle name
	int Year; // Year level
	string Section; //Section
	char Course[100]; //Course name
	int ID; //ID assigned to student
	string password;
	string fileN;
	int No_subs; //No. of subjects for the semester
	char Sub_code[100]; //Subject code
	char Sub_des[100]; //Subject name/description
	int Units; //Credited units
	int Q1; //Grade for quiz 1
	int Lab1_2; //Grade for lab 1 and 2
	int Q2; //Grade for quiz 2
	int Lab3; //Grade for lab 3
	int Q3; //Grade for quiz 3
	int Lab4; //Grade for lab 4
	int Q4; //Grade for quiz 4
	int Lab5; //Grade for lab 5
}; stud_p stud;


//MAIN
void SystemMain(){
	while(1){
		system("color 0B");
		system("title STUDENT REGISTRATION AND MARK LIST SYSTEM");
		system("mode con cols=200 lines=50");
		Main_display();
		ExitConfirmation();
		system("cls");
		system("if not exist \"database\" mkdir database");
		RepeatOption();
	}
	return;
}

//To display the main window after running the program.
void Main_display(){
	cout<<"     \t\t\t\t\t\t\t********************************************************************************************\n";
  	cout<<"     \t\t\t\t\t\t\t\t     *      W     E     L     C     O     M     E      T     O      *\n";
  	cout<<"     \t\t\t\t\t\t\t********************************************************************************************\n";
	cout<<"\t\t\t\t\t\t\t_________  _______       ___        ______    _______        ____    ____           ___      ___"<<endl;
	cout<<"\t\t\t\t\t\t       /   ______| |   _   \\    /   \\      /  ____|  |  ____ |       \\   \\  /   /          |   |    |   |"<<endl;
	cout<<"\t\t\t\t\t\t      |   (        |  |_ )  |  /  ^  \\    |  '       |  |__           \\    V   /           |   |    |   |"<<endl;
	cout<<"\t\t\t\t\t\t       \\    \\      |   ____/  /  /_\\  \\   |  |       |   __|           >      <            |   |    |   |"<<endl;
	cout<<"\t\t\t\t\t\t   -----)    |     |   |     /  ____   \\  |  '____   |  |___          /    .   \\           \\   \\____/   /"<<endl;
	cout<<"\t\t\t\t\t\t  |_________/      |___|    /__/     \\__\\  \\______|  |_______|       /___/  \\___\\           \\__________/"<<endl;
	cout<<"\n"<<endl;
	system("powershell write-host -fore DarkMagenta    ********************************************************************************************************************************************************************************************************\n");
  	cout<<"     \t\t\t\t\t\t\t\t\t    *  STUDENT REGISTRATION AND MARK LIST SYSTEM *\n\n";
  	system("powershell write-host -fore DarkMagenta    ********************************************************************************************************************************************************************************************************");
  	cout<<"\n\n";
  	cout.width(110);
	cout<<"PRESS ENTER TO ACCESS\n"<<endl;
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
	cout<<"FINAL PROJECT IN COMPUTER PROGRAMMING 1 (cc202)"<<endl;
	cout<<"Submitted to:"<<endl;
	cout<<"Sir Frank Elijorde"<<endl;
	cout<<"Submitted by:"<<endl;
	cout<<"Rod Lester A. Moreno BSCS 1-B"<<endl;
	return;
}

//  TO CONFIRM IF THE USER PRESSED THE CORRECT BUTTON AFTER THE MAIN DISPLAY
void ExitConfirmation(){
	char enter=getch();
	if(!isspace(enter)){//if the user did not press enter
		char conf;
		cout.width(140);
		cout<<"Enter 'y' if you misclicked to start the system again while 'n' if you did not."<<endl;
		cout<<"Choice:  ";
		cin>>conf;
		if(conf!='y'){
			cout<<"\n\n\n";
			cout.width(80);
			cout<<"Thank you!"<<endl;
			cout.width(80);
			cout<<"RESTARTING THE SYSTEM";
			for(int i=0;i<=5;i++){
				cout<<".";
				Sleep(500);
			}
			SystemMain();
		}
		else{
			system("cls");
			SystemMain();
		}
	}
	return;
}

//THIS PROMPTS EVERY AFTER SESSION TO PROVIDE OPTIONS FOR THE USER ON WHAT TO DO NEXT
void RepeatOption(){
	char option;
	cout<<endl;
	cout<<"  ****************************************************************************************************************************************************************************************************  \n";
	cout.width(110);
	cout<<"I N S T R U C T I O N S";
	cout<<"\n\nPress 1 To Register New Student\n";
	cout<<"Press 2 To Show the List of Registered Students\n";
	cout<<"Press 3 To Search for Your Student Account\n";
	cout<<"Press 4 To Edit a Student Record\n";
	cout<<"Press 5 To Delete a Student Record\n";
	cout<<"Press 0 To Exit and Restart the System\n";
	cout<<"Select what you want to do next: ";
    option=wait();
    fflush(stdin);
		switch(option){
			case '1':
				{
					//Register a student
					system("color F0");
					system("cls");
					stud.ID++;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					create_append_file(out_account);
					cout.width(80);
					cout<<"\n\nRegistration successful!"<<endl;
					system("pause");
					cout<<"\n\n"<<endl;
					RepeatOption();
				}
				break;
			case '2':
				{
					//Show List of Registered Students
					system("cls");
					system("color 0A");
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					database_in.open("database\\databasefile.txt");
					if(database_in.fail()){
						cout<<"File doesn't exist."<<endl;
						system("pause");
						SystemMain();
					}
					view_database(database_in);
					database_in.close();
					system("pause");
					cout<<"\n\n"<<endl;
					RepeatOption();
				}
				break;
			case '3':
				{
					//Search for a Student account
					system("color B0");
					system("cls");
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"Please enter your Username:\nFORMAT:  First Name Middle Name Surname+ID , e.g. Rod Lester Angusto Moreno1\n";
					cout<<":";
					string extension=".txt";
					string keyword;
					getline(cin,keyword,'\n');
					string cd = "database\\";
					stringstream strstr;
					strstr<<cd<<keyword<<extension;
					in_account.open(strstr.str().c_str());
					if(in_account.fail()){
						cout.width(75);
						cout<<"Sorry, you have no existing account in our system yet."<<endl;
						system("pause");
						RepeatOption();
					}
					search_student(in_account);
					in_account.close();
					system("pause");
					cout<<"\n\n"<<endl;
					RepeatOption();
				}
				break;
			case '4':
				{
					//Account modification
					system("color F0");
					system("cls");
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					Modify_account();
					cout<<"Account modification complete"<<endl;
					system("pause");
					RepeatOption();
				}
				break;
			case '5':
				{
					//Delete Student Record
					system("color 4E");
					system("cls");
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					Delete_account();
					system("pause");
					cout<<"\n\n"<<endl;
					RepeatOption();
				}
				break;
			case '0':
				{
					//RESTART THE PROGRAM FROM THE MAIN DISPLAY
					system("cls");
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    //  \t_________  \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  //           /   ______|   \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t//            |   (\t       \\\\"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\\\\           \\    \\\t       //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\\\     -----)    |  \t     //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t    \\\\  |_________/ \t   //"<<endl;
					cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t      ====================="<<endl;
					cout<<"\n\n\n";
					cout.width(100);
					cout<<"THANK YOU!\n"<<endl;
					cout.width(110);
					cout<<"RESTARTING THE SYSTEM";
					for(int i=0;i<=5;i++){
						cout<<".";
						Sleep(500);
					}
					SystemMain();
				}
				break;
			default:
				{
					//DEFAULT PART
					cout<<"\nInvalid Entry. Please try again.\n";
					RepeatOption();
				}
		}
	return;	
}

//FOR SCREEN TIMEOUT IF THE USER HASN'T PROVIDED AN INPUT IN REPEATOPTION(); FOR 30 SECONDS
char wait()
{
	int option;
    DWORD start_time, check_time;
    start_time=GetTickCount();
    check_time=start_time+30000;
    while(!kbhit())
    {
        while((check_time>GetTickCount()))
        {
            if (kbhit())
            {
                option=getch();
                return option;
            }
        }
        cout<<"\n\n\n";
        cout.width(110);
        cout<<"Time-out: 30 seconds"<<endl;
		cout.width(110);
		cout<<"THANK YOU!\n"<<endl;
		cout.width(110);
		cout<<"RESTARTING THE SYSTEM";
		for(int i=0;i<=5;i++){
			cout<<".";
			Sleep(500);
		}
		SystemMain();
    }
}


//OPENING THE FILE TO REGISTER
void create_append_file(ofstream& out_account){
	string un;
	cout<<"Your ID is "<<stud.ID<<endl;
	cout<<"Write your Full name (First Name Middle Name Surname)\n";
//	cin.ignore();
	getline(cin,un);
	system("if not exist \"database\" mkdir database"); //IF THE DATABASE DIRECTORY DOESN'T EXIST IN THE CURRENT DIRECTORY, THIS LINE CREATES IT
	database_out.open("database\\databasefile.txt",ios::app);
	if(database_out.fail()){
		cout<<"File creation failed"<<endl;
		database_out.close();
		system("pause");
		SystemMain();
	}
	database_out.close();
	string cd = "database\\";
	string fileType=".txt";
	stringstream ss;
	ss<<cd<<un<<stud.ID<<fileType;
	stud.fileN=un+stud.ID;
	out_account.open(ss.str().c_str()); //CREATES YOUR STUDENT DATA FILE IN THE DATABASE DIRECTORY
	if(out_account.fail()){
		cout<<"Error: File creation failed!"<<endl;
		exit(1);
	}
	place_password();
	cout<<"\n"<<endl;
	cout<<"Remember these credentials.  You will have to sign in if you want to modify or delete your record."<<endl; //THIS PROVIDES THE STUDENT HIS/HER CREDENTIALS WHEN INTERACTING WITH THE PROGRAM
	cout<<"Username:  "<<un<<stud.ID<<endl;
	cout<<"Password:  "<<stud.password<<"\n"<<endl;
	Register();
	out_account.close();
	return;
}

//PROMPTS THE USER FOR HIS/HER DESIRED PASSWORD
void place_password(){
	cout<<"\nOnly you or the admin can modify and delete your data.\n";
	cout<<"To do this, please enter your desired password.\nPassword: ";
	cin>>stud.password;
	cin.ignore();
}

//FOR OPTION 1: TO REGISTER NEW ACCOUNT
void Register(){
	out_account<<stud.fileN<<endl; //OUTPUTS THE FILENAME/USERNAME INTO THE FIRST LINE OF THE FILE FOR CONVENIENCE FOR THE OTHER FUNCTIONS
	out_account<<stud.password<<endl; //OUTPUTS THE PASSWORD INTO THE SECOND LINE OF THE FILE FOR CONVENIENCE FOR THE OTHER FUNCTIONS
	out_account<<stud.ID<<endl;
	cout<<"\n  ****************************************************************************************************************************************************************************************************\n";
	cout<<"  ******************************************************************************************** R E G I S T R A T I O N *******************************************************************************\n";
	cout<<"  ****************************************************************************************************************************************************************************************************\n\n";
	cout<<"        \n\n\tEnter First Name of student: ";
//	cin.ignore();
	cin.get(stud.FName,100);
	out_account<<stud.FName<<endl;
	cout<<"        Enter Middle Name of student: ";
	cin.ignore();
	cin.get(stud.MName,100);
	out_account<<stud.MName<<endl;
	cout<<"        Enter Last Name of student: ";
	cin.ignore();
	cin.get(stud.LName,100);
	out_account<<stud.LName<<endl;
	cout<<"        Enter Registration year: ";
	cin.ignore();
	cin>>stud.Year;
	out_account<<stud.Year<<endl;
	cout<<"        Enter Section: ";
	cin>>stud.Section;
	out_account<<stud.Section<<endl;
	cout<<"        Enter Course of student: ";
	cin.ignore();
	cin.get(stud.Course,100);
	out_account<<stud.Course<<endl;
	cout<<"        Enter number of subjects that student learns in this semester and register them one by one\n";
	cout<<"        Number of subjects: ";
	cin>> stud.No_subs;
	out_account<<stud.No_subs<<endl;
/* for loop used to register multiple courses for one student
   based on the student's number of courses entered.
 */
	for(int a=1; a<=stud.No_subs; a++) {
		cout<<"           Enter Subject Name: ";
		cin.ignore();
		cin.get(stud.Sub_des,100);
		out_account<<stud.Sub_des<<endl;
		cout<<"           Enter Subject code: ";
		cin.ignore();
		cin.get(stud.Sub_code,100);
		out_account<<stud.Sub_code<<endl;
		cout<<"           Enter grade for quiz one: ";
		cin>>stud.Q1;
		out_account<<stud.Q1<<endl;
		cout<<"           Enter grade for Labs 1 and 2: ";
		cin>>stud.Lab1_2;
		out_account<<stud.Lab1_2<<endl;
		cout<<"           Enter grade for quiz two: ";
		cin>>stud.Q2;
		out_account<<stud.Q2<<endl;
		cout<<"           Enter grade for Lab 3: ";
		cin>>stud.Lab3;
		out_account<<stud.Lab3<<endl;
		cout<<"           Enter grade for quiz 3: ";
		cin>>stud.Q3;
		out_account<<stud.Q3<<endl;
		cout<<"           Enter lab 4 grade: ";
		cin>>stud.Lab4;
		out_account<<stud.Lab4<<endl;
		cout<<"           Enter grade for quiz 4: ";
		cin>>stud.Q4;
		out_account<<stud.Q4<<endl;
		cout<<"           Enter lab 5 grade: ";
		cin>>stud.Lab5;
		out_account<<stud.Lab5<<endl;
	}
	database_file(stud.FName, stud.MName, stud.LName, stud.Course, stud.Section);
	return;
}

//FOR MODIFICATION OF ACCOUNT
void Modify(){
	out_account<<stud.fileN<<endl;
	out_account<<stud.password<<endl;
	out_account<<stud.ID<<endl;
	cout<<"\n  ****************************************************************************************************************************************************************************************************\n";
	cout<<"  *************************************************************************** M O D I F I C A T I O N  O F  A C C O U N T ****************************************************************************\n";
	cout<<"  ****************************************************************************************************************************************************************************************************\n\n";
	cout<<"        \n\n\tEnter First Name of student: ";
//	cin.ignore();
	cin.get(stud.FName,100);
	out_account<<stud.FName<<endl;
	cout<<"        Enter Middle Name of student: ";
	cin.ignore();
	cin.get(stud.MName,100);
	out_account<<stud.MName<<endl;
	cout<<"        Enter Last Name of student: ";
	cin.ignore();
	cin.get(stud.LName,100);
	out_account<<stud.LName<<endl;
	cout<<"        Enter Registration year: ";
	cin.ignore();
	cin>>stud.Year;
	out_account<<stud.Year<<endl;
	cout<<"        Enter Section: ";
	cin>>stud.Section;
	out_account<<stud.Section<<endl;
	cout<<"        Enter Course of student: ";
	cin.ignore();
	cin.get(stud.Course,100);
	out_account<<stud.Course<<endl;
	cout<<"        Enter number of subjects that student learns in this semester and register them one by one\n";
	cout<<"        Number of subjects: ";
	cin>> stud.No_subs;
	out_account<<stud.No_subs<<endl;
/* for loop used to register multiple courses for one student
   based on the student's number of courses entered.
 */
	for(int a=1; a<=stud.No_subs; a++) {
		cout<<"           Enter Subject Name: ";
		cin.ignore();
		cin.get(stud.Sub_des,100);
		out_account<<stud.Sub_des<<endl;
		cout<<"           Enter Subject code: ";
		cin.ignore();
		cin.get(stud.Sub_code,100);
		out_account<<stud.Sub_code<<endl;
		cout<<"           Enter grade for quiz one: ";
		cin>>stud.Q1;
		out_account<<stud.Q1<<endl;
		cout<<"           Enter grade for Labs 1 and 2: ";
		cin>>stud.Lab1_2;
		out_account<<stud.Lab1_2<<endl;
		cout<<"           Enter grade for quiz two: ";
		cin>>stud.Q2;
		out_account<<stud.Q2<<endl;
		cout<<"           Enter grade for Lab 3: ";
		cin>>stud.Lab3;
		out_account<<stud.Lab3<<endl;
		cout<<"           Enter grade for quiz 3: ";
		cin>>stud.Q3;
		out_account<<stud.Q3<<endl;
		cout<<"           Enter lab 4 grade: ";
		cin>>stud.Lab4;
		out_account<<stud.Lab4<<endl;
		cout<<"           Enter grade for quiz 4: ";
		cin>>stud.Q4;
		out_account<<stud.Q4<<endl;
		cout<<"           Enter lab 5 grade: ";
		cin>>stud.Lab5;
		out_account<<stud.Lab5<<endl;
	}
	return;
}

//THIS CREATES/OPENS THE DATABASE FILE AND APPENDS THE NEXT REGISTERED STUDENT DATA
void database_file(char FName[100], char MName[100], char LName[100], char Course[100], string Section){
	database_in.open("database\\databasefile.txt");
	if(is_empty(database_in)){ //CHECKS IF THE FILE IS EMPTY; IF TRUE, 1 IS OUTPUTED INTO THE FILE. THIS NUMBER IS FOR THE NUMBERING IN OPTION 2
		database_in.close();
		database_out.open("database\\databasefile.txt");
		database_out<<1<<endl;
		database_out.close();
	}
	database_in.close();
	database_out.open("database\\databasefile.txt",ios::app); //APPENDS THE STUDENT DATA
	database_out<<FName<<endl;
	database_out<<MName<<endl;
	database_out<<LName<<endl;
	database_out<<Course<<endl;
	database_out<<Section<<endl;
	database_out.close();
	database_in.open("database\\databasefile.txt");
	int no=0;
	char ch;
		while (database_in.get(ch)){
		if (ch == '\n')
        no++;
	}
	no/=5;//number of students in database file
	database_in.close();
	database_out.open("database\\databasefile.txt",ios::app);
	database_out<<no+1<<endl; //THIS OUTPUTS THE NEXT NUMBER THAT WILL BE ASSIGNED TO THE NEXT STUDENT INTO THE DATABASE FILE
	database_out.close();
	return;
}

//FOR OPTION 2: VIEW LIST OF REGISTERED STUDENTS
void view_database(ifstream& database_in){
	int no,i=0,check=1;
	char FirstName[100]="N/A", MidName[100]="N/A", LastName[100]="N/A", Crse[100]="N/A",c,Sctn[100]="N/A";
	while (database_in.get(c)){ //CHECKS THE NUMBER OF LINES IN THE DATABASE FILE
		if (c == '\n')
        i++;
	}
	i/=5;//number of students
	database_in.close();
	database_in.open("database\\databasefile.txt");//CHECKS IF THE FILE EXISTS; BECAUSE THE USER MIGHT MISCLICK 2 IN THE FIRST USE OF THE PROGRAM
		if(database_in.fail()){
			cout<<"File doesn't exist."<<endl;
			system("pause");
			SystemMain();
		}
	cout<<"\n  ****************************************************************************************************************************************************************************************************\n";
	cout<<"  ************************************************************************************ R E G I S T E R E D  S T U D E N T S **************************************************************************\n";
	cout<<"  ****************************************************************************************************************************************************************************************************\n\n";
//	cout<<"\tNo.\t\t|Last Name\t\t|First Name\t\t\t\t|Middle Name\t\t\t|Course\t\t\t\t|Section\n"<<endl;
	cout<<"    Total Number of Registered Students:  "<<i<<endl;
	while(check<=i){ //INPUTS THE STUDENT DATA FROM THE DATABASE FILE
	    for(int m=1;m<=6;m++){
	    	if(m==1){
	    		database_in>>no;
			}
			if(m==2){
				database_in.ignore();
				database_in.getline(FirstName,100,'\n');
			}
			if(m==3){
				database_in.getline(MidName,100,'\n');
			}
			if(m==4){
				database_in.getline(LastName,100,'\n');
			}
			if(m==5){
				database_in.getline(Crse,100,'\n');
			}
			if(m==6){
				database_in.getline(Sctn,100,'\n');
			}
		}
		cout<<endl;
		//DISPLAYING THE STUDENT DATA FROM THE DATABASE FILE ONTO THE SCREEN
		system("powershell write-host -fore DarkYellow \"`tNo.`t`t`t\" -nonewline");
		cout<<no<<endl;
		system("powershell write-host -fore DarkYellow \"`tFull Name:`t`t\" -nonewline");
		cout<<LastName<<", "<<FirstName<<" "<<MidName<<endl;
		system("powershell write-host -fore DarkYellow \"`tCourse - Section:`t\" -nonewline");
		cout<<Crse<<" - "<<Sctn<<endl;
//		cout<<"\t("<<no<<")"<<"\t\t"<<LastName<<"\t\t"<<FirstName<<"\t\t\t\t\t"<<MidName<<"\t\t\t"<<Crse<<"\t\t\t"<<Sctn<<endl;
		cout<<"\t_______________________________________________________________________________________________________________________________________________________________"<<endl;
		check++;
	}
	return;
}

//FOR OPTION 3: TO SEARCH FOR AN ACCOUNT
void search_student(ifstream& in_account){
	char sub_code[100]={"N/A"},fname[100]="N/A",mname[100]="N/A",lname[100]="N/A",sub_des[100]="N/A",course[100]="N/A";
	int year, id=0,no_subs=0,units=0,q1=0,lab1_2=0,q2=0,lab3=0,q3=0,lab4=0,q4=0,lab5=0;
	string pw="N/A",filen="N/A",section="N/A";

	for(int lineno=1;lineno<=10;lineno++){ //THIS IS BECAUSE FOR EVERY STUDENT FILE, 10 LINES IN THE FILE ARE DEDICATED FOR THE PERSONAL INFO, AND THE NEXT LINES ARE FOR THE SUBJECTS
		if(lineno==1){
			getline(in_account,filen);//for STRING DATA TYPE input fstream
		}
		if(lineno==2){
			getline(in_account,pw);
		}
		if(lineno==3){
			in_account>>id;//for INT DATA TYPE input fstream
		}
		if(lineno==4){
			in_account.ignore();
			in_account.getline(fname,100,'\n');//for CHAR ARRAY DATA TYPE input fstream
		}
		if(lineno==5){
			in_account.getline(mname,100,'\n');
		}
		if(lineno==6){
			in_account.getline(lname,100,'\n');
		}
		if(lineno==7){
			in_account>>year;
		}
		if(lineno==8){
			in_account.ignore();
			getline(in_account,section);
		}
		if(lineno==9){
			in_account.getline(course,100,'\n');
		}
		if(lineno==10){
			in_account>>no_subs;
		}
	}
		//DISPLAYS THE PERSONAL INFO ONTO THE CONSOLE
		cout<<"\n\n\n   Full name: "<<fname<<" "<<mname<<" "<<lname<<endl;
		cout<<"   Registration Year: "<<year<<endl;
		cout<<"   Section: "<<section<<endl;
		cout<<"   Course: "<<course<<endl;
		cout<<"  **************************************************************************************************************************************************************************************************\n";
		cout<<"  ******************************************************************************************** S T U D E N T   M A R K L I S T *********************************************************************\n";
		cout<<"  **************************************************************************************************************************************************************************************************\n\n";  
		cout<<"  Subject(Subject code)    \t\tQuiz1\t\tLabs 1&2\t\tQuiz2\t\tLab 3\t\tQuiz3\t\tLab 4\t\tQuiz4\t\tLab 5\t\tTotal\t\tGrade\n";
		cout<<"  _________________________________________________________________________________________________________________________________________________________________________________________________\n";
		
	for(int t=1;t<=no_subs;t++){ //THIS INPUTS STUDENT'S SUBJECT DATA FROM HIS FILE
		for(int lineno=1;lineno<=10;lineno++){
			if(lineno==1){
				in_account.ignore();
				in_account.getline(sub_des,100,'\n');
			}
			if(lineno==2){
				in_account.getline(sub_code,100,'\n');
			}
			if(lineno==3){
				in_account>>q1;
			}
			if(lineno==4){
				in_account>>lab1_2;
			}
			if(lineno==5){
				in_account>>q2;
			}
			if(lineno==6){
				in_account>>lab3;
			}
			if(lineno==7){
				in_account>>q3;
			}
			if(lineno==8){
				in_account>>lab4;
			}
			if(lineno==9){
				in_account>>q4;
			}
			if(lineno==10){
				in_account>>lab5;
			}
			
		}
		int totalMark=(q1+lab1_2+q2+lab3+q3+lab4+q4+lab5)/8; //CALCULATES THE AVERAGE GRADE
		//OUTPUTS THE STUDENT'S SUBJECT DATA ONTO THE CONSOLE
		cout<<" "<<sub_des<<"("<<sub_code<<")\n\t\t\t\t\t"<<q1<<" \t\t"<<lab1_2<<" \t\t\t"<<q2<<" \t\t"<<lab3<<" \t\t"<<q3<<" \t\t"<<lab4<<" \t\t"<<q4<<" \t\t"<<lab5<<" \t\t"<<totalMark<<" \t\t";
		grade_calculator(totalMark); //RUNS THE GRADE_CALCULATOR FUNCTION WHICH DISPLAYS A STRING
		cout<<endl;
		cout<<" _________________________________________________________________________________________________________________________________________________________________________________________________"<<endl;
		}
	return;
}


//FOR OPTION 5: TO DELETE AN ACCOUNT
void Delete_account(){
	cout<<"\n  ****************************************************************************************************************************************************************************************************\n";
	cout<<"  ******************************************************************************************* A C C O U N T  D E L E T I O N *************************************************************************\n";
	cout<<"  ****************************************************************************************************************************************************************************************************\n\n";
	string usern,usn,password,pw,d="database\\",ext=".txt";
	cout<<"Enter your username: ";
//	cin.ignore();
	getline(cin,usern,'\n');
	stringstream filen,to_delete;
	filen<<d<<usern<<ext;
	in_account.open(filen.str().c_str()); //CHECKS IF THE FILE WITH THE SAME USERNAME AS INPUTTED BY THE USER EXISTS IN THE DATABASE DIRECTORY
	if(in_account.fail()){
		cout<<"File doesn't exist."<<endl;
		system("pause");
		RepeatOption();
	}
	getline(in_account,usn); //IF THE FILE EXISTS, GET THE USERNAME
	getline(in_account,password); //AND THE PASSWORD
	in_account.close();
	system("if not exist \"database\\deletedaccounts\" mkdir database\\deletedaccounts"); //THIS CHECKS IF THE DIRECTORY DELETEDACCOUNTS EXISTS; THIS IS WHERE THE DELETED ACCOUNTS ARE MOVED
	cout<<"\nAccount found."<<endl;
	cout<<"Enter your password to delete your account: "; //PROMPTS FOR THE STUDENT FILE PASSWORD
	getline(cin,pw);
	if(password==pw){ //IF THE PASSWORDS MATCH, THIS CODE BLOCK WILL RUN AND THE FILE WILL BE MOVED INTO THE DELETEDACCOUNTS DIRECTORY
		string mov="move \"database\\",dr="\" database\\deletedaccounts\\";
		to_delete<<mov<<usern<<ext<<dr;
		system(to_delete.str().c_str());
		cout<<"File deleted."<<endl;
	}
	else{ //ELSE, THE OPTIONS WILL BE DISPLAYED
		cout<<"Wrong password."<<endl;
		system("pause");
		RepeatOption();
	}
	return;
}


//MODIFY ACCOUNT
void Modify_account(){
	cout<<"\n  ****************************************************************************************************************************************************************************************************\n";
	cout<<"  ******************************************************************************* M O D I F Y  A C C O U N T *****************************************************************************************\n";
	cout<<"  ****************************************************************************************************************************************************************************************************\n\n";
	string usern,usn,password,pw,d="database\\",ext=".txt";
	int id;
	cout<<"Enter your username: ";
	getline(cin,usern,'\n');
	stringstream filen;
	filen<<d<<usern<<ext;
	in_account.open(filen.str().c_str()); //CHECKS IF THE USERNAME ENTERED BY THE USER MATCHES ONE OF THE FILENAMES IN THE DATABASE DIRECTORY
	if(in_account.fail()){
		cout<<"File doesn't exist."<<endl; //IF NOT, OPTIONS WILL BE DISPLAYED
		system("pause");
		RepeatOption();
	}
	getline(in_account,usn); //GETS THE USERNAME FROM THE FILE
	getline(in_account,password); //AND THE PASSWORD
	in_account>>id; //AND THE ID
	in_account.close();
	cout<<"\nAccount found."<<endl;
	cout<<"Enter your password to modify your account: "; //PROMPTS FOR THE PASSWORD
	getline(cin,pw);
	if(password==pw){ //IF THE PASSWORDS MATCH, THE CODE BLOCK BELOW WILL RUN.  IF THE FILE TO BE OUTPUTTED TO FAILS TO OPEN, OPTIONS WILL BE DISPLAYED
		out_account.open(filen.str().c_str()); //WHILE IF THE FILE SUCCEEDS TO OPEN, IT WILL RUN THE MODIFY() FUNCTION
		if(out_account.fail()){
			cout<<"Account opening failed"<<endl;
			system("pause");
			RepeatOption();
		}
		stud.fileN=usn;
		stud.password=password;
		stud.ID=id;
		Modify();
		out_account.close();
	}
	else{ //ELSE, THE OPTIONS WILL BE DISPLAYED
		cout<<"Wrong password."<<endl;
		system("pause");
		RepeatOption();
	}
	return;
}


//GRADE CALCULATOR; DISPLAYS STRING
void grade_calculator(int totalMark){
	char grade;
	if(totalMark>=90 && totalMark<=100)
        cout<<"A+";
    else if(totalMark>=80 && totalMark<90)
    	cout<<"A";
    else if(totalMark>=70 && totalMark<80)
    	cout<<"B";
    else if(totalMark>=60 && totalMark<70)
        cout<<"C";
    else if(totalMark>=50 && totalMark<60)
        cout<<"D";
    else if(totalMark>=0 && totalMark<50)
        cout<<"F";
    else
    	cout<<"NG";   
    return;
}

//FOR STRINGSTREAM, FOR FILENAME, FOR FILE LOCATE
//FOR APPENDING THE STUDENT ID INTO THE FILENAME
string operator+(string const &a, int b) {
  ostringstream oss;
  oss << a << b;
  return oss.str();
}

//START OF C++ PROGRAM
int main(){
	SystemMain();
	
	return 0;
}
