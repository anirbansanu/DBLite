#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED
#include<string>
#include<vector>
using namespace std;
class DB
{
    protected:
        string fileName;
        int rowsCount;
        int columnsCount;
        string lastId;
    int createDB(string dbName);
    int insertColumns();
    int insertRow();
    int insertRows();
    vector<string> fetchRow();
    vector<vector<string>> fetchRows();

};

#endif