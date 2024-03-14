#include "iostream"
#include "fstream"
#include "string.h"
#include "stdlib.h"
#include <vector>
#include <iomanip>
#include "math.h"
#include "limits.h"
#include "time.h"
#include <ctime>
using namespace std;
#define DROP_FACTOR 0.999
#define MAX_VAL RAND_MAX
class TSP {
private:
vector<double>x,y;
vector<vector<double>>mat;
int *currentPath;
int *exchangedPath;
int *bestPath;
double temparature;
public:
 TSP(){

 };
 ~TSP(){
     delete[] currentPath;
     delete[] exchangedPath;
     delete[] bestPath;
 };
 void initialise();
 void SimulatedAnnealing();
 double cost(int *,int n);
 void getNewPath(int *,int, int);
 void pathExchange(int *,int *,int);
};
 void TSP::initialise(){
    temparature=1e9;
 }
 void TSP::SimulatedAnnealing(){
  string distance_type;
  getline(cin,distance_type);
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    double a,b;
   cin>>a>>b;
   x.push_back(a);
   y.push_back(b);
  }
  for(int i=0;i<n;i++){
      vector<double>temp(n);
      for(int j=0;j<n;j++){
           cin>>temp[j];
      }
      mat.push_back(temp);
      temp.clear();
  }
  currentPath=new int[n+1];
  exchangedPath=new int[n+1];
  bestPath=new int[n+1];
  for(int i=0;i<=n;i++){
       currentPath[i]=exchangedPath[i]=bestPath[i]=0;
  }
  for(int i=0;i<=n;i++){
    if(i==n) {
        currentPath[i]=n-1;
    }
    else{
      currentPath[i]=(n-1)-i;
      continue;
    }
  }

  for(int i=0;i<=n;i++){
      if(i==n){
          exchangedPath[i]=n-1;
      }
      else{
          exchangedPath[i]=n-1-i;;
      }
  }

  for(int i=0;i<=n;i++){
     if(i==n){
         bestPath[i]=n-1;
     }
     else{
       bestPath[i]=(n-1)-i;
       continue;
     }
  }
  int k;
  for(;;){
   for(int k=100;k>0;k--){
    pathExchange(exchangedPath,currentPath,n);
    int r1,r2;
    r1=(rand()%(n-1))+1;
    r2=(rand()%(n-1))+1;
    getNewPath(exchangedPath,r1,r2);
    double gain;
    gain=cost(exchangedPath,n) - cost(currentPath,n);
    double randProb;
    randProb=(double) ((double)rand()/ (double) MAX_VAL);
    double prob = pow((1+ pow(M_E, (gain/temparature))),-1);
    if(randProb<prob){
      pathExchange(currentPath,exchangedPath,n);
    }
    if(cost(exchangedPath,n) < cost(bestPath,n) ){
      pathExchange(bestPath,exchangedPath,n);
      // cout<<fixed<<setprecision(2)<<"The shortest cost obtained so far is "<<cost(bestPath,n)<<endl;
      for(int i=0;i<n;i++){
          int temp=bestPath[i];
          cout<<temp<<" ";
      }
      cout<<endl;
    }
   }
   temparature=temparature*DROP_FACTOR;
  }
 }

 void TSP::getNewPath(int * exchangedPath,int a, int b ){
  if(b<a){
     swap(a,b);
  }
  int d=b-a;
  int l=(d+1)/2;
  int i,j;
  i=a;
  j=b;
     int k=0;
     while(k<=l){
      swap(exchangedPath[i++],exchangedPath[j--]);
      k++;
     }

 }

 double TSP::cost(int *path,int n){
  double cost_val=0;
  for(int i=0;i<n;i++){
    int a =path[i];
    int b =path[i+1];
    cost_val=cost_val+mat[a][b];
  }
  return cost_val;
 }

void TSP::pathExchange(int *path1, int *path2, int n) {
  for(int i=1;i<n;i++){
      path1[i]=path2[i];
  }
}
 int main(){
  TSP tsp;
  tsp.initialise();
  tsp.SimulatedAnnealing();
  return 0;
 }
