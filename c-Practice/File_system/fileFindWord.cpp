#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
using namespace std;

int main()
{
    string name; 
  //  cout << "enter the name of file : " << endl;
  //  cin >> name;

    // opening the file
  //  std::fstream TheFile (name.c_str(), std::fstream::out);
    std::fstream TheFile ( "test.txt", std::fstream::out);

    if (TheFile.is_open())
    {
        string word; // hold the word user inputs to be searched for
        cout << "enter the word: " << endl;
        cin>>word ;

        string Line;
        int curline = 0;
	 
			while (getline (TheFile, Line) ) 
			{
				cout<<Line <<endl;
			
		/*	cout<< "  :loop is started  " <<endl;
			char found = Line.find(word.c_str()) ;
			
			if (found != string::npos ) {
			
				
				cout<<"found " <<word << "  was found  " <<curline <<endl;
			}
				
		*/		
				
			}
			
	
        

        cout << "the word " << word << " was found " << " times" << endl;
    }
    else
    {
        cout << "the file " << name << " does not exist!" << endl;
    }

    cout << "press enter to exit " << endl;
    int c = getch();
    return 0;
}
