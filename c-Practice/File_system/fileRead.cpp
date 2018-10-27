#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    std::fstream TheFile ( "tt.txt", std::fstream::in);

    if (TheFile.is_open())
    {
	    string Line;
		string word = "ipsum" ;
	    int curline = 0 ;
	    int countp = 0;
		while (getline (TheFile, Line) ) 
		{
		//	cout<<Line <<endl;
		
			if (Line.find(word.c_str()) != string::npos ) {
				
				int pos = word.find(word.c_str()) ;
				cout<<"Bhargavi is starting with the position of " << pos <<"   word   "<< word << endl;
				cout<<"found " <<word << "  was found  "<< curline <<"****times" <<endl;
				curline++ ;
			}
				cout<<word.c_str() <<endl;
		/*	
			while(!TheFile.eof()) 
			{
				TheFile >> word ;
			//	cout<<word.c_str() <<endl;
				countp++;
				
			}
		*/	
		cout <<countp << "    countp " <<endl;
			while(TheFile >> word) 
			{
				int pos = word.find(word.c_str()) ;
				cout<<"Bhargavi is starting with the position of " << pos <<"   word   "<< word << endl;
				countp++;	
				cout  << "countp " <<countp<<endl;
			}		
			
		cout<<"found " << word.c_str() << "  was found  "<< ++curline <<"times" <<endl;
		cout << "Number of  '  "<< word  <<"    '   words in file is " << ++countp;	
		}
		
		TheFile.close() ;
		
		
		word.clear() ;

    }
    else
    {
        cout << "the file  does not exist!" << endl;
    }

    return 0;
}
