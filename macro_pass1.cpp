#include<bits/stdc++.h>
using namespace std;

class macro{

    vector<tuple<string,int,int,int,int>>MNT;
    vector<vector<string>>PNTAB;
    vector<vector<string>>MDT;
    vector<tuple<string,string>>KPTAB;
    ifstream ipFile;
    vector<vector<string>>Tokens;
    public:
        macro(){
            ipFile.open("macro_input_2.txt",ios::in);
            getTokens();
        }
        void getTokens(){
            string buffer,word;

            while(!ipFile.eof()){
                getline(ipFile,buffer);
                stringstream ss(buffer);
                vector<string>temp;
                while(ss>>word){
                    if(word.substr(0,1) !=",")
                      temp.push_back(word);
                }
                Tokens.push_back(temp);
            }
        }

        void display(){
            cout<<"\n------TOKEN------\n";
            for(int i=0;i<Tokens.size();i++){
                for(int j=0;j<Tokens[i].size();j++)
                    cout<<Tokens[i][j]<<" " ;
                cout<<endl;
            }
             cout<<"\n---------------\n";
              cout<<"\n------MDT------\n";
            for(int i=0;i<MDT.size();i++){
                for(int j=0;j<MDT[i].size();j++)
                    cout<<MDT[i][j] <<" ";
                cout<<endl;
            }

            cout<<"\n---------------\n";
             cout<<"\n------PNTAB------\n";
            for(int i=0;i<PNTAB.size();i++){
                for(int j=0;j<PNTAB[i].size();j++)
                    cout<<PNTAB[i][j]<<" " ;
                cout<<endl;
            }
            cout<<"\n---------------\n";

        cout<<"\n------MNT------\n";
        cout<<"Name\t#PP\t#KP\t#KDTP\tMDTP\n";
            for(int i=0;i<MNT.size();i++){
                cout<<get<0>(MNT[i])<<"\t";
                cout<<get<1>(MNT[i])<<"\t";
                cout<<get<2>(MNT[i])<<"\t";
                cout<<get<3>(MNT[i])<<"\t";
                cout<<get<4>(MNT[i])<<"\t";
                cout<<endl;
            }
                     cout<<"\n---------------\n";

         cout<<"\n------KPTAB------\n";
         cout<<"KW\tVALUE"<<endl;
            for(int i=0;i<KPTAB.size();i++){
                cout<<get<0>(KPTAB[i])<<"\t";
                cout<<get<1>(KPTAB[i])<<"\n";
            }
                           cout<<"\n---------------\n";
 
       }

       int searchMNT(string mName){
        for(int i=0;i<MNT.size();i++){
            if(get<0>(MNT[i])==mName)
                return i;
        }
        return -1;
       }

       int deal(int index ,string parameter){
            for(int i=0;i<PNTAB[index].size();i++){
                if(PNTAB[index][i]==parameter)
                return i;
            }
            return -1;
       }

       void saveTables(){
        ofstream MNTFile,MDTFile,PNTABFile,KPTABFile;
        MNTFile.open("MNTFile.txt",ios::out);
        MDTFile.open("MDTFile.txt",ios::out);
        PNTABFile.open("PNTABFile.txt",ios::out);
        KPTABFile.open("KPTABFile.txt",ios::out);

       
        MDTFile<<"------MDT------\n";
        for(int i=0;i<MDT.size();i++){
            for(int j=0;j<MDT[i].size();j++)
                MDTFile<<MDT[i][j] <<" ";
            MDTFile<<endl;
        }

        PNTABFile<<"------PNTAB------\n";
        for(int i=0;i<PNTAB.size();i++){
            for(int j=0;j<PNTAB[i].size();j++)
                PNTABFile<<PNTAB[i][j]<<" " ;
            PNTABFile<<endl;
        }

        MNTFile<<"Name\t#PP\t#KP\t#KDTP\tMDTP\n";
        for(int i=0;i<MNT.size();i++){
            MNTFile<<get<0>(MNT[i])<<"\t";
            MNTFile<<get<1>(MNT[i])<<"\t";
            MNTFile<<get<2>(MNT[i])<<"\t";
            MNTFile<<get<3>(MNT[i])<<"\t";
            MNTFile<<get<4>(MNT[i])<<"\t";
            MNTFile<<endl;
        }

        KPTABFile<<"KEY\tVALUE"<<endl;
        for(int i=0;i<KPTAB.size();i++){
            KPTABFile<<get<0>(KPTAB[i])<<"\t";
            KPTABFile<<get<1>(KPTAB[i])<<"\n";
        }
        cout<<"\n---------------\n";
       }

       int storeDefinition(int lineNum)
       {
            string name=Tokens[lineNum+1][0];
            int KP,PP,MDTP,KDTP;
            KP=PP=0;
            MDTP=MDT.size();
            KDTP=KPTAB.size();
            vector<string>temp;
            for(int i=1;i<Tokens[lineNum+1].size();i++){
                if(Tokens[lineNum+1][i].find("=")!=string::npos){
                    //KP
                    KP++;
                    string key=Tokens[lineNum+1][i].substr(0,Tokens[lineNum+1][i].find("="));
                    string value=Tokens[lineNum+1][i].substr(Tokens[lineNum+1][i].find("=")+1 , Tokens[lineNum+1][i].size());
                    if(value=="")
                        value="----";
                    KPTAB.push_back(make_tuple(key,value));
                    temp.push_back(key);
                }
                else{
                    //PP
                    cout<<"-P->"<<Tokens[lineNum+1][i];
                    PP++;
                    temp.push_back(Tokens[lineNum+1][i]);
                    
                }
            }
            PNTAB.push_back(temp);
            temp={};
            string word;
            int i;
            for( i=lineNum+2;i<Tokens.size();i++){
                cout<<i<<endl;
                if(Tokens[i][0]=="MEND")
                    break;
                for( int j=0;j<Tokens[i].size();j++){
                    int index=deal(PNTAB.size()-1,Tokens[i][j]);
                    if(index!=-1){
                        word="(P,"+to_string(index)+")";
                    }
                    else
                        word=Tokens[i][j];
                    temp.push_back(word);
                }
                MDT.push_back(temp);
                temp={};
            }
            MDT.push_back({"MEND"});
            MNT.push_back(make_tuple(name,PP,KP,KDTP,MDTP));
            cout<<"Lngth:"<<i<<endl;
            return i;

       }
        void pass1(){
            for(int i=0;i<Tokens.size();i++){
                if(Tokens[i][0]=="MACRO")
                    i=storeDefinition(i);
            }
            saveTables();
        }



};
int main(){
    macro obj;
    obj.display();
   obj. pass1();
    obj.display();
return 0;
}