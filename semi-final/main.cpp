#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm> 
#include<time.h> 
#include<string.h>
#include<thread>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<atomic>
#include<cmath>

# define INT_MAX 2147483647
# define page_size 65536 
# define ll long long
using namespace std;
typedef unsigned int ui;
struct Node{
	int id;
	ll high, low, w;
	Node(){}
	Node(int iid, ll ww, ll hhigh, ll llow) {
		id = iid;
		w = ww;
		high = hhigh;
		low = llow;
	}
};
bool cmp(Node& a, Node& b){
	return a.id < b.id;
}
const int MaxElement = 4000005;
const int P = 4;
const int cores = 4;

//output
char buffer[1000000000];
ui ans3[P][8000000][3];
int num3[P];
ui ans4[P][8000000][4];
int num4[P];
ui ans5[P][8000000][5];
int num5[P];
ui ans6[P][8000000][6];
int num6[P];
ui ans7[P][6000000][7];
int num7[P];
ui ans8[P][6000000][8];
int num8[P]; 
int ansnum[P];
int num;
//input
int fd, iter = 0, length;
char * buf;


bool vis[P][MaxElement];
int to_st[MaxElement];
int back_st[MaxElement];
Node to[MaxElement];
int back[MaxElement];
int back_to[MaxElement];
Node* path[P][MaxElement];
int pathnum[P][MaxElement];
int to_index[MaxElement];
int back_index[MaxElement];
int element_number;
int aftcon1[P][MaxElement],aftcon2[P][MaxElement],aftcon3[P][MaxElement];
int indx[P][MaxElement];
ui XX[2000000];
ui YY[2000000];
ll WW[2000000];
ui mymap[2000000];
atomic<bool> lock[MaxElement];
int thread_index[MaxElement];

inline void fast_buffer_int(ui x){
	if(x > 9){
		fast_buffer_int(x / 10);
	}
	buffer[num++] = x % 10 + '0';
	return;
}

