#include<fstream>
#include<iostream>
#include "Dictionary.h"
#include "Trie.h"
using namespace std;

string filename; //stores filename
  void readFileData(Trie t) //reads text from a file and writes it to the AVL tree
{
	string word,pos, meaning;
	fstream fin;
	cout << "\e[46mEnter the filename\x1b[0m "; 
	cin.ignore();
  cin >> filename;
	fin.open(filename);
  cout << "\e[0;32mFile reading succesful.\x1b[0m\n";
  while( getline(fin,word,',') )  //write into file name
  {
    getline(fin,pos,',');
    getline(fin,meaning,'\n');
    Dictionary dict = Dictionary(word,pos,meaning);
    t.insert(dict);
  }
  

	fin.close();
}

void writeToFile(Trie t) //write the linked list to a text file
{
  // string word, pos, meaning;
  fstream dictFile; //create fstream object for the file
  cout << "\e[46mEnter the filename\x1b[0m "; 
	cin.ignore();
  cin >> filename;
  dictFile.open(filename, std::ios::app); //create/open a text file in append mode. new information is always added to the end
  dictFile << "Word,Part of Speech,Meaning" << endl;
  // traverse the trie and write to file
  writeToFileUtil(t.root, dictFile);
  cout << "\e[0;32mFile writing succesful.\x1b[0m\n";
  dictFile.close();
}



void mainMenu() //menu function
{
  // Logo with * in Start with text "Dictionary"
  cout << "\e[1;35m********************************************************************************************************************************************\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @ @ @ @      @ @ @ @ @      @ @ @ @    @ @ @ @ @    @ @ @ @ @      @ @ @      @         @    @ @ @      @ @ @ @      @       @   \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @       @        @        @                @            @        @       @    @ @       @  @       @    @       @      @   @     \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @       @        @        @                @            @        @       @    @   @     @  @       @    @       @        @       \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @       @        @        @                @            @        @       @    @     @   @  @ @ @ @ @    @ @ @ @          @       \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @       @        @        @                @            @        @       @    @       @ @  @       @    @       @        @       \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @       @        @        @                @            @          @ @ @      @         @  @       @    @       @        @       \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m****\e[0;37m" <<  "\e[1;33m   @ @ @ @      @ @ @ @ @      @ @ @ @        @        @ @ @ @ @                              @       @    @       @        @       \x1b[0m"  <<  "\e[1;35m****\e[0;37m" << endl;
  cout << "\e[1;35m********************************************************************************************************************************************\e[0;37m" << endl;  
  Trie trie = Trie();
  Trie favorities = Trie();
  string word, pos, meaning; //stores the word and meaning
  char choice;  //stores user choice for the actions
  while (choice != 's') //while loop until 's' is entered
  {
    cout << "\e[1;35m\nInput 's' to terminate the program anytime.\e[0;37m" << endl;
    cout << "\n\x1b[36mPlease select an action: " << endl << endl;
    cout << "\t1. Read file data" << endl;
    cout << "\t2. Write to file" << endl;
    cout << "\t3. Search a word" << endl;
    cout << "\t4. Print my favorities" << endl;
    cout << "\t5. Filter By Prefix" << endl;
    cout << "\t6. Delete a word" << endl;

    cout << "\x1b[0m"; cin >> choice; cout << endl;
    switch(choice)  //switch statement to check user input and calling respective functions
    {

      case('1'):
      {
        readFileData(trie);
      }; break;

      case('2'):
      {
        writeToFile(trie);
      }; break;

      case('3'):
      {
        cout << "\e[46mEnter the word\x1b[0m ";
        cin.ignore();
        cin >> word;
        Dictionary dict = trie.search(word);
        if(dict.word == "")
        {
          cout << "\e[0;31m\nWord not found!\n\x1b[0m\n";
        }
        else
        {
          cout << "\e[0;32m\nWord found!\n\x1b[0m\n";
          cout << "\e[1;33mWord: \x1b[0m" << dict.word << endl;
          cout << "\e[1;33mPart of Speech: \x1b[0m" << dict.pos << endl;
          cout << "\e[1;33mMeaning: \x1b[0m" << dict.meaning << endl;
          cout<< "\e[0;32m\nDo you want to add the word to favorities? y/n \x1b[0m";
          string fav;
          cin.ignore();
          cin>>fav;
          if (fav=="y")
            favorities.insert(dict);
        }
      }; break;

      case('4'):
      {
        string auth;
        do
        {
          cout << "\e[1;33mFavorities: \n\x1b[0m ";
          favorities.display(favorities.root,"");
          cout << "\e[46m Do you want to remove any word from favorities.\nIf yes Enter the word! Enter -1 to exit: \x1b[0m ";
          cin.ignore();
          cin >> auth;
          if (auth!="-1"){
            favorities.deleteWord(auth);
            cout<<"\e[0;32mWord deleted succesfully!\x1b[0m";
          }
        } while (auth!="-1");
        
        
      }; break;

      case('5'):
      {
        cout << "\e[46mEnter the Prefix\x1b[0m ";
        cin.ignore();
        cin >> word;
        Trie t = filterWords(trie, word);
        cout<<"\e[0;32mFiltered the list succesfully!\n\nDo you want to write it in a file? y/n \x1b[0m\n";
        string write;
        cin >> write;
        if(write == "y")
        {
          writeToFile(t);
        }

      }; break;

      case('6'):
      {
        trie.display(trie.root,"");
        string s;
        cin>>s;
        trie.deleteWord(s);
      }

      case('s'):
      {
        cout << "\e[1;33mProgram terminated." << endl;
      }; break;

      default:
        cout << "\x1b[31mInvalid action selected!\x1b[37m" << endl;
    }
  }
}