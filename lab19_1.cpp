#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream source;
    source.open(filename.c_str());
    string x ;
    while(getline(source,x)){
        char format[] = "%[^:]: %d %d %d" ;
        char n[100] ;
        int g1 ;
        int g2 ;
        int g3 ;
        int sumscore ;
        
        sscanf(x.c_str(),format,n,&g1,&g2,&g3);
        sumscore = g1 + g2 + g3 ;
        char gradesA = score2grade(sumscore) ;
        string cn = n ;
        names.push_back(cn) ;
        scores.push_back(sumscore) ;
        grades.push_back(gradesA) ;
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string x1 ;
    getline(cin,x1);
    int start = 0 ;
    int end = x1.find_first_of(" ");
    command = x1.substr(start,end-start) ;
    start = end + 1 ;
    end = x1.find_first_of(" ",start);
    key = x1.substr(start);
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------"<< endl ;
    for(unsigned int i = 0 ; i < names.size() ;i++ ){
        if (toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl ;   
            cout << names[i] << "'s grade = " << grades[i] << endl;     
            cout << "---------------------------------"<< endl; 
            return ; 
        }
    }
    cout << "Cannot found."<< endl ;
    cout << "---------------------------------"<< endl ;
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------"<< endl ;
    for(unsigned int i = 0 ; i < grades.size() ;i++ ){
        if (grades[i] == key.c_str()[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl ;

        }
    }
    cout << "---------------------------------"<< endl ;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