void thread_dfs(int p){	
	for(int ii = p; ii < element_number; ii++){
		if(lock[ii].exchange(true, std::memory_order_relaxed)) continue; 
		if(back_index[ii] == 0) continue;
		thread_index[ii] = p;
		for(int j = back_st[ii]; j < back_st[ii + 1]; j++) {
			int e = back[j];
			if(e <= ii) continue;
			aftcon3[p][e] = aftcon1[p][e] = ii;
			indx[p][e] = back_to[j];
			int ind1 = indx[p][e];
			for(int k = back_st[e]; k < back_st[e + 1]; k++){
				int d = back[k];
				if(d <= ii) continue;
				int ind2 = back_to[k];
				if(to[ind2].high < to[ind1].w || to[ind1].w < to[ind2].low) continue;
				if(aftcon2[p][d] != ii) {
					pathnum[p][d] = to_st[d];
				}
				path[p][pathnum[p][d]++] = &to[ind2];
				aftcon3[p][d] = aftcon2[p][d] = ii;
				for(int l = back_st[d]; l < back_st[d + 1]; l++){
					int dd = back[l];
					aftcon3[p][dd] = ii;
				}
			}
		}
		int v1 = ii;
		int i = to_st[v1];
		while(i < to_st[v1 + 1] && to[i].id <= v1) i++;
		for(; i < to_st[v1 + 1]; i++){
			int v2 = to[i].id;
			vis[p][v2]=true;
			int j = to_st[v2];
			while(j < to_st[v2 + 1] && to[j].id <= v1) j++;
			for(; j < to_st[v2 + 1]; j++){
				int v3 = to[j].id;
				if(vis[p][v3] || to[i].high < to[j].w || to[j].w < to[i].low)continue;
				vis[p][v3]=true;
				int k = to_st[v3];
				while(k < to_st[v3 + 1] && to[k].id < v1) k++;
				if(k != to_st[v3 + 1] && to[k].id == v1) {
					if(to[k].w >= to[j].low && to[k].w <= to[j].high && to[k].high >= to[i].w && to[k].low <= to[i].w){
						ansnum[p]++;
						ans3[p][num3[p]][0] = v1;
						ans3[p][num3[p]][1] = v2;
						ans3[p][num3[p]++][2] = v3;
					}
					k++;
				}
				for(; k < to_st[v3 + 1]; k++){
					int v4 = to[k].id;
					if(vis[p][v4] || to[j].high < to[k].w || to[k].w < to[j].low) continue;
					vis[p][v4]=true;
					int l = to_st[v4];
					while(l < to_st[v4 + 1] && to[l].id < v1) l++;
					if(l != to_st[v4 + 1] && to[l].id == v1) {
						if(to[l].w >= to[k].low && to[l].w <= to[k].high && to[l].high >= to[i].w && to[l].low <= to[i].w) {
							ansnum[p]++;
							ans4[p][num4[p]][0] = v1;
							ans4[p][num4[p]][1] = v2;
							ans4[p][num4[p]][2] = v3;
							ans4[p][num4[p]++][3] = v4;
						}
						l++;
					}
					for(; l < to_st[v4 + 1]; l++){
						int v5 = to[l].id;
						if(vis[p][v5] || to[k].high < to[l].w || to[l].w < to[k].low) continue;
						vis[p][v5]=true;
						int m = to_st[v5];
						while(m < to_st[v5 + 1] && to[m].id < v1) m++;
						if(m != to_st[v5 + 1] && to[m].id == v1) {
							if(to[m].w >= to[l].low && to[m].w <= to[l].high && to[m].high >= to[i].w && to[m].low <= to[i].w) {
								ansnum[p]++;
								ans5[p][num5[p]][0] = v1;
								ans5[p][num5[p]][1] = v2;
								ans5[p][num5[p]][2] = v3;
								ans5[p][num5[p]][3] = v4;
								ans5[p][num5[p]++][4] = v5;	
							}
							m++;
						}
						for(; m < to_st[v5 + 1]; m++) {
							int v6 = to[m].id;
							if(vis[p][v6] || aftcon3[p][v6] != v1 || to[l].high < to[m].w || to[m].w < to[l].low) continue;
							vis[p][v6] = true;
							int n = to_st[v6];
							while(n < to_st[v6 + 1] && to[n].id < v1) n++;
							if(n != to_st[v6 + 1] && to[n].id == v1) {
								if(to[n].w >= to[m].low && to[n].w <= to[m].high && to[n].high >= to[i].w && to[n].low <= to[i].w) {
									ansnum[p]++;
									ans6[p][num6[p]][0] = v1;
									ans6[p][num6[p]][1] = v2;
									ans6[p][num6[p]][2] = v3;
									ans6[p][num6[p]][3] = v4;
									ans6[p][num6[p]][4] = v5;
									ans6[p][num6[p]++][5] = v6;
								}
								n++;
							}
							for(; n < to_st[v6 + 1]; n++){
								int v7 = to[n].id;
								if(vis[p][v7] || to[m].high < to[n].w || to[n].w < to[m].low) continue;
								if(aftcon1[p][v7] == ii) {
									int o = indx[p][v7];
									if(to[o].w >= to[n].low && to[o].w <= to[n].high && to[o].high >= to[i].w && to[o].low <= to[i].w) {
										ansnum[p]++;
										ans7[p][num7[p]][0] = v1;
										ans7[p][num7[p]][1] = v2;
										ans7[p][num7[p]][2] = v3;
										ans7[p][num7[p]][3] = v4;
										ans7[p][num7[p]][4] = v5;
										ans7[p][num7[p]][5] = v6;
										ans7[p][num7[p]++][6] = v7;
									}
								}
								if(aftcon2[p][v7] != v1) continue;
								
								for(int r = to_st[v7]; r < pathnum[p][v7]; r++) {
									int v8 = path[p][r]->id;
									int indv8 = indx[p][v8];
									if(!vis[p][v8] && to[indv8].high >= to[i].w && to[indv8].low <= to[i].w
									&& to[n].high >= path[p][r]->w && path[p][r]->w >= to[n].low) {
										ansnum[p]++;
										ans8[p][num8[p]][0] = v1;
										ans8[p][num8[p]][1] = v2;
										ans8[p][num8[p]][2] = v3;
										ans8[p][num8[p]][3] = v4;
										ans8[p][num8[p]][4] = v5;
										ans8[p][num8[p]][5] = v6;
										ans8[p][num8[p]][6] = v7;
										ans8[p][num8[p]++][7] = v8;
									}
								}
							}
							vis[p][v6] = false;
						}
						vis[p][v5]=false;
					}
					vis[p][v4]=false;
				}
				vis[p][v3]=false;
			}
			vis[p][v2]=false;
		}
	}
}

inline bool has_next() {
	while (iter < length && !isdigit(buf[iter]))
		iter++;
	return iter != length;
}

inline char get() {
	return iter == length ? EOF : buf[iter++];
}

inline ui next_ui() {
	ui number = 0;
	char ch = get();
	for (; isdigit(ch); ch = get())
		number = number * 10 + ch - '0';
	return number;
}

