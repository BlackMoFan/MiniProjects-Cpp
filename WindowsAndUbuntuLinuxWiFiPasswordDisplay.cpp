//SIMPLE PROGRAM TO DISPLAY ONCE CONNECTED WIFI PROFILES AND
//OFFER OPTION OF DISPLAYING DETAILS ON ANY PROFILE

//ROD MORENO
//THIS WORKS ON WINDOWS USING THE NETSH COMMAND LINE UTILITY
//THIS ALSO WORKS IN LINUX BY UTILIZING THE NATIVE COMMAND LINE COMMANDS

//IF WINDOWS
#ifdef _WIN32
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <fstream>
#include <typeinfo>
#include <sstream>

std::ofstream out_display;
std::ifstream in_display;


//from https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
//THIS IS OPTIONAL BECAUSE WE CAN ALSO USE "command > file.txt" TO STORE THE RESULT OF THE TERMINAL COMMAND. BUT IT IS GOOD TO STUDY DOING THIS WITHOUT THE system()
std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

void createFile(std::ofstream& out_display, std::string filename){
	std::stringstream ss;
	ss << filename;
	out_display.open(ss.str().c_str());
	if(out_display.fail()){
		std::cout << "File creation failed.\n";
	}
	return;
}

void openFile(std::ifstream& in_display){
	in_display.open("outputFile.txt");
	if(in_display.fail()){
		std::cout << "File not found.\n";
	}
	return;
}

void getProfiles(){
	//CREATE FILE TO STORE RESULT FROM COMMAND PROMPT
	std::cout << "Windows environment detected.\n";
	createFile(out_display, "outputFile.txt");
	std::string result = exec("netsh wlan show profiles");
	out_display << result << "\n";
	out_display.close();

	//OPEN THE CREATED FILE
	openFile(in_display); //open ifstream
	int l, at, soss, sop;
	char discardData[100], profiles[100], c;
	std::string currentProfile;
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
	}

	//CHECKS THE NUMBER OF PROFILES
	while (in_display.get(c)){
		if (c == '\n')
			l++;
	}
	l -= 2;
	in_display.close();

	//GET NAME OF PROFILES
	std::cout << "These are all your WiFi Profiles:\n\n";
	openFile(in_display); //open ifstream
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
	}
	int num = 1;
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
		std::string profile(profiles);
		soss = profile.size();
		at = profile.find(':');
		at += 2;
		currentProfile = profile.substr(at,soss);
		sop = currentProfile.size(); //length of profile name
		std::cout << num << ".  " << currentProfile << "\n";
		num++;
	}
	in_display.close();

	//GET OPTION
	int option;
	std::cout << "Enter the number of profile you want to view its details:  ";
	std::cin >> option;

	//GET THE PROFILE NAME CORRESPONDING TO OPTION
	openFile(in_display); //open ifstream
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
	}
	num = 1;
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
		std::string profile(profiles);
		soss = profile.size();
		at = profile.find(':');
		at += 2;
		currentProfile = profile.substr(at,soss);
		num++;
		if (j == option){
			break;
		}
	}
	in_display.close();

	//PASTE PROFILE CHOSEN TO A FILE
	createFile(out_display, "profileFile.txt");
	out_display << currentProfile << "\n";
	out_display.close();

	//DISPLAY WIFI PROFILE DETAILS WITH PASSWORD
	std::string comm = "netsh wlan show profile \"";
	std::string keys = "\" key=clear";
	std::stringstream theCommand;
	theCommand << comm << currentProfile << keys;
	std::cout << "\n\nCommand entered is \"" << theCommand.str().c_str() << "\"\n";
	std::cout << "Note:  You can view your password under Security settings -> Key Content\n";
	std::cout << "Result: \n\n";


	//CALL CODE FROM STACKOVERFLOW
	std::string resultProfile = exec(theCommand.str().c_str());
	std::cout << resultProfile << "\n";

	return;
}

int main(){
	char choice;
	do{
		getProfiles();
		std::cout << "Another session? Y/N : ";
		std::cin >> choice;
		system("cls");
	}while(choice == 'Y');


	return 0;
}



#else //IF LINUX
//--------------------------------------------------------------------------------------------



#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::ofstream out_display;
std::ifstream in_display;

void openFile(std::ifstream& in_display){
	in_display.open("outputFile.txt");
	if(in_display.fail()){
		std::cout << "File not found.\n";
	}
	return;
}

void getProfiles(){
	//CREATE FILE TO STORE RESULT FROM TERMINAL
	std::cout << "Non-Windows environment detected. Linux is a strict system which makes it secure. And so, the directory in which your WiFi details are stored is locked.  If prompted, kindly enter your password to allow the program to access that directory.\n";
	system("if test -f outputFile.txt; then rm outputFile.txt; fi");
	system("ls /etc/NetworkManager/system-connections/ >> outputFile.txt");


	//OPEN THE CREATED FILE
	openFile(in_display); //open ifstream

	//CHECKS THE NUMBER OF PROFILES
	int l = 0;
	char c;
	while (in_display.get(c)){
		if (c == '\n')
			l++;
	}
	std::cout << "Total Profiles: " << l << "\n";
	in_display.close();

	//GET NAME OF PROFILES
	int at;
	char profiles[100];
	std::string currentProfile;
	std::cout << "These are all your WiFi Profiles:\n";
	openFile(in_display); //open ifstream
	int num = 1;
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
		std::string profile(profiles);
		at = profile.find('.');
		currentProfile = profile.substr(0,at);
		std::cout << num << ".  " << currentProfile << "\n";
		num++;
	}
	in_display.close();

	//GET OPTION
	int option;
	std::cout << "Enter the number of profile you want to view its details:  ";
	std::cin >> option;

	//GET THE PROFILE NAME CORRESPONDING TO OPTION
	int soss;
	openFile(in_display); //open ifstream
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
		std::string profile(profiles);
		soss = profile.size();
		currentProfile = profile.substr(0,soss);
		if (j == option){
			break;
		}
	}
	in_display.close();

	//PASTE PROFILE CHOSEN TO A FILE
	std::string comm = "sudo cat /etc/NetworkManager/system-connections/";
	std::string redirect = " >> profileFile.txt";
	std::stringstream theCommand;
	system("if test -f profileFile.txt; then rm profileFile.txt; fi");
	theCommand << comm << currentProfile << redirect;
	system(theCommand.str().c_str());

	// std::cout << theCommand.str().c_str() << "\n";

	//DISPLAY WIFI PROFILE DETAILS WITH PASSWORD
	std::cout << "\n\nCommand entered is \"" << theCommand.str().c_str() << "\"\n";
	std::cout << "Note:  You can view your password under wifi security -> psk\n";
	std::cout << "Result: \n\n";


	//PASTE THE CONTENT OF profileFile.txt containing the WiFi details
	in_display.open("profileFile.txt");
	if(in_display.fail()){
		std::cout << "File not found.\n";
	}
	while (in_display.get(c)){
		std::cout << c;
	}
	in_display.close();

}

int main(){
	char choice;
	do{
		getProfiles();
		std::cout << "\n\nAnother session? Y/N : ";
		std::cin >> choice;
		system("clear");
	}while(choice == 'Y');

	return 0;
}

#endif //END OF PROGRAM
