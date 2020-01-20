#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>





using namespace std;

//ERRORRRRRRRRRRRRRRRRS
bool errorInCoordinates(const vector<vector<char>>& vec,int x,int y)
	//ERROR-CHECK2 - IS COORDINATES VALID?             
{
	if(y<vec.size() && y>=0)                               
	{
		if (x<vec[y].size() && x>=0)
			return false;
		else
			return true;
	}
	else
		return true;
}
bool errorInSquare(const vector<vector<char>>& vec)
	// ERROR-CHECK1 == IS MATRIX CONSISTENT?
{
	char sample=vec[0].size();	// 0 is our sample row

	for (int i = 0; i < vec.size(); i++)
	{
		if(!(vec[i].size()==sample))
			return true;
	}
	return false;
}
bool errorInLRDU(string path)
{
	string allowed="lrdu";
	for (int i = 0; i < path.length(); i++)
	{
		if(allowed.find(path[i])==string::npos)
			return true;
	}
	return false;
}
bool errorInRange(int row,int column,int x,int y,string path)
{
	for (int i = 0; i < path.length(); i++)
	{                                                     
		if(path[i]=='r'){x++;}
		if(path[i]=='l'){x--;}
		if(path[i]=='d'){y++;}
		if(path[i]=='u'){y--;}

		if(x>column || x<0 || y>row || y<0)
		{
			return true;
		}
	}
	return false;

}
bool errorVisitedTwice(string path)
{
	int x=0,y=0;
	vector<pair<int,int>> visitedCell;
	pair<int,int> cellCode;
	for (int i = 0; i < path.length(); i++)
	{
		if(path[i]=='r'){x++;}
		if(path[i]=='l'){x--;}
		if(path[i]=='d'){y--;}
		if(path[i]=='u'){y++;}

		cellCode=make_pair(x,y);


		for (int i = 0; i < visitedCell.size(); i++)
		{
			if(visitedCell[i]==cellCode)
				return true;
		}
		visitedCell.push_back(cellCode);

	}
	return false;
}
bool errorTooShort(string path){                        
	return path.length()<2;
}
bool errorPreviouslyVisited(string word)                  
{
	for (int i = 0; i < word.length(); i++)
	{
		if(word[i]=='_')
			return true;
	}
	return false;
}
bool errorLowerCaseChar(const vector<vector<char>>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			if(vec[i][j]<'a' || vec[i][j]>'z')
				return true;
		}
	}
	return false;
}
bool errorNotChar(string str)
{                                                 
	string temp;
	istringstream iss(str);
	while(iss>>temp)                      
		if(temp.length()!=1)
			return true;

	return false;
}



void print(const vector<vector<char>>& vec)	//NOEIER ==> Number of element in each row
{
	cout<<endl;
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			cout<<vec[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
bool is_Empty(const vector<vector<char>>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			if(vec[i][j]!='_')
				return false;
		}
	}
	return true;
}
bool search(const vector<vector<char>>& vec,string path,ifstream &wordIn,int y,int x,string& word)
{
	string obtained="";
	obtained+=vec[x][y];

	for (int i = 0; i < path.length(); i++)                        // we define the letters and their duty
	{
		if(path[i]=='r'){y++;}
		if(path[i]=='l'){y--;}
		if(path[i]=='d'){x++;}
		if(path[i]=='u'){x--;}

		obtained+=vec[x][y];
	}



	string line;
	bool found=false;
	while(getline(wordIn,line))
	{
		if((line==obtained))
			found=true;
	}

	wordIn.clear();
	wordIn.seekg(0);

	if (found)
	{
		word=obtained;
		return true;
	}
	else
	{
		if(errorPreviouslyVisited(obtained))
		{
			cout<<"Invalid path - cell visited previously"<<endl;
			return false;
		}
		cout<<"Invalid word - non-existent word \""<<obtained<<"\" "<<endl;
		return false;
	}

}
void eraseElements(vector<vector<char>>& vec,string path,int y,int x)               
{
	vec[x][y]='_';

	for (int i = 0; i < path.length(); i++)                      //if there is a word in dictionary we change the letters with '_'
	{
		if(path[i]=='r'){y++;}
		if(path[i]=='l'){y--;}
		if(path[i]=='d'){x++;}
		if(path[i]=='u'){x--;}

		vec[x][y]='_';
	}
}

