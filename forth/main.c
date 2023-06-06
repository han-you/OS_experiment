#include<iostream>
using namespace std;
#include<vector>
int n,m;
vector<int>ans;
void help(vector<int>&rec,vector<bool>&Finish,vector<vector<int>>&Need,vector<vector<int>>&Allocation,vector<int>Available,int pos)
{
	if(pos==n)
	{
		ans=rec;
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(Finish[i]==true)
			continue;
		bool flag=true;
		for(int j=0;j<m;j++)
		{
			if(Available[j]<Need[i][j])
			{
			flag=false;
			break;
			}
		}
		if(flag)
		{
		        vector<int>workaddallocation(m);
			for(int k=0;k<m;k++)
			{
			workaddallocation[k]=Available[k]+Allocation[i][k];
			}
			Finish[i]=true;
		        rec.push_back(i);
			help(rec,Finish,Need,Allocation,workaddallocation,pos+1);
			rec.pop_back();
			Finish[i]=false;
		}
	}
}
void printinit(vector<vector<int>>&Max,vector<vector<int>>Allocation,vector<vector<int>>Need,vector<int>&Available)
{
	vector<string>Process={"P0","P1","P2","P3","P4"};
	int count=0;
	cout<<"Init states"<<endl;
        cout<<"Process      "<<"Max         "<<"Allocation   "<<"Need      "<<"Available      "<<endl;
	for(int pos=0;pos<Allocation.size();pos++)
	{
		cout<<Process[pos]<<"           ";
		for(int i=0;i<Max[pos].size();i++)
		{
			cout<<Max[pos][i]<<" ";
		}
                cout<<"    ";
		for(int i=0;i<Allocation[pos].size();i++)
		{
			cout<<Allocation[pos][i]<<" ";
		}
		cout<<"     ";
		for(int i=0;i<Need[pos].size();i++)
		{
			cout<<Need[pos][i]<<" ";
		}
		cout<<"  ";
		if(count==0)
		{
			for(int i=0;i<Available.size();i++)
			{
				cout<<Available[i]<<" ";
			}
		}
		cout<<endl;
		count++;
	}
}
		

void print(vector<int>&rec,vector<int>&work,vector<vector<int>>&Need,vector<vector<int>>&Allocation)
{
	cout<<"safe series:"<<endl;
	vector<string>Process={"P0","P1","P2","P3","P4"};
	cout<<"Process   "<<"Work      "<<"Need      "<<"Allocation    "<<"Work+Alloc    "<<"Finish"<<endl;
		for(auto pos:rec)
                {
			cout<<Process[pos]<<"        ";
			for(int i=0;i<work.size();i++)
			{
				cout<<work[i]<<" ";
				work[i]+=Allocation[pos][i];
			}
			cout<<"  ";
			for(int i=0;i<Need[0].size();i++)
			{
				cout<<Need[pos][i]<<" ";
			}
			cout<<"  ";
			for(int i=0;i<Allocation[0].size();i++)
	        	{
				cout<<Allocation[pos][i]<<" ";
			}
			cout<<"      ";
			for(int i=0;i<work.size();i++)
			{
				cout<<work[i]<<" ";
	        	}
			cout<<"      ";
			cout<<"true";
			cout<<endl;
		}
}
int main()
{
	cin>>n>>m;
	vector<bool>Finish(n);
	vector<int>rec;
	for(int i=0;i<n;i++)
	{
		Finish[i]=false;
	}
	vector<vector<int>>Max(n,vector<int>(m));
	vector<vector<int>>Allocation(n,vector<int>(m));
	vector<int>Available(m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>Max[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			cin>>Allocation[i][j];
		}
	}
	for(int i=0;i<m;i++)
	{
		cin>>Available[i];
	}
	vector<vector<int>>Need(n,vector<int>(m));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			Need[i][j]=Max[i][j]-Allocation[i][j];
		}
	}
	printinit(Max,Allocation,Need,Available);
	help(rec,Finish,Need,Allocation,Available,0);
	print(ans,Available,Need,Allocation);	
}
