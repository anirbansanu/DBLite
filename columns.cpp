//#ifndef COLUMNS_HPP_INCLUDED
//#define COLUMNS_HPP_INCLUDED
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
#include "Tkns.hpp"

using namespace std;

class Columns
{
    protected:
        int write(string db, string tableName, vector<string> data)
        {
            int dataSize = data.size();
            fstream fio;
            string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbtl";
            cout<<"\nFile name : "<<temp<<endl;
            fio.open(temp, ios::out | ios::in | ios::ate);
            fio.seekg(0, ios::beg);
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
                cerr << "in Columns.hpp : File is Not Created";
                fio.close();
                return 0;
            }
            fio.close();
            return 1;
        
        }
        int update(string db, string tableName, vector<string> data)
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
                cerr << "in TABLE.H : File is Not Created";
                fio.close();
                return 0;
            }
            fio.close();
            return 1;
        
        }
    public:
        //1st argu is tableName and 2nd is columns Name>>
        int pushColumns(string db, string tableName, vector<string> columns, vector<string>types, string action)
        {
            vector<string> data;
            if(tableName.empty() && db.empty())
            {
                return 0;     // return 0 if table and DB name is not provided
            }
            
            for(int i=0; i<columns.size();i++)
            {
                data.push_back(columns[i]);
            }

            data.push_back("{");
            for(int i=0; i<types.size();i++)
            {
                data.push_back(types[i]);
            }
            data.push_back("}");
            
            for(int i=0; i<data.size();i++)
            {
                cout << data[i] << " ";
            }
            if(action=="update" || action=="Update" || action=="UPDATE")
                this->update(db, tableName, data);
            else if(action=="write" || action=="Write" || action=="WRITE")
                this->write(db, tableName, data);
            return 1;

        }
        vector<string> fetchColumns(string db, string tableName)
        {
            string line;
            fstream fio;
            string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbtl";
            fio.open(temp, ios::out | ios::in | ios::app);
            fio.seekg(0, ios::beg);
            vector<string>data;
            vector<string>columns;
            //cout << "FILE NAME : " << this->f_path <<endl;
            if(fio.is_open())
            {
                // Read Colums from File
                getline(fio, line);
                Tkns tok;
                data = tok.split(line,"","{"," ");
                for(int i=0;i<data.size();i++)
                {
                    if(data[i] != "{")
                    {
                        columns.push_back(data[i]);
                    }
                    else
                    {
                        
                    }
                    
                    //cout<<"columns " << i << " : "<<columns[i]<<endl;
                }

                return columns;
            }
            else
            {
                cerr << "Invalid Path is in Columns.h";
            }
            fio.close();
            return columns;
        }
        vector<string> columnsTypes(string db, string tableName)
        {
            vector<string>types;
            string line;
            fstream fio;
            string temp = ".\\"+db+"\\"+tableName+"\\"+tableName+".dbtl";
            fio.open(temp, ios::out | ios::in | ios::app);
            fio.seekg(0, ios::beg);
            //cout << "FILE NAME : " << this->f_path <<endl;
            if(fio.is_open())
            {
                // Read Colums from File
                getline(fio, line);
                Tkns tok;
                types = tok.split(line, "{", "}", " ");
                types.erase(types.begin());
                types.erase(types.end());
                
            }
            else
            {
                cerr << "Invalid Path is in Columns.hpp";
                
            }
            
            return types;
        }
        int renameColumn(string db, string tableName, string oldColumnName, string newColumnName, string oldType, string newType)
        {
            vector<string>columns;
            vector<string>types;
            columns = this->fetchColumns(db,tableName);
            types = this->columnsTypes(db,tableName);
            unsigned i;
            cout<<"Call renameColumn()"<<endl;
            for(i=0;i<columns.size();i++)
            {
                if(columns[i]==oldColumnName)
                {
                    columns[i]=newColumnName;
                    if(types[i]==oldType)
                        types[i]=newType;

                    this->pushColumns(db, tableName, columns, types, "Update");
                    return 1;
                }
                
                cout<<"columns["<<i<<"] : "<<columns[i];
                cout<<" types["<<i<<"] : "<<types[i]<<endl;

            }
            if(i==columns.size())
            {
                cerr<<"Error : Column Not found <Columns.renameColumn()>";
            }
            return 0;
        }
        int addColumns(string db, string tableName, vector<string> columns, vector<string>types)
        {
            vector<string>existsColumns;
            vector<string>existsTypes;
            existsColumns = this->fetchColumns(db,tableName);
            existsTypes = this->columnsTypes(db,tableName);
            unsigned i;
            cout<<"Call addColumns()"<<endl;
            for(i=0;i<columns.size();i++)
            {
                if(columns[i]!="")
                {
                    existsColumns.push_back(columns[i]);
                    if(types[i]!="")
                        existsTypes.push_back(types[i]);

                }
                
                cout<<"existsColumns["<<i<<"] : "<<existsColumns[i];
                cout<<" existsTypes["<<i<<"] : "<<existsTypes[i]<<endl;

            }
            if(i==columns.size())
            {
                this->pushColumns(db, tableName, existsColumns, existsTypes, "Update");
                
                return 1;
            }
            else
            {
                cerr<<"Error <Columns.addColumns()> : Failed To Add New Columns ";
            }
            return 0;
        }
};

int main()
{
    Tkns tok;
    Columns t;
    
    //t.write("sample.dbtl", tok.split("Table_Name Columns { ID Name Class Section } Type { Int String String String }", " "));

    //t.createTable("school", "students", tok.split("ID Name Class Section"," "), tok.split("Int String String String"," ") );
    vector<string>data;
    data = t.fetchColumns("school", "students");

    for(int i=0;i<data.size();i++)
        cout<<i<<" "+data[i]<<endl;


    vector<string>dataTypes;
    dataTypes = t.columnsTypes("school", "students");

    for(int i=0;i<dataTypes.size();i++)
        cout<<i<<" "+dataTypes[i]<<endl;

 
    int checked = t.renameColumn("school", "students", "Section", "StuSec", "String", "Int");

    if(checked)
    {
        cout<<"ReNamed Successfull";
    }
    vector<string>columns{"Grade","CGPA","SGPA"};
    vector<string>types{"String","String","String"};
    t.addColumns("school", "students", columns, types);
    int n;
    cin>>n;
    return 0;
}
//#endif // COLUMNS_HPP_INCLUDED