#include<iostream>
 #include<stdio.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
using namespace std;
 
pthread_mutex_t mutex, wrt; 
int s, rcount = 0; 
 
void *writer(void *arg){
 
        pthread_mutex_lock(&wrt); 
        int n = rand() % 10; 
        int d = ((int)arg); 
        cout<< "W Wait for Random time between 0ns and 10ns"<<endl; 
        sleep(n); 
        cout<<"Enter the number of time W want to write"<<endl; 
        int t; 
        cin>>t; 
        cout<<"Now W is writing... i.e. ADDING..."<<endl; 
        int j; 
        for(j=0; j<t; j++){ 
                cout<<"Enter the INTEGER value to write:"<<endl<< (j+1)<<endl; 
                int u; 
                cin>>u; 
                s = s + u; 
        } 
        cout<<"UPDATED value of Shared variable ="<<endl<<s; 
       cout<<endl; 
        pthread_mutex_unlock(&wrt); 
} 
 
void *reader(void *arg){ 
        //Entry Part 
        pthread_mutex_lock(&mutex); 
        rcount++; 
        if(rcount==1){ 
                pthread_mutex_lock(&wrt);//No writer should come 
        } 
        pthread_mutex_unlock(&mutex);//so next reader can come 
        //Exit Part 
        int n = rand() % 10; 
        int d; 
        cout<<"R  wait for Random time between 0ns and 10ns ..="<<endl<<d, n; 
        sleep(n); 
        cout<<"Enter the number of time R  want to read:"<<endl<<d<<endl; 
        int t; 
        cin>>t; 
        cout<<"Now R is reading...."<<endl<<d<<endl; 
        int j; 
        for(j=0; j<t; j++){ 
                cout<<"R  read the shared value ="<<endl<< d<<s; 
        } 
        cout<<"Number of Readers present ="<<endl<<rcount<<endl; 
        pthread_mutex_lock(&mutex); 
        rcount--; 
        if(rcount==0){//Now writer can come if they want 
                pthread_mutex_unlock(&wrt); 
        } 
        pthread_mutex_unlock(&mutex); 
} 
 
 int main(){ 
        cout<<"Enter the 'INTEGER' Initial value of share variable:"<<endl; 
        cin>>s; 
       cout<<endl; 
        int rn, wn, i; 
        cout<<"Enter the no. of Reader"<<endl; 
        cin>>rn; 
        for(i=0; i<rn; i++){ 
                cout<<i<<endl; 
        } 
        cout<<"Enter the no. of Write"<<endl; 
        cin>>wn; 
        for(i=0; i<wn; i++){ 
                cout<<i<<endl; 
        } 
 
        pthread_t r[rn], w[wn]; 
        pthread_mutex_init(&wrt, NULL); 
        pthread_mutex_init(&mutex, NULL); 
 
        if(rn<0 || wn<0){ 
                cout<<"Sorry: You have Entered NEGATIVE number of READER | WRITER"<<endl; 
                cout<<"Program is Terminating..."<<endl; 
                return 1; 
        }else if(rn == 0){ 
                cout<<"Sorry: You have not taken any READER"<<endl; 
                cout<<"No READER thread will be created"<<endl; 
        }else if(wn == 0){ 
                cout<<"Sorry: You have not taken any WRITE"<<endl; 
                cout<<"No WRITER thread will be created"<<endl; 
        }else{ 
                cout<<"Thread Creating...."<<endl; 
        } 
         cout<<endl; 
 
        if(wn==rn){ 
                for(i=0; i<wn; i++){ 
                        pthread_create(&w[i], NULL, &writer, (int *)i); 
                        pthread_create(&r[i], NULL, &reader, (int *)i); 
                } 
                for(i=0; i<wn; i++){ 
                        pthread_join(w[i], NULL); 
                        pthread_join(r[i], NULL); 
                } 
        }else if(wn>rn){ 
                for(i=0; i<rn; i++){ 
                        pthread_create(&w[i], NULL, &writer, (int *)i); 
                        pthread_create(&r[i], NULL, &reader, (int *)i); 
                } 
                for(i=rn; i<wn; i++){ 
                        pthread_create(&w[i], NULL, &writer, (int *)i); 
                } 
                for(i=0; i<rn; i++){ 
                        pthread_join(w[i], NULL); 
                        pthread_join(r[i], NULL); 
                } 
                for(i=rn; i<wn; i++){ 
                        pthread_join(w[i], NULL); 
                } 
        }else{ 
                for(i=0; i<wn; i++){ 
                        pthread_create(&w[i], NULL, &writer, (int *)i); 
                        pthread_create(&r[i], NULL, &reader, (int *)i); 
                } 
                for(i=wn; i<rn; i++){ 
                        pthread_create(&r[i], NULL, &reader, (int *)i); 
                } 
                for(i=0; i<wn; i++){ 
                        pthread_join(w[i], NULL); 
                        pthread_join(r[i], NULL); 
                } 
                for(i=wn; i<rn; i++){ 
                        pthread_join(r[i], NULL); 
                } 
        } 
        cout<<"After joining the thread"<<endl; 
        cout<<"Final value of share variable ="<<endl<<s; 
} 
