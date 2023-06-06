#include"sfs_api.h"
#include<string>
#include<vector>
#include<iostream>
#include"sfs_api.c"
using namespace std;
vector<string> split(string cmd, char sp)
{
	vector<string>ans;
	int start = 0;
	int judge = false;
	for (int i = 0; i < cmd.size(); i++)
	{
		if (!judge && cmd[i] != sp)
		{
			start = i;
			judge = true;
		}
		else if (judge && cmd[i] == sp)
		{
			ans.push_back(cmd.substr(start, i - start));
			judge = false;
		}
	}
	if (cmd[cmd.size() - 1] != sp)
	{
		ans.push_back(cmd.substr(start, cmd.size() - start + 1));
	}
	return ans;
}
char* string_to_str(string x)
{
	char* tmp = new char[x.size()+1];
	for (int i = 0; i < x.size(); i++)
	{
		tmp[i] = x[i];
	}
	tmp[x.size()] = '\0';
	return tmp;
}
int dealtype(string cmd)
{
	vector<string>tmp = split(cmd, ' ');
	if (tmp.size() == 0)
	{
		return -1;
	}
	if (tmp[0] == "ls")
	{
		if (tmp.size() == 1)
		{
			return 1;
		}
		else
		{
			cout << "to many argument" << endl;
			return -1;
		}
	}
	else if (tmp[0] == "rm")
	{
		if (tmp.size() != 2)
		{
			cout << "to many argument" << endl;
			return -1;
		}
		else return 2;
	}
	else if (tmp[0] == "echo")
	{
		if (tmp.size() < 3)
		{
			cout << "to few argument" << endl;
			return -1;
		}
		else if (tmp.size() > 3)
		{
			cout << "to many argument" << endl;
			return -1;
		}
		else return 4;

	}
	else if (tmp[0] == "touch")
	{
		if (tmp.size() != 2&&tmp.size()!=4)
        {
            cout<<"no such commond"<<endl;
            return -1;
        }
		else return 3;
	}
	else if (tmp[0] == "quit")
	{
		if (tmp.size() != 1)
		{
			cout << "to many argument" << endl;
			return -1;
		}
		else return 0;
	}
	else if (tmp[0] == "cat")
	{
		if (tmp.size() > 2)
		{
			cout << "to many argument" << endl;
			return -1;
		}
		else if (tmp.size() == 1)
		{
			cout << "to few argument" << endl;
			return -1;
		}
		else
        {
            if(getIndexOfFileInDirectory(string_to_str(tmp[1]),&root)==-1)
            {

                cout<<"no such file"<<endl;
                return -1;
            }
            else return 5;
        }
	}
	else
	{
		cout << "no such commond" << endl;
		return -1;
	}
}
//template <class type>
//void print_vector(vector<type>V)
//{
//	for (int i = 0; i < V.size(); i++)
//	{
//		cout << V[i] << ' ';
//	}
//};
//void test_split()
//{
//	string cmd = "ls cuhduvur ";
//	vector<int>ans = split(cmd, ' ');
//	print_vector(ans);
//	stirng cmd = "ls jnhvberh";
//	ans = split(cmd);
//	print_vector(ans);
//}
//ls 1
//rm 2
//touch 3
//echo  4
//quit 0
//cat 5
void deal(int type,string cmd)
{
	vector<string>tmp = split(cmd,' ');
	if (type == 0)
	{
		sfs_system_close();
		exit(0);
	}
	else if (type == 1)
	{
		sfs_ls();
	}
	else if (type == 2)
	{
		int fileID = getIndexOfFileInDirectory(string_to_str(tmp[1]),&root);
		if (fileID == -1)
		{
			cout << "file " <<tmp[1]<< " not exits" << endl;
		}
		else
        {
            if(root.table[fileID].passwordexit)
            {
                cout<<"enter the password"<<endl;
                string s;
                getline(cin,s);
                if(strlen(root.table[fileID].password)!=strlen(string_to_str(s))||strcmp(root.table[fileID].password,string_to_str(s))!=0)
                {
                    cout<<"password error"<<endl;
                    return;
                }
            }
            sfs_delete(fileID);
        }
	}
	else if (type == 3)
	{
        if(tmp.size()==2)
        {
            int fileID=sfs_open(string_to_str(tmp[1]));
            root.table[fileID].passwordexit=false;
            sfs_close(fileID);
        }
        else
        {
            if(tmp[2]!="-l")
            {
                cout<<"no such commond"<<endl;
            }
            else
            {
                int fileID=sfs_open(string_to_str(tmp[1]));
                for(int i=0;i<tmp[3].size();i++)
                {
                    root.table[fileID].password[i]=tmp[3][i];
                }
                root.table[fileID].password[tmp[3].size()]='\0';
                root.table[fileID].passwordexit=true;
                sfs_close(fileID);
            }
        }
	}
	else if (type == 4)
	{
        int fileid=10;
        fileid=getIndexOfFileInDirectory(string_to_str(tmp[1]),&root);
        if(fileid==-1)
		fileid = sfs_open(string_to_str(tmp[1]));
        else
        {
            if(root.table[fileid].passwordexit)
            {
                cout<<"enter the password"<<endl;
                string s;
                getline(cin,s);
               if(strlen(root.table[fileid].password)!=strlen(string_to_str(s))||strcmp(root.table[fileid].password,string_to_str(s))!=0)
               {
                   cout<<"password error"<<endl;
                   return;
               }
            
            }
            sfs_open(string_to_str(tmp[1]));
        }
		sfs_write(fileid,string_to_str(tmp[2]),tmp[2].size());
		sfs_close(fileid);
	}
	else if (type == 5)
	{      int fileID=getIndexOfFileInDirectory(string_to_str(tmp[1]),&root);
           if(root.table[fileID].passwordexit)
           {
               cout<<"enter the password"<<endl;
               string s;
               getline(cin,s);
               if(strlen(root.table[fileID].password)!=strlen(string_to_str(s))||strcmp(root.table[fileID].password,string_to_str(s))!=0)
               {
                   cout<<"password error"<<endl;
                   return;
               }
           }
            int FileId=sfs_open(string_to_str(tmp[1]));
            int length=root.table[FileId].size;
            char*buf=new char[length];
            int x=sfs_read(FileId,buf,length);
            for(int i=0;i<length;i++)
            {
                cout<<buf[i];
            }
            cout<<endl;
            sfs_close(FileId);
	}
    return;
}
int main()
{
	sfs_system_init();
	string cmd = "";
	while (1)
	{
		getline(cin, cmd);
		int dtype = -1;
        dtype=dealtype(cmd);
		while (dtype==-1)
		{
			getline(cin, cmd);
            dtype=dealtype(cmd);
		}
		deal(dtype,cmd);
	}
	return 0;
}
