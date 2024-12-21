#include<bits/stdc++.h>
using namespace std;

bool HH(int n, const vector<vector<int>> graph, vector<bool>& visited, int tg){
	visited[n] = true;
	if(n == tg){
		cout << "Da tim thay so " << tg << " tai dinh " << n << endl;
		return true;
	}
	for(int neighbor : graph[n]){
		if(!visited[neighbor]){
			if(HH(neighbor, graph, visited, tg)){
				return true;
			}
		}
	}
	return false;
}
int main(){
	int k, nn;
	cout << "Nhap so dinh: ";
	cin >> k;
	vector<vector<int>> graph(k);
	
	cout << "Nhap so canh: ";
	cin >> nn;
	cout << "Nhap cac cap dinh noi(u,v):" << endl;
	for(int i = 0; i<nn;i++){
		int u,v;
		cin  >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	int tg;
	cout << "Nhap so can tim: ";
	cin >> tg;
	vector<bool> visited(k, false);
	cout << "Bat dau tim tu dinh 0" << endl;
	if(!HH(0, graph,visited,tg)){
		cout << "Khong tim thay so " << tg << " trong do thi!" << endl;
	}
	return 0;
}
