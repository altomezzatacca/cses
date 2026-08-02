#include "bits/stdc++.h"
using namespace std;
typedef complex<double> cd;
typedef long long ll;
constexpr double PI = acos(-1);
 
cd temp[1<<19];
 
void fft(cd arr[], int step, int size){ // con l'uso di data posso usare un array statico modificando il vector dinamico
	if (size == 1) return;
	
	cd omega = exp(2i * (PI / size));
	
	fft(arr, 2 * step, size / 2);
	fft(arr + step, 2 * step, size / 2);
	
	for(int j = 0; j < size; j++) temp[j] = arr[j*step];
	
	cd w = 1;
	for(int j = 0; j < size / 2; j++){
		arr[j*step] = temp[2*j] + w * temp[2*j+1];
		arr[(j+size/2)*step] = temp[2*j] - w * temp[2*j+1];
		w *= omega;
	}
}
 
void ifft(cd arr[], int step, int size){
	if(size == 1) return;
	
	cd omega = exp(-2i * (PI / size));
	
	ifft(arr, 2 * step, size / 2);
	ifft(arr + step, 2 * step, size / 2);
	
	for(int j = 0; j < size; j++) temp[j] = arr[j*step];
	
	cd w = 1;
	for(int j = 0; j < size / 2; j++){
		arr[j*step] = temp[2*j] + w * temp[2*j+1];
		arr[(j+size/2) * step] = temp[2*j] - w * temp[2*j+1];
		w *= omega;
	}
}
 
vector<ll> mult(vector<ll> P, vector<ll> Q){
	int size = 1 << (int)ceil(log2(P.size() + Q.size() - 1));
	vector<cd> p(size), q(size);
	
	copy(P.begin(), P.end(), p.begin());
	copy(Q.begin(), Q.end(), q.begin());
	
	fft(p.data(), 1, size);
	fft(q.data(), 1, size);
	
	for(int i = 0; i < size; i++) p[i] *= q[i];
	
	ifft(p.data(), 1, size);
	
	vector<ll> ans(size);
	for(int i = 0; i < size; i++) ans[i] = p[i].real() / size + 0.5;
	
	return ans;
	
}
 
int main(){
	
	int n, m; cin >> n >> m;
	vector<ll> signal(n), mask(m);
	
	for(auto &u: signal) cin >> u;
	for(auto &u: mask) cin >> u;
	reverse(mask.begin(), mask.end());
	
	signal.resize( 1LL * 1 << (ll)ceil(log2(n)) );
	mask.resize( 1LL * 1 << (ll)ceil(log2(m)) );
	
	vector<ll> ans = mult(signal, mask);
	
	for(int i = 0; i < n + m - 1; i++){
		cout << ans[i] << " ";
	}
	
	return 0;
}
