#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

void merge(vector<long long> &v, int st, int m, int dr){
    int l = m-st+1 , r= dr-m;
    vector<long long> vst(l), vdr(l);
    for(int i=0; i<l; i++) {
        vst[i] = v[st + i];
        vdr[i] = v[m + 1 + i];
    }
    int indl = 0, indr= 0;
    int indmerge = st;
    while (indl < l && indr < r) {
        if (vst[indl] <= vdr[indr]) {
            v[indmerge] = vst[indl];
            indl++;
        }
        else {
            v[indmerge] = vdr[indr];
            indr++;
        }
        indmerge++;
    }
    while (indl < l) {
        v[indmerge] = vst[indl];
        indl++;
        indmerge++;
    }
    while (indr < r) {
        v[indmerge] = vdr[indr];
        indr++;
        indmerge++;
    }
}

void mergeSort(vector<long long> &v,int st,int dr){
    if (dr > st) {
        int m = st + (dr - st) / 2;
        mergeSort(v, st, m);
        mergeSort(v, m + 1, dr);
        merge(v, st, m, dr);
    }
}

void heap(vector<long long> &v, int n, long long x){
    auto max = x;
    auto st = 2 * x +1;
    auto dr = 2 * x +2;
    if(st < n  && v[st] > v[max])
        max = st;
    if(dr < n && v[dr] > v[max])
        max = dr;
    if(max != x) {
        swap(v[max], v[x]);
        heap(v,n, max);
    }
}
void Heapsort(vector<long long> &v, int n){
    for(int i = n/2-1; i >= 0; i--)
        heap(v,n,i);
    for(int i = n - 1; i >= 0; i--){
        swap(v[0],v[i]);
        heap(v, i, 0);
    }
}

void shellsort(vector<long long> &v, int n){
    for(int gap = n/2;gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            long long aux = v[i];
            int j;
            for(j = i; j >= gap && v[j-gap] > aux; j -= gap)
                v[j] = v[j - gap];
            v[j] = aux;
        }
    }
}

void countSort(vector<long long> &v, int n, long long maxim){
    int i;
    vector<long long> count(maxim);
    long long j = 0;
    for (i = 0; i < n; i++)
        count[v[i]]++;
    for (i = 0; i < n; i++) {
        while(count[j] == 0) j++;
        v[i] = j;
        count[j]--;
    }
}

void radixsort(vector<long long> &v, int n, int baza)
{
    long long m = v[0];
    int i;
    vector<long long> iesire(n);
    for(int i = 1; i < n; i++) if(m < v[i]) m = v[i];
    for (long long cif = 1; m / cif > 0; cif *= baza) {
        int count[baza] = {0};
        for (i = 0; i < n; i++)
            count[(v[i] / cif) % baza]++;
        for (i = 1; i < baza; i++)
            count[i] += count[i - 1];
        for (i = n - 1; i >= 0; i--) {
            iesire[count[(v[i] / cif) % baza] - 1] = v[i];
            count[(v[i] / cif) % baza]--;
        }
        for (i = 0; i < n; i++)
            v[i] = iesire[i];
    }
}

bool sortat(vector<long long> &v, vector<long long> &a) {
    for (int i = 0; i < v.size(); ++i)
        if (v[i] != a[i]) return false;
    return true;
}

int main() {
    clock_t Start = clock();
    int nrteste,n;
    long long maxim;
    ifstream fisier("input.in");
    fisier>>nrteste;
    for(int i = 0; i < nrteste; i++){
        fisier>>n>>maxim;
        cout<<"N="<<n<<" M="<<maxim<<endl;
        vector<long long> d(n),c(n),a(n);
        srand(unsigned(time(nullptr)));
        for (int j = 0; j < n; j++) {
            d[j] = rand();
            d[j] = (d[j] * d[j] * d[j]) % maxim;
        }
        a = d;
        Start = clock();
        sort(a.begin(), a.end());
        cout.precision(5);
        cout << "STL sort: " << fixed << float(clock() - Start) / CLOCKS_PER_SEC << "s" << endl;

        c = d;
        Start = clock();
        radixsort(c, n, 8);
        cout.precision(5);
            cout << "RadixSort(8): " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   ";
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        c = d;
        Start = clock();
            radixsort(c, n, 10);
        cout.precision(5);
            cout << "RadixSort(10): " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   ";
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        c = d;
        Start = clock();
        radixsort(c, n, pow(2,16));
        cout.precision(5);
            cout << "RadixSort(2^16): " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   ";
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        c = d;
        Start = clock();
        shellsort(c, n);
        cout.precision(5);
            cout << "ShellSort: " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   " ;
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        c = d;
        Start = clock();
        Heapsort(c, n);
        cout.precision(5);
            cout << "HeapSort: " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   " ;
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        c = d;
        Start = clock();
        mergeSort(c, 0, n-1);
        cout.precision(5);
            cout << "MergeSort: " << fixed << float(clock() - Start)/CLOCKS_PER_SEC << "s   " ;
        if( sortat(c, a)) cout<<"Sortat"<< endl;

        if(maxim <= 1000000000){
        c = d;
        Start = clock();
        countSort(c, n, maxim);
        cout.precision(5);
        cout << "CountSort: " << fixed << float(clock() - Start) / CLOCKS_PER_SEC << "s   ";
        if( sortat(c, a)) cout<<"Sortat"<< endl;}
        else cout<<"CountSort nu se poate sorta din cauza valorilor prea mari"<<endl;
    cout<<endl<<endl;
    }
    fisier.close();
    return 0;
}