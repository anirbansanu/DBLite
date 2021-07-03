#ifndef TKNS_HPP_INCLUDED
#define TKNS_HPP_INCLUDED
#include<string>
#include<vector>

using namespace std;
class Tkns
{
    public:

        int length;
    public:
        vector<string> split(string str, string delimiter)
        {
            vector<string> tokens;
            int i=0,j=0;
            int strSize;
            string temp;
            strSize = str.size();
            while(i<strSize)
            {
                if(str[i]!=delimiter[0] && i<strSize)
                {
                    while(str[i]!=delimiter[0] && i<strSize)
                    {
                        temp = temp + str[i];
                        i++;
                    }
                    tokens.push_back(temp);
                    temp="";
                }
                else
                {                
                    i++;
                }
                
            }
            length = tokens.size();
            return tokens;
        }
        vector<string> split(string str, string startElement, string endElement, string delimiter)
        {
            string finalString;
            int startIndex=str.find(startElement);
            int endIndex = str.find(endElement);

            finalString.assign(str,startIndex,endIndex);

            vector<string> tokens;
            string temp;
            
            int i=startIndex;
            while(i<=endIndex)
            {
                if(str[i]!=delimiter[0] && i<=endIndex)
                {
                    while(str[i]!=delimiter[0] && i<=endIndex)
                    {
                        //cout<<str[i];
                        temp = temp + str[i];
                        i++;
                        
                    }
                   
                    tokens.push_back(temp);
                    temp="";
                }
                else
                {                
                    i++;
                }
                
            }
            //cout<<"split the string by start and end : "<<finalString<<endl;
            //cout<<"str : "<<str<<endl;
            //cout<<"startIndex : "<<startIndex<<endl;
            //cout<<"endIndex : "<<endIndex<<endl;
            
            
            return tokens;//this->split(finalString, delimiter);
        }
        /*void display()
        {
            int i=0;
            while(i < this->length)
            {
                cout << endl << this->tokens[i] << endl;
                i++;
            }
            
            cout<<"\n"<<this->length;
        }*/
};


#endif // TKNS_H_INCLUDED