inline ll next_l() {
	ll x = 0;
	int y = 50;
	char ch = get();
	while(isdigit(ch)){
		x = x * 10 + (ch - '0');
		ch = get();
	}
	x *= 500;
	ch = get();
	while(isdigit(ch)){
		x += y * (ch - '0');
		y = 5;
		ch = get();
	}
	return x;
}

int main(){
	fd = open("/data/test_data.txt", O_RDONLY, 0666);
	FILE* file = fdopen(fd, "r");
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	buf = (char*)mmap(0, length, PROT_READ, MAP_PRIVATE, fd, 0);
	element_number = 0;
	int nod_number = 0;
	while(has_next()){
		XX[nod_number] = next_ui();
		YY[nod_number] = next_ui();
		WW[nod_number] = next_l();
		mymap[nod_number] = XX[nod_number];
		nod_number++;
		
	}
	
	close(fd);
	
	unordered_map<ui, int> q;
	sort(mymap, mymap + nod_number);
	element_number = unique(mymap, mymap + nod_number) - mymap;
	for(int i = 0; i < element_number; i++) q[mymap[i]] = i;
	for(int i = 0; i < nod_number; i++) {
		if(q.find(YY[i]) == q.end()) continue;
		int x = q[XX[i]];
		int y = q[YY[i]];
		to_st[x + 1]++;
		back_st[y + 1]++;
	}

	for(int i = 2 ; i <= element_number; i++) {
		to_st[i] += to_st[i - 1];
		back_st[i] += back_st[i - 1];
	}

	for(int i = 0; i < nod_number; i++) {
		if(q.find(YY[i]) == q.end()) continue;
		int x = q[XX[i]];
		int y = q[YY[i]];
		to[to_st[x] + to_index[x]].id = y;
		to[to_st[x] + to_index[x]].w = WW[i];
		to[to_st[x] + to_index[x]].low = WW[i] / 5;
		to[to_st[x] + to_index[x]++].high = WW[i] * 3;
	}
	
	for(int i = 0; i < element_number; i++) {
		aftcon3[0][i] = aftcon2[0][i] = aftcon1[0][i] = -1;
		sort(to + to_st[i], to + to_st[i + 1], cmp);
		for(int j = 0; j < to_index[i]; j++) {
			int y = to[to_st[i] + j].id;
			back[back_st[y] + back_index[y]] = i;
			back_to[back_st[y] + back_index[y]++] = to_st[i] + j;
		}
	}
	thread th1(thread_dfs, 0);
	thread th2(thread_dfs, 1);
	thread th3(thread_dfs, 2);
	thread th4(thread_dfs, 3);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
    
	FILE *stream = fopen("/projects/student/result.txt", "w");

	int thread_num = 0;
	for(int i = 0; i < cores; i++){
		thread_num += ansnum[i];
	}
	fast_buffer_int(thread_num); 
	buffer[num++] = '\n';

	int cur_index[4];
	for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}

	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans3[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans3[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans3[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans3[min_index][cur_index[min_index]++][2]]);
			buffer[num++] = '\n';
		}		
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}	
	}

	for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}
	
	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans4[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans4[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans4[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans4[min_index][cur_index[min_index]][2]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans4[min_index][cur_index[min_index]++][3]]);
			buffer[num++] = '\n';
		}			
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}	
	}	

	for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}
	
	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans5[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans5[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans5[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans5[min_index][cur_index[min_index]][2]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans5[min_index][cur_index[min_index]][3]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans5[min_index][cur_index[min_index]++][4]]);
			buffer[num++] = '\n';
		}	
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}			
	}

	for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}
		
	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans6[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]][2]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]][3]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]][4]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans6[min_index][cur_index[min_index]++][5]]);
			buffer[num++] = '\n';
		}	
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}			
	}

	for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}
	
	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans7[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][2]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][3]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][4]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]][5]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans7[min_index][cur_index[min_index]++][6]]);
			buffer[num++] = '\n';
		}	
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}			
	}
    
    for(int i = 0; i < cores; i++){
		cur_index[i] = 0;
	}
	
	for(int i = 0; i < element_number; i++){
		int min_index = thread_index[i];
		while(ans8[min_index][cur_index[min_index]][0] == i){
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][0]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][1]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][2]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][3]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][4]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][5]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]][6]]);
			buffer[num++] = ',';
			fast_buffer_int(mymap[ans8[min_index][cur_index[min_index]++][7]]);
			buffer[num++] = '\n';
		}	
		if(num >= page_size){
			fwrite(buffer, num, 1, stream);
			num = 0;
		}		
	}

	fwrite(buffer, num, 1, stream);
	fclose(stream);
	
	return 0;
}
