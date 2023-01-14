// Cipher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//This file is largely for personal use and as demonstration of abilities.
//I do not plan on updating it, except as for when I need it and may or may not publish updates.

//Some elements of this code were copied and modified from my own unpublished project titled, MakeFile Maker

/*
 * To encrypt a message type [${ and }$] in your txt document;
 * */

bool defaultFolderIsActive = false;
std::string boolValue(bool);
std::string defaultPath = "/home/pi/Documents/";
std::string adtnlSubDirectories = "";
std::string fileName = "";

int startEncrypt;
int endEncrypt;

std::vector<int> startNStop;
std::vector<int> newLinePos;

bool HandleMainInput(std::string filePath);
std::string addBackSlashes(std::string);

void Encrypt(std::string filePath);

bool scanString (std::fstream&);

bool encrypt = true;

std::string newFileName(std::string);

bool txtInInput = false;

int main()
{
    
    if (defaultFolderIsActive == false) {
        std::cout << "Default folder is deactivated. Please Input fileName\n";
        defaultPath = "";
    } else {
        std::cout << "Default folder is activated. Please Input fileName after: " <<  defaultPath << "\n";;
    }
    std::string filePathNoBackSlash;
    std::cin >> filePathNoBackSlash;
    std::cout << "Do you want to encrypt (E) or Decrypt(D)? ((E/D)\n";
    HandleMainInput(filePathNoBackSlash);
    
   Encrypt(filePathNoBackSlash);
   std::cout << "Done\n";

}

//returns bool value as "True or False"
std::string boolValue(bool b)
{
    std::string s;
    if (b) {
        s = "True\n";
    }
    else if (b == false) {
        s = "False\n";
    }
    else {
        s = "AJD error: Bool has not been initialized";
    }

    return s;
}

//Determines weather to Encrypt or Decrypt
bool HandleMainInput(std::string filePath) {
    std::string EorD;
    std::cin >> EorD;
	std::string newPath;
	    
    newPath = addBackSlashes(filePath);
    std::cout << "New path is: " << newPath <<std::endl;

    if (EorD.at(0) == 'D' || EorD.at(0) == 'd') {
	
        encrypt = false;
    }
    else if (EorD.at(0) == 'E' || EorD.at(0) == 'e') {
    
    }else {
        std::cout << "Defaulting to true\n";
    }
  
	
return encrypt;

}

//returns inputString but with "\" before spaces
std::string addBackSlashes(std::string inputString){
//copied and edited from an unpublished project created by Austin Devine called, "MakeFile Maker";


		std::string tempString1 = "";
			for (int i = 0; i < inputString.size(); i++){
					if(inputString.at(i) == ' '){
						tempString1 += '\\';
					}
							//cout << "\t Looping Through \'Add Backslashes\' successfully" <<endl;
					tempString1 += inputString.at(i);
					
				}
				inputString = tempString1;
				//cout << "\t \'Add Backslashes\' finished successfully" <<endl;
				return tempString1;

}

void Encrypt(std::string filePath){
	std::string fName = defaultPath + filePath;
	 
	std::fstream myFile;
	myFile.open(fName);
	int TrackVector = -1;
	
	std::string line;
	std::string newLine;
	//reads the file line by line looking for
	bool pointless = scanString(myFile);
	
	std::string newFilePath =defaultPath + newFileName(filePath) + ".txt";
	//std::fstream newFile(newFilePath);
	
	std::ofstream newFile;
	if(encrypt){
	newFile.open(newFilePath);

	}else{
	newFile.open(newFilePath);

	
	}
	int charTracker = 0;
	int vectorTracker = 0;
	bool cipherIsOn = false;
	
	//I'm not super familiar with reseting files. 
	//The following is a modified code from stack overflow
	myFile.clear();
	myFile.seekg(0, std::ios::beg);
	//end of copy
	
	while(std::getline(myFile,line)){
	newLine = "";
	
	
		//for every char in the line
		for(int i = 0; i < line.size(); i++,charTracker++){
			if(startNStop.size() > 0 && charTracker == startNStop.at(vectorTracker)){
			
				if(cipherIsOn == true){
					cipherIsOn = false;
				}else{
					cipherIsOn = true;
				}
				if(vectorTracker < startNStop.size()-1){
				vectorTracker++;
				}
			}
			char c = line.at(i);
			
			if(cipherIsOn){
				//
				if(encrypt == true){
					for(int j = 0; j < 15; j++){
					if (c > 126){
							c = 32;
					}
					c++;
					}
				}else{
					for(int j = 0; j < 15; j++){
						if (c < 32){
							c = 126;
						}
						c--;
					}
				}
			}
			
			newLine += c;
		}
		newFile << newLine << "\n"; 
	
	}

	
	//
	//save filename
	//create andFillnewFile
	//copy into old file || delete old file and rename new. 
	
	
	
}

