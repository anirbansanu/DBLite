//#ifndef ROW_H_INCLUDED
//#define ROW_H_INCLUDED
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "Tkns.hpp"
//#include "columns.cpp"

using namespace std;
class Row
{
    protected:
        int write(string db, string tableName, vector<string> data);
        vector<string> read(string db, string tableName);
        int update(string db, string tableName, vector<string> data);

    public:
        vector<vector<string>> readlines(string db, string tableName);
        vector<string> search(string db, string tableName, string data);
        int pushRow(string db, string tableName, vector<string> data);
        vector<string> readByLoc(string db, string tableName, int loc);
        

};
int Row::write(string db, string tableName, vector<string> data)
{
    int dataSize = data.size();
    fstream fio;
    string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbl";
    cout<<"\nFile name : "<<temp<<endl;
    fio.open(temp, ios::out | ios::in | ios::app);
    if(fio.is_open())
    {
        int i;
        

        for(i=0;i<dataSize;i++)
        {
            fio << data[i] << " ";
            cout<<"write func : "<<data[i]<<endl;
        }
        fio<<endl;
    }
    else
    {
        cerr << "in Row.H : File is Not Created";
        fio.close();
        return 0;
    }
    fio.close();
    return 1;
}
vector<string> Row::read(string db, string tableName)
{
    vector<string>data;
    string line;
    fstream fio;
    string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbl";
    fio.open(temp, ios::out | ios::in | ios::app);
    fio.seekg(0, ios::beg);
    //cout << "FILE NAME : " << this->f_path <<endl;
    if(fio.is_open())
    {
        // Read Colums from File
        getline(fio, line);
        Tkns tok;
        data = tok.split(line, " ");
        return data;
    }
    else
    {
        data.push_back("0");
        return data;
    }
}

int Row::update(string db, string tableName, vector<string> data)
{
    cout<<"\nRunning Update function"<<endl;
    string line;
    int dataSize = data.size();
    fstream fio;
    string filePath = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbtl";
    cout<<"\nFile name : "<<filePath<<endl;
    fio.open(filePath, ios::out | ios::in | ios::ate);
    fio.seekg(0, ios::beg);
    getline(fio, line);
    fio.seekg(0, ios::beg);
    for(int i=0;i<line.size();i++)
    {
        fio << " ";
    }
    fio.seekg(0, ios::beg);
    if(fio.is_open())
    {
        int i;
        for(i=0;i<dataSize;i++)
        {
            fio << data[i] << " ";
            cout<<"write func : "<<data[i]<<endl;
        }
    }
    else
    {
        cerr << "in ROW.HPP : File is Not Created";
        fio.close();
        return 0;
    }
    fio.close();
    return 1;
}

int Row::pushRow(string db, string tableName, vector<string> data)
{
    this->write(db,tableName,data);
    return 1;
}
vector<string> Row::readByLoc(string db, string tableName, int loc)
{
    vector<string>data;
    fstream fio;
    string filePath,line,delimiter,temp;
    Tkns tok;
    filePath = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbl";
    cout<<"\nFile name : "<<filePath<<endl;
    fio.open(filePath, ios::out | ios::in);
    fio.seekp(loc);
    if(fio.is_open())
    {
        // Read Colums from File
        getline(fio, line);
        Tkns tok;
        data = tok.split(line, " ");
        return data;
    }
    else
    {
        data.push_back("0");
        return data;
    }
}

vector<string> Row::search(string db, string tableName, string value)
{
    vector<string>data;
    if(!value.empty())
    {
        fstream fio;
        string filePath,line,delimiter,temp;
        Tkns tok;
        filePath = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbl";
        cout<<"\nFile name : "<<filePath<<endl;
        fio.open(filePath, ios::out | ios::in);
        fio.seekg(0, ios::beg);
        int i=0,j=0,pos;
        pos = fio.tellp();
        while(getline(fio, line) && temp != value)
        {
            //cout << line[j] << "\n";
            while(line[j]==value[j])
            {
                temp=temp+line[j];
                cout<<"temp search() data["<<j<<"] : "<<temp<<endl;
                j++;
            } 
            if(temp == value)
            {
                data = tok.split(line," ");
                break;
            }
            pos = fio.tellp();
            j=0;
        }
        data.push_back(to_string(pos));
        return data;
    }
    data.push_back("0");
    return data;
}
vector<vector<string>> Row::readlines(string db, string tableName)
{
    vector<vector<string>>data;
    Tkns tok;
    string line;
    fstream fio;
    string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbl";
    fio.open(temp, ios::out | ios::in | ios::app);
    fio.seekg(0, ios::beg);
    int pos = fio.tellg();
    cout<<"Tell : "<<pos<<" ";
    while(getline(fio, line)){  //read data from txt file and put it into string.
        cout<<"Tell : "<<pos<<" ";
        cout << line << "\n";
        pos = fio.tellg();
        
        //data[i] = tok.split(line," ");
    }
    return data;
}
int main()
{
    Row r;
    Tkns tok;

    //r.pushRow("school","students",tok.split("5 Ram vi C 78 B+ 8.8 8.6"," "));
    
    vector<string>data,temp;
    data=r.search("school","students","2");
    for(int i=0;i<data.size();i++)
    {
        cout<<" data : "<<data[i]<<endl;
    }
    
    temp=r.readByLoc("school","students",101);
    for(int i=0;i<temp.size();i++)
    {
        cout<<" temp : "<<temp[i]<<endl;
    }

    r.readlines("school","students");
    

}

//#endif //ROW_H_INCLUDED
