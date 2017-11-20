#include <bits/stdc++.h>
#define loop(a,b,c) for(int a=b;a<c;a++)
#define pb push_back
#define sz(v) v.size()
#define mp make_pair
#define all(v) v.begin(),v.end()
#define fi first
#define se second
using namespace std;
vector<string> solusi,child,next_solusi, merged;
int V[1001],W[1001],barang,batasbeban;

bool cmp(pair<int,int> a,pair<int,int> b){
 if(a.fi==b.fi)return a.se>b.se;
 else return a.fi>b.fi;
}

bool cmp2(pair<double,int> a,pair<double,int> b){
 if(a.fi==b.fi)return a.se>b.se;
 else return a.fi>b.fi;
}

void bitwise(){
 int kk=sz(solusi);
 loop(i,0,kk){
  string z=solusi[i];
  int pp=z.length();
  loop(j,0,pp){
   double acak=((double)rand()/(RAND_MAX));
   if(acak<1.0/barang)z[j]=(((int)z[j]-(int)'0'+1)%2)+(int)'0';
  }
  child.pb(z);
 }
}

void crossover(){
	for(int i = 0; i < sz(solusi); i+=2){
		string hasil1, hasil2;
		int r = rand()%(sz(solusi[0])+1);
		loop(ir, 0, r){
			hasil1.pb(solusi[i][ir]);
			hasil2.pb(solusi[i+1][ir]);
		}
		loop(ir, r, sz(solusi[0])){
			hasil1.pb(solusi[i+1][ir]);
			hasil2.pb(solusi[i][ir]);
		}
		child.pb(hasil1);
		child.pb(hasil2);
	}

}

void rasio(int idx){
 string z=child[idx];
 int kk=z.length();
 vector<pair<double,int> > ada;
 int beban=0;
 loop(i,0,kk){
  if(z[i]=='1'){
   ada.pb(mp((double)V[i]/(double)W[i],i));
   beban+=W[i];
  }
 }
 sort(all(ada),cmp2);
 while(beban>batasbeban){
  beban-=W[ada.back().se];
  z[ada.back().se]='0';
  ada.pop_back();
 }
 child[idx]=z;
}

void randomm(int idx){
 string z=child[idx];
 int kk=z.length();
 vector<int> ada;
 int beban=0;
 loop(i,0,kk){
  if(z[i]=='1'){
   ada.pb(i);
   beban+=W[i];
  }
 }
 int jj=sz(ada);
 while(beban>batasbeban){
  int rr=rand()%jj;
  beban-=W[rr];
  z[ada[rr]]='0';
  loop(i,rr,jj-1)ada[i]=ada[i+1];
  ada.pop_back();
  jj--;
 }
 child[idx]=z;
}

void nilai(int idx){
 string z=child[idx];
 int kk=z.length();
 vector<pair<int,int> > ada;
 int beban=0;
 loop(i,0,kk){
  if(z[i]=='1'){
   ada.pb(mp(V[i],i));
   beban+=W[i];
  }
 }
 sort(all(ada),cmp);
 while(beban>batasbeban){
  beban-=W[ada.back().se];
  z[ada.back().se]='0';
  ada.pop_back();
 }
 child[idx]=z;
}
int hitung_fitness(string bv){
	int fitness = 0;
	loop(i,0,sz(bv)){
		fitness+=(((int)bv[i]-(int)'0')*V[i]);
	}	
	return fitness;
}
void roulette(){
	int totalfitness;
	int fitness[sz(merged)];
	loop(i,0,sz(merged)){
		fitness[i] = hitung_fitness(merged[i]);
		totalfitness += fitness[i];
	}
	loop(i, 0, sz(solusi)-1){
		double r=rand()%11; r/=10;
		loop(ix, 0, sz(merged)){
			double cumulative = 0;
			cumulative += fitness[i]/(double)totalfitness;
			if (r<cumulative){
				next_solusi.pb(merged[i]);
				break;
			}
		}
	}
}

int main() {
 srand(time(NULL));
 int N;
 cin>>barang>>batasbeban;
 loop(i,0,barang){
  cin>>W[i]>>V[i];
 }
 cin>>N;
 while(sz(solusi)<N){
  string hasil;
  int beban=0;
  loop(i,0,barang){
   int stat=rand()%2;
   beban+=(W[i]*stat);
   hasil.pb((int)'0'+stat);
  }
  if(beban<=batasbeban)solusi.pb(hasil);
 }
 loop(i,0,N)cout<<solusi[i]<<"\n";
 double r=rand()%11; r/=10;
 if(r<0.9)bitwise();
 else crossover();
 int banyak=sz(child);
 loop(i,0,sz(child)){
  int p=child[i].length();
  int beban=0;
  loop(j,0,p){
   beban+=(((int)child[i][j]-(int)'0')*W[j]);
  }
  if(beban>batasbeban){
   int prob=rand()%3;
   if(prob==0)rasio(i);
   else if(prob==1)randomm(i);
   else nilai(i);
  }
 }
 int imax = -1;
 int max = -1;
 merged.reserve(solusi.size() + child.size()); 
 std::merge(solusi.begin(), solusi.end(), child.begin(), child.end(), std::back_inserter(merged));
 loop(i, 0, sz(merged)){
 	int fit = hitung_fitness(merged[i]);
 	if (fit > max){
 		max = fit;
 		imax = i;
 	}
 }
 next_solusi.pb(merged[imax]);
 roulette();
 int kk=sz(next_solusi);
 loop(i,0,kk)cout<<next_solusi[i]<<"\n";
}