bool getPath(vector<vector<char>>& vec,int x, int y, string &path)
{
	string allowed="lrdu";
	cout<<"Enter the path: ";
	cin>>path;
	                                                        //we get path from the user and check the errors.

	if(errorTooShort(path))
	{
		cout<<"Invalid path - path too short "<<endl;
		return false;
	}
	if(errorInLRDU(path))
	{
		cout<<"Invalid path - non-RLUD input "<<endl;
		return false;
	}

	if(errorVisitedTwice(path))
	{
		cout<<"Invalid path - cell visited twice "<<endl;
		return false;
	}

	if(errorInRange(vec[0].size(),vec.size(),x,y,path))
	{
		cout<<"Invalid path - out of range "<<endl;
		return false;
	}

	return true;
}
void scorePrint(string word,int &score)
{
	int len=word.length();
	cout<<"Word found: "<<word<<endl; 
	cout<<"Word length: "<<len<<endl;
	cout<<"Points gained: "<<len*len<<endl; 
	score+=len*len;
	cout<<"Current score: "<<score<<endl;

}

void getCoordinates(vector<vector<char>>& vec, ifstream &wordIn,int&score)
{
	int x,y;
	string path;
	cout<<"\nEnter the starting location for word (x, y): ";
	cin>>y>>x;
	if(x==-1 || y==-1)
	{
		cout<<"\nYou didn't completely solve the puzzle. \nYour final score is "<<score<<"." <<endl;
		return;
	}

	if(errorInCoordinates(vec,x,y))
	{
		cout<<"Invalid coordinate - out of range\n";
		print(vec);
		getCoordinates(vec,wordIn,score);
	}
	else{
		if(!getPath(vec,x,y,path))
		{
			print(vec);
			getCoordinates(vec,wordIn,score);
		}
		else{
			string word="";
			if(search(vec,path,wordIn,x,y,word))
			{
				eraseElements(vec,path,x,y);

				if(is_Empty(vec))
				{
					cout<<"Congratulations, you have solved the puzzle perfectly!\nYour final score is "<<score<<".\n";
					return;
				}

				scorePrint(word,score);
				print(vec);
				getCoordinates(vec,wordIn,score);


			}
			else{
				print(vec);
				getCoordinates(vec,wordIn,score);
			}
		}
	}
}


int main()
{
	vector<vector<char>> puzzle;
	ifstream inPuzzle,inWords;
	string puz_file,word_file;
	int score=0;

	///****************CHECK OF FILENAMES**************////
	do
	{
		cout<<"Please enter the name of the puzzle file: ";
		cin>>puz_file;
		inPuzzle.open(puz_file);

		if(inPuzzle.fail())
			cout<<"File could not be opened. \n";
	} while (!inPuzzle.is_open());



	//**********GET PUZZLE TO MATRIX**********///
	string line;

	bool stop=false;
	while (getline(inPuzzle,line))
	{
		if(errorNotChar(line))
		{
			cout<<"Invalid matrix - cell entry is not a char\n";
			stop=true;
		}
		vector<char> temp;
		char t;
		istringstream iss(line);
		while(iss >> t){
			temp.push_back(t);
		}
		puzzle.push_back(temp);
	}
	//**********GET PUZZLE TO MATRIX**********//

	if(!stop){
		if(errorInSquare(puzzle))
		{
			cout<<"Invalid matrix - inconsistent dimensions "<<endl;
		}
		else if(errorLowerCaseChar(puzzle)){
			cout<<"Invalid matrix - char not lowercase letter\n";
		}
		else{

			do
			{
				cout<<"Please enter the name of the word file: ";
				cin>>word_file;
				inWords.open(word_file);

				if(inWords.fail())
					cout<<"File could not be opened. \n";
			} while (!inWords.is_open());


			
			print(puzzle);
			getCoordinates(puzzle,inWords,score);
		}
	}
	system("pause");
	return 0;
}
