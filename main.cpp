/* Written by Blake Mizzell
 * This program reads a word file and does the following:
 * Counts the number of words
 * Counts the number of unique words
 * Takes a users input and counts how many time it occurs
 */

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

int countWords(const char *);
int countUnique(const char *);
void compareInput(const char*, string);
void printResults(string, string, int);

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Proper usage ./project1 sample.txt query.txt" << endl;
		return 0; 
	}
    //opens file to read from
	ifstream inFile(argv[1]);
    //stream for output file
    ofstream outFile;
    outFile.open("outFile.txt");
	string word;
    while (inFile >> word) {
        //loop to convert to lower case and remove punctuation
	    for (unsigned int i = 0; i < word.length(); i++) {
		    word[i] = tolower(word[i]);
            if (ispunct(word[i]) || (!isalpha(word[i]))) { 
                    word[i] = ' ';
            }        
                
        }
        word += " ";
        //outputs the clean strings to a new file
	    outFile << word;
    }
	inFile.close();
    outFile.close();
    const char *clean = "outFile.txt";
//    const char *found = "found.txt";
    int count = countWords(clean);
	cout << "The number of words found in the file was " << count << endl;
	int uniqueCount = countUnique(clean);
	cout << "The number of unique words found in the file was " << uniqueCount << endl;
    string input;
    //loop that keeps getting user input and searching for it till a certian input
	while (input != "^C") {
		cout << endl << "Please enter a word: ";
		cin >> input;
        compareInput(clean, input);
	}
	return 0;
}

//counts how many words are in the file
int countWords (const char *fp) {
    int count = 0;
    string word;
    ifstream file;
    file.open(fp);
    while (file >> word) {
        count ++;
    }
    file.close();
    return count;
}    

//counts how many unique words are in the file
int countUnique(const char *fp) {
	int count = 0, check = 0, p = 0;
    string word;
    string wordbank[10000];
    ifstream file;
    file.open(fp);
    while (file >> word) {
        wordbank[p] = word;
        for (int i = 0; i < 10000; i++) {
            if (word == wordbank[i]) {
                cout << word << "\t" << wordbank[i] << endl;
                check++;
            }
        }    
        p++;
        if (check == 1) {
            cout << word << endl;
            count++;
        }
        check = 0;
    }    
    file.close();
    return count;
}

//counts how many times the user input occurs in the file
void compareInput (const char *fp, string input) {
    unsigned int check = 0, count = 0;
    string word;
    string wordFound;
    ifstream file;
    file.open(fp);
    while (file >> word) {
        for (unsigned int i = 0; i < input.length(); i++) {
            //if the input matches the word or input is a question mark incrament check
            if ( (input[i] == word[i]) || (input[i] == '?') ) {
				check++;
			}
            //if the check is equal to input length add word to wordFound and incrament count
            if ( (check == input.length()) && (input.length() >= word.length() ) ) {
                wordFound = word;
                count++;
            }    
		}
        check = 0;
    }    
    file.close();
    //print results with another function
    printResults(wordFound,input,count); 
}    

//function to print the results
//does not work for multiple words but works for 1
void printResults (string wordFound, string input, int count) {
    if (count == 0) {
        cout << endl << "The word " << input; 
        cout << " appears " << count << " times in the document" << endl << endl;
    }    
    else if (count == 1) {
        cout << endl << "The word " << wordFound; 
        cout << " appears " << count << " time in the document" << endl << endl;
    }
    else {
        cout << endl << "The word " << wordFound; 
        cout << " appears " << count << " times in the document" << endl << endl;
    }     
}     
