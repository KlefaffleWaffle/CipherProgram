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
std::string defaultPath = "/home/pi/Documents/";
std::string fileName = "";


//determines where encryption/decryption starts and stops
std::vector<int> startNStop;

//determines whether to encrypt or decrypt
bool HandleMainInput(std::string filePath);

//adds backslashes in case input string has a space
std::string addBackSlashes(std::string);

//Encrypts the file.
void Encrypt(std::string filePath);

//Searches for encryption triggers
void scanFile (std::fstream&);

//True means Encrypt False means Decrypt
//Not to be confused with "CipherIsOn" which references whether to apply any effect to txt.
bool encrypt = true;

//Converts filename from x --> xE.txt --> xD.txt
std::string newFileName(std::string);

//Used to handle situations where fileName has ".txt" in it.
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
		
		//for every character in Input, check to see if it's space.
		//If so, insert "\\" before adding the space
			for (int i = 0; i < inputString.size(); i++){
					if(inputString.at(i) == ' '){
						tempString1 += '\\';
					}
					
					tempString1 += inputString.at(i);
					
			}
				
			return tempString1;

}

void Encrypt(std::string filePath){
	std::string fName = defaultPath + filePath;
	 
	std::fstream myFile;
	myFile.open(fName);
	int TrackVector = -1;
	
	std::string line;
	std::string newLine;
	
	//reads the file line by line looking for encryption points
	scanFile(myFile);
	
	std::string newFilePath =defaultPath + newFileName(filePath) + ".txt";
	//std::fstream newFile(newFilePath);
	
	std::ofstream newFile;
	newFile.open(newFilePath);
	
	int charTracker = 0;
	int vectorTracker = 0;
	
	/*==================================
	 * Means Modify NOT Encrypt/Decrypt
	 * =================================
	 * */
	bool cipherIsOn = false;
	
	//myFile not to be confused with newFile
	
	//I'm not super familiar with reseting files. 
	//The following is a modified code from stack overflow
	myFile.clear();
	myFile.seekg(0, std::ios::beg);
	//end of copy
	
	while(std::getline(myFile,line)){
	newLine = "";
	
	
		//for every char in the line
		for(int i = 0; i < line.size(); i++,charTracker++){
			
			//if charValue is = to a value that turns encryption on or off
			if(startNStop.size() > 0 && charTracker == startNStop.at(vectorTracker)){
			
				if(cipherIsOn == true){
					cipherIsOn = false;
				}else{
					cipherIsOn = true;
				}
				
				//once we hit an encryption trigger, advance the index for StartNStop
				if(vectorTracker < startNStop.size()-1){
				vectorTracker++;
				}
			}
			char c = line.at(i);
			
			if(cipherIsOn){
				//Heart of Encryption/Decryption
				
				if(encrypt == true){
				c+= 15;
				
					if(c > 126){
						int diff = c-126;
						c= 32+diff;
					}
				}else{
					c-=15;
					if(c < 32){
						int diff = 32-c;
						c = 126-diff;
					}
				}
			}
			//adds the char, whether original or ciphered to newLine, which will be added to newFile
			newLine += c;
		}
		newFile << newLine << "\n"; 
	
	}	
	
}

//actually scans file
void scanFile (std::fstream& file){
	//Rename to Scan File
	int startEncrypt;
	int endEncrypt;
		
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
		
		//for every character in the line
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
		//Used to keep track of which character we are on in the document
		characterCounter += line.size();

		
		line = "";
		
		
	}

}

//creates new filename x --> xE --> xD
std::string newFileName(std::string s){

txtInInput = true;

	std::string newName = "";
	std::string testString = "";
	
	//sets testString to last four chars of input s;
	for(int i = s.size() -4; i < s.size() && i > 0; i++){
		testString = testString + s.at(i);
	}
	std::string txt = ".txt";
	
	
	//if+for checks to see if testString matches ".txt"
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
	

	//if filename has ".txt" in it
	if(txtInInput == true){

	//adding all chars UNTIL '.'
		for(int i = 0; i < s.size()-4; i++){
			newName = newName + s.at(i);
		}
		
	}else{

		newName = s;
	}

	if(encrypt){
			newName = newName+"E";	
		
	}else{
		
		if(newName.at(newName.size()-1) == 'E'){
			newName.at(newName.size()-1) = 'D';

		}else{
			newName += 'D';
		}
		
	}
	return newName;
}
