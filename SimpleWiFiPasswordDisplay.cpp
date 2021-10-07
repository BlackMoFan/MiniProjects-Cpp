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

void openFile(std::ifstream& in_display){
	in_display.open("outputFile.txt");
	if(out_display.fail()){
		std::cout << "File not found." << std::endl;
	}
	return;
}

void getProfiles(){
	openFile(in_display); //open ifstream
	int l, at, soss, sop;
	char discardData[100], profiles[100], c;
	std::string currentProfile;
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
//		std::cout << discardData << std::endl;
	}
	while (in_display.get(c)){ //CHECKS THE NUMBER OF PROFILES
		if (c == '\n')
        l++;
	}
	l -= 2;
//	std::cout << l << std::endl;
	in_display.close();
	
	//GET NAME OF PROFILES
	std::cout << "These are all your WiFi Profiles:\n" << std::endl;
	openFile(in_display); //open ifstream
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
//		std::cout << discardData << std::endl;
	}
	int num = 1;
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
//		std::cout << profiles << std::endl;
		std::string profile(profiles);
		soss = profile.size();
		at = profile.find(':');
		at += 2;
		currentProfile = profile.substr(at,soss);
		sop = currentProfile.size(); //length of profile name
		std::cout << num << ".  " << currentProfile << std::endl;
		num++;
	}
	in_display.close();
	
	//GET OPTION
	int option;
	std::cout << "Enter the number of profile you want to view its details:  ";
	std::cin >> option;
	
	//GET PROFILE AGAIN
	openFile(in_display); //open ifstream
	for(int i = 0; i < 9; i++){
		in_display.getline(discardData,100,'\n');
//		std::cout << discardData << std::endl;
	}
	num = 1;
	for(int j = 1; j <= l; j++){
		in_display.getline(profiles,100,'\n');
		std::string profile(profiles);
		soss = profile.size();
		at = profile.find(':');
		at += 2;
		currentProfile = profile.substr(at,soss);
		sop = currentProfile.size(); //length of profile name
		num++;
		if (j == option){
			break;
		}
	}
	in_display.close();

	//PASTE PROFILE TO FILE
	out_display.open("profilesFile.txt");
	if(out_display.fail()){
		std::cout << "File creation failed" << std::endl;
	}
	out_display << currentProfile << std::endl;
	out_display.close();
//	for(int j = l; j > 0; j--){
//		in_display.getline(profiles,100,'\n');
//		std::cout << profiles << std::endl;
//	}

	//GET PROFILE PASSWORD
	std::string comm = "netsh wlan show profile \"";
	std::string keys = "\" key=clear";
	std::stringstream theCommand;
	theCommand << comm << currentProfile << keys;
	std::cout << "\n\nCommand entered is \"" << theCommand.str().c_str() << "\"" << std::endl;
	std::cout << "Note:  You can view your password under Security settings -> Key Content" << std::endl;
	std::cout << "Result: \n\n";
	
	std::string resultProfile = exec(theCommand.str().c_str());
	std::cout << resultProfile << std::endl;
	
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
