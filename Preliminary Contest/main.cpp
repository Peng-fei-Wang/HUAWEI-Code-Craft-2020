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

using namespace std;
typedef unsigned int ui;
const int MaxElement = 290000;
const int P = 4;
int cores = 4;

//output
char buffer[P][8][68157440];
int num[P][8];
//input
int fd, iter = 0, length;
char * buf;

int ansnum[P];
bool vis[P][MaxElement];
int to[MaxElement][50];
int back[MaxElement][255];
int to_index[MaxElement];
int back_index[MaxElement];
int element_number; 
int aftcon1[P][MaxElement],aftcon2[P][MaxElement],aftcon3[P][MaxElement];

inline void fast_buffer_int(int x){
	if(x > 9){
		fast_buffer_int(x / 10);
	}
	buffer[0][0][num[0][0]++] = x % 10 + '0';
	return;
}
inline void fast_buffer_uint(int x, const int p, const int step){
	if(x > 9){
		fast_buffer_uint(x / 10, p, step);
	}
	buffer[p][step][num[p][step]++] = x % 10 + '0';
	return;
}

void thread_dfs(int p, int begin, int end){	
	for(int ii = begin; ii < end; ii++){
		if(to_index[ii] == 0 || back_index[ii] == 0) continue;
		for(int j = 0; j < back_index[ii]; j++) {
			int e = back[ii][j];
			if(e < ii) continue;
			aftcon3[p][e] = aftcon2[p][e] = aftcon1[p][e] = ii;
			for(int k = 0; k < back_index[e]; k++){
				int d = back[e][k];
				if(d < ii) continue;
				aftcon3[p][d] = aftcon2[p][d] = ii;
				for(int l = 0; l < back_index[d]; l++){
					int dd = back[d][l];
					aftcon3[p][dd] = ii;
				}
			}
		}
		int v1 = ii;
		int i = 0;
		while(i < to_index[v1] && to[v1][i] <= v1) i++;
		for(; i < to_index[v1]; i++){
			int v2 = to[v1][i];
			vis[p][v2] = true;
			int j = 0;
			while(j < to_index[v2] && to[v2][j] <= v1) j++;
			for(; j < to_index[v2]; j++){
				int v3 = to[v2][j];
				if(vis[p][v3]) continue;
				vis[p][v3] = true;
				int k = 0;
				while(k < to_index[v3] && to[v3][k] < v1) k++;
				if(k != to_index[v3] && to[v3][k] == v1) {
					ansnum[p]++;
					fast_buffer_uint(v1, p, 3);
					buffer[p][3][num[p][3]++] = ',';
					fast_buffer_uint(v2, p, 3);
					buffer[p][3][num[p][3]++] = ',';
					fast_buffer_uint(v3, p, 3);
					buffer[p][3][num[p][3]++] = '\n';
					k++;
				}
				for(; k < to_index[v3]; k++){
					int v4 = to[v3][k];
					if(vis[p][v4]) continue;
					vis[p][v4] = true;
					int l = 0;
					while(l < to_index[v4] && to[v4][l] < v1) l++;
					if(l != to_index[v4] && to[v4][l] == v1) {
						ansnum[p]++;
						fast_buffer_uint(v1, p, 4);
						buffer[p][4][num[p][4]++] = ',';
						fast_buffer_uint(v2, p, 4);
						buffer[p][4][num[p][4]++] = ',';
						fast_buffer_uint(v3, p, 4);
						buffer[p][4][num[p][4]++] = ',';
						fast_buffer_uint(v4, p, 4);
						buffer[p][4][num[p][4]++] = '\n';
						l++;
					}
					for(; l < to_index[v4]; l++){
						int v5 = to[v4][l];
						if(vis[p][v5] || aftcon3[p][v5] != v1) continue;
						vis[p][v5] = true;
						int m = 0;
						while(m < to_index[v5] && to[v5][m] < v1) m++;
						if(m != to_index[v5] && to[v5][m] == v1) {
							ansnum[p]++;
							fast_buffer_uint(v1, p, 5);
							buffer[p][5][num[p][5]++] = ',';
							fast_buffer_uint(v2, p, 5);
							buffer[p][5][num[p][5]++] = ',';
							fast_buffer_uint(v3, p, 5);
							buffer[p][5][num[p][5]++] = ',';
							fast_buffer_uint(v4, p, 5);
							buffer[p][5][num[p][5]++] = ',';
							fast_buffer_uint(v5, p, 5);
							buffer[p][5][num[p][5]++] = '\n';
							m++;
						}
						for(; m < to_index[v5]; m++){
							int v6 = to[v5][m];
							if(vis[p][v6] || aftcon2[p][v6] != v1) continue;
							vis[p][v6] = true;
							int n = 0;
							while(n < to_index[v6] && to[v6][n] < v1) n++;
							if(n != to_index[v6] && to[v6][n] == v1) {
								ansnum[p]++;
								fast_buffer_uint(v1, p, 6);
								buffer[p][6][num[p][6]++] = ',';
								fast_buffer_uint(v2, p, 6);
								buffer[p][6][num[p][6]++] = ',';
								fast_buffer_uint(v3, p, 6);
								buffer[p][6][num[p][6]++] = ',';
								fast_buffer_uint(v4, p, 6);
								buffer[p][6][num[p][6]++] = ',';
								fast_buffer_uint(v5, p, 6);	
								buffer[p][6][num[p][6]++] = ',';
								fast_buffer_uint(v6, p, 6);	
								buffer[p][6][num[p][6]++] = '\n';
								n++;
							}
							for(; n < to_index[v6]; n++){
								int v7 = to[v6][n];
								if(vis[p][v7] ||  aftcon1[p][v7] != v1) continue;
								ansnum[p]++;
								fast_buffer_uint(v1, p, 7);
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v2, p, 7);
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v3, p, 7);
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v4, p, 7);
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v5, p, 7);	
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v6, p, 7);	
								buffer[p][7][num[p][7]++] = ',';
								fast_buffer_uint(v7, p, 7);	
								buffer[p][7][num[p][7]++] = '\n';
							}
							vis[p][v6] = false;
						}
						vis[p][v5] = false;
					}
					vis[p][v4] = false;
				}
				vis[p][v3] = false;
			}
			vis[p][v2] = false;
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

