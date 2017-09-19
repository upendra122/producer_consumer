#include<iostream>
#include<vector>
#include<unistd.h>
#include<pthread.h>
using namespace std;
pthread_mutex_t mutex,mutex2,mutex3;
int SIZE =6;
int bucket,i;
vector <string> process;
void *producer(void *vargp)
{
    int flag=0;
    pthread_mutex_lock(&mutex3);//to ensure no two producer get inside cs at same time
    if(bucket!=SIZE)
    {
        pthread_mutex_lock(&mutex); //for ensuring that if bucket size is not full than consumer cant go in cs
        flag=1;
    }
     while(bucket==SIZE)
            {
                cout<<"producer  is busy waiting\n";
            }
            cout<<"\nItem produced by  producer"<<endl;
            bucket++;
            if(flag==1)
                pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex3);
}
void *consumer(void *vargp)
{

    pthread_mutex_lock(&mutex2);//to ensure no two consumer get inside at same time;
    if(bucket>0)
    pthread_mutex_lock(&mutex);
     while(bucket==0)
            {
                cout<<"consumer is waiting  is busy waiting\n";
            }
            cout<<"Item consumed by  consumer\n"<<endl;
            bucket--;
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex2);
}
int main()
{
	int no_process,j,n,flag1=0,flag2=0;
	bucket=0;
	pthread_t tid1,tid2;
	pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&mutex2,NULL);
	pthread_mutex_init(&mutex3,NULL);
	cout<<"Enter the number of process::";
	cin>>no_process;
	cout<<" Enter the process in the order you want (ex: for producer give p1 and for consumer give c1 p and c before no is strictly required)"<<endl;
	for(j=0;j<no_process;j++)
		{
		    string temp;
            cin>>temp;
            process.push_back(temp);
		}
		i=0;

    while(i<no_process)
    {
        cout<<flag1<<endl;
        if((process[i][0]=='p'||process[i][0]=='P'))
        {
            pthread_create(&tid1,NULL,producer,NULL);
            flag1=1;

        }
        else if((process[i][0]=='c'||process[i][0]=='C'))
        {
            pthread_create(&tid2,NULL,consumer,NULL);
            flag2=1;
            cout<<"f"<<endl;
        }
        i++;

    }
if(flag1==1)
pthread_join(tid1, NULL);
if(flag2==1)
pthread_join(tid2, NULL);
pthread_mutex_destroy(&mutex);

pthread_mutex_destroy(&mutex2);

pthread_mutex_destroy(&mutex3);

return 0;
}