//actually scans file
bool scanString (std::fstream& file){
	//Rename to Scan File

		
	int sqrOpnBr = -1;
	int dllrOpnSgn=-1;
	int crlyOpnBr=-1;
	
	int sqrClsdBr = -1;
	int dllrClsdSgn=-1;
	int crlyClsdBr=-1;
	
	bool foundEnd = true;
	std::string line;
	int characterCounter = 0;
	while(file.good()){
		//file >> line;
		std::getline(file, line);
		
		
		for(int i = 0; i < line.size(); i++){
	
	//Vector startNStop is added in pairs. If size is odd, then it needs an EndPoint, if Even, it's only looking for startingPoint
		if(startNStop.size()%2 == 0){
			if(line.at(i) == '[' ){
			sqrOpnBr = i;
			
			}
			if(line.at(i) == '$'){
			dllrOpnSgn = i;
			
			}
			if(line.at(i) == '{'){
			crlyOpnBr = i;
			
			}
		
			if (dllrOpnSgn == sqrOpnBr+1 && crlyOpnBr == dllrOpnSgn+1){
			
			startEncrypt= crlyOpnBr+1;
			startNStop.push_back(characterCounter +startEncrypt);
			
			foundEnd = false;
	 sqrOpnBr = -1;
	 dllrOpnSgn=-1;
	 crlyOpnBr=-1;
			}
		}
	
		if(startNStop.size()%2 == 1){
	
	
			if(line.at(i) == ']' ){
			sqrClsdBr = i;
		
			}
			if(line.at(i) == '$'){
			dllrClsdSgn = i;
			
			}
			if(line.at(i) == '}'){
			crlyClsdBr = i;
		
			}
		
				if (dllrClsdSgn == sqrClsdBr-1 && crlyClsdBr == dllrClsdSgn-1){
				endEncrypt= crlyClsdBr-1; 
				startNStop.push_back(characterCounter + endEncrypt);
		
	 sqrClsdBr = -1;
	 dllrClsdSgn=-1;
	 crlyClsdBr=-1;
				}
			}
			
		}
		characterCounter += line.size();

		
		line = "";
		
		
	}

	
	
	if(startNStop.size() > 0){
	return true;
	}else{
	return false;
	}
}

std::string newFileName(std::string s){
txtInInput = true;

std::string newName = "";
	std::string testString = "";
	for(int i = s.size() -4; i < s.size() && i > 0; i++){
		testString = testString + s.at(i);
	}

	std::string txt = ".txt";
	
	if(testString.size() < 4){
		testString = s;
		txtInInput = false;
	}
	
	for(int i = 0; i < 4 && txtInInput == true; i++){
		if(testString.at(i) != txt.at(i)){
			txtInInput = false;
			break;
		}
	}
	
	if(txtInInput == true){

		for(int i = 0; i < s.size()-4; i++){
			newName = newName + s.at(i);
		}
	}else{

		newName = s;
	}

	if(encrypt){
			newName = newName+"E";	
		
	}else{
		//some files may have .txt in them;
		int pos = 1;
		if(txtInInput == true){
			//pos = 4;
		}
		if(newName.at(newName.size()-pos) == 'E'){
			newName.at(newName.size()-pos) = 'D';

		}else{
			newName += 'D';
		}
		
	}
	return newName;
}