inline int next_int() {
	int number = 0;
	char ch = get();
	for (; isdigit(ch); ch = get())
		number = number * 10 + ch - '0';
	return number;
}

int main(){
	// fd = open("test_data.txt", O_RDONLY, 0666);
	fd = open("/data/test_data.txt", O_RDONLY, 0666);
	
	FILE* file = fdopen(fd, "r");
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	buf = (char*)mmap(0, length, PROT_READ, MAP_PRIVATE, fd, 0);
	element_number = 0;

	while(has_next()){
		int x, y, w;
		x=next_int();
		y=next_int();
		w=next_int();
		if(element_number < x) element_number = x;
		to[x][to_index[x]++] = y;
		back[y][back_index[y]++] = x;		
	}

	close(fd);
	
	int nodes_number = 0; 
	element_number++;
	for(int i = 0; i < element_number; i++) {
		if(to_index[i] != 0 && back_index[i] != 0){
			aftcon3[0][i] = aftcon2[0][i] = aftcon1[0][i] = -1;
			sort(to[i], to[i] + to_index[i]);
		} 
	}

	thread th1(thread_dfs, 3, element_number / 4, element_number);
	thread th2(thread_dfs, 2, element_number / 12, element_number / 4);
	thread th3(thread_dfs, 1, element_number / 24, element_number / 12);
	thread th4(thread_dfs, 0, 0, element_number / 24);
	th1.join();
	th2.join();
	th3.join();
	th4.join();

    // FILE *stream = fopen("result.txt", "w");
	FILE *stream = fopen("/projects/student/result.txt", "w");
	
	int thread_num = 0;
	for(int i = 0; i < cores; i++){
		thread_num += ansnum[i];
	}
	fast_buffer_int(thread_num); 
	buffer[0][0][num[0][0]++] = '\n';
	fwrite(buffer[0][0], num[0][0], 1, stream);
	for(int i = 3; i <= 7; i++){
		for(int p = 0; p < cores; p++){
			fwrite(buffer[p][i], num[p][i], 1, stream);
		}
	}
	fclose(stream);
	
	return 0;
}

