#include <bits/stdc++.h>
#include <ctime>
#include <vector>

using namespace std;
using namespace std::chrono;

int n, c, max_side;

// notation: https://drive.google.com/file/d/1GC2jjehBaVT8eMVL-qbUNi2qrkReFUAY/view?usp=sharing
// [R1, R2, R3, diagonal D1, diagonal D2, DR1, DR2, DR3, DR4]
vector<int> sumVec;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_real_distribution<double> distribution (0,1);

// From annealing.cpp
long long unitDist(long long x, long long c){
    return (x - c) * (x - c) * (x - c) * (x - c) * (x - c) * (x - c);
}

// From annealing.cpp
long long distanceMat(vector<int> arr){
    vector<int> sumHor(n, 0);
    vector<int> sumVer(n, 0);
    assert(arr.size() == n * n);
    for(int i = 0; i < n * n; i++){
        sumHor[i / n] += arr[i];
        sumVer[i % n] += arr[i];
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans += unitDist(sumHor[i], c);
        ans += unitDist(sumVer[i], c);
    }
    return ans;
}

// From annealing.cpp
vector<int> distanceVec(vector<int> arr){
    vector<int> sumPillar(n * n, 0);
    vector<int> ans;
    for(int i = 0; i < (int)arr.size(); i += n * n){
        vector<int> temp;
        vector<int> sumHor(n, 0);
        for(int j = i; j < i + n * n; j++){
            sumPillar[j % (n * n)] += arr[j];
            sumHor[(j / n) % n] += arr[j];
        }
        ans.insert(ans.end(), sumHor.begin(), sumHor.end());
    }
    for(int i = 0; i < (int)arr.size(); i += n * n){
        vector<int> temp;
        vector<int> sumVer(n, 0);
        for(int j = i; j < i + n * n; j++){
            sumVer[j % n] += arr[j];
        }
        ans.insert(ans.end(), sumVer.begin(), sumVer.end());
    }
    ans.insert(ans.end(), sumPillar.begin(), sumPillar.end());
    for(int k = 0; k < n; k++){
        int i1 = 0, j1 = 0;
        int i2 = 0, j2 = n - 1;
        // D1
        int st1 = 0, st2 = 0;
        for(int u = 0; u < n; u++){
            st1 += arr[(k * n * n + i1 * n + j1)];
            st2 += arr[(k * n * n + i2 * n + j2)];
            i1++; i2++;
            j1++; j2--;
        }
        ans.push_back(st1);
        ans.push_back(st2);
    }
    for(int k = 0; k < n; k++){
        int i1 = 0, j1 = 0;
        int i2 = 0, j2 = n - 1;
        // D2
        int st3 = 0, st4 = 0;
        for(int u = 0; u < n; u++){
            st3 += arr[(i1 * n * n + k * n + j1)];
            st4 += arr[(i2 * n * n + k * n + j2)];
            i1++; i2++;
            j1++; j2--;
        }
        ans.push_back(st3);
        ans.push_back(st4);
    }
    int r1 = 0, c1 = 0;
    int r2 = 0, c2 = n - 1;
    int r3 = n - 1, c3 = 0;
    int r4 = n - 1, c4 = n - 1;
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    for(int i = 0; i < n; i++){
        s1 += arr[(r1 * n + c1) + i * n * n];
        s2 += arr[(r2 * n + c2) + i * n * n];
        s3 += arr[(r3 * n + c3) + i * n * n];
        s4 += arr[(r4 * n + c4) + i * n * n];
        r1++; c1++;
        r2++; c2--;
        r3--; c3++;
        r4--; c4--;
    }
    ans.push_back(s1);
    ans.push_back(s2);
    ans.push_back(s3);
    ans.push_back(s4);
    return ans;
}

// From annealing.cpp
long long distance(vector<int> &arr){
    int cnt = 0;
    vector<int> sumPillar(n * n, 0);
    long long ans = 0;
    for(int i = 0; i < (int)arr.size(); i += n * n){
        vector<int> temp;
        for(int j = i; j < i + n * n; j++){
            sumPillar[j % (n * n)] += arr[j];
            temp.push_back(arr[j]);
        }
        ans += distanceMat(temp);
    }
    for(int i = 0; i < n * n; i++){
        ans += unitDist(sumPillar[i], c);
    }
    int r1 = 0, c1 = 0;
    int r2 = 0, c2 = n - 1;
    int r3 = n - 1, c3 = 0;
    int r4 = n - 1, c4 = n - 1;
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    for(int i = 0; i < n; i++){
        s1 += arr[(r1 * n + c1) + i * n * n];
        s2 += arr[(r2 * n + c2) + i * n * n];
        s3 += arr[(r3 * n + c3) + i * n * n];
        s4 += arr[(r4 * n + c4) + i * n * n];
        r1++; c1++;
        r2++; c2--;
        r3--; c3++;
        r4--; c4--;
    }
    ans += unitDist(s1, c);
    ans += unitDist(s2, c);
    ans += unitDist(s3, c);
    ans += unitDist(s4, c);
    for(int k = 0; k < n; k++){
        int i1 = 0, j1 = 0;
        int i2 = 0, j2 = n - 1;
        // D1
        int st1 = 0, st2 = 0;
        // D2
        int st3 = 0, st4 = 0;
        // D3
        int st5 = 0, st6 = 0;
        for(int u = 0; u < n; u++){
            st1 += arr[(k * n * n + i1 * n + j1)];
            st2 += arr[(k * n * n + i2 * n + j2)];
            st3 += arr[(i1 * n * n + k * n + j1)];
            st4 += arr[(i2 * n * n + k * n + j2)];
            st5 += arr[(j1 * n * n + i1 * n + k)];
            st6 += arr[(j2 * n * n + i2 * n + k)];
            i1++; i2++;
            j1++; j2--;
        }
        ans += unitDist(st1, c);
        ans += unitDist(st2, c);
        ans += unitDist(st3, c);
        ans += unitDist(st4, c);
        //ans += unitDist(st5, c);
        //ans += unitDist(st6, c);
    }
    return ans;
}

// From genetic.cpp
vector<int> makeRandomCube(int n) {
    random_device rd;
    mt19937 rng(rd());

    vector<int> cube;
    for(int i = 1; i <= n * n * n; i++){
        cube.push_back(i);
    }
    shuffle(begin(cube), std::end(cube), rng);
    for(int i = 0; i < cube.size(); i++){
        if(cube[i] == 63){
            swap(cube[i], cube[62]);
            break;
        }
    }

    return cube;
}

int32_t main(){
    //evalAnswer();
    cout << "Ukuran Kubus: ";
    cin >> n;
    cout << "Maksimal Sideways Move: ";
		cin >> max_side;
    auto beg = high_resolution_clock::now();
    c = n * (n * n * n + 1);
    c /= 2;

    vector<int> cube = makeRandomCube(n);
    vector<int> startingCube = cube;
    sumVec = distanceVec(cube);

    vector<int> ans;
    long long curDist = distance(cube);
    long long difference;
    int pos1, pos2;
    int steps = 0;
    int maxFail = 2e6;
    int minToRestart = 64;
    long long mini = LLONG_MAX;

    bool decreasingVal = true;

    ofstream logs("hill-climbing_log.txt");

    while(decreasingVal) {
				decreasingVal = false;
				for(int pos1 = 0; pos1 < cube.size(); pos1++) {
						for(int pos2 = pos1 + 1; pos2 < cube.size(); pos2++) {
								swap(cube[pos1], cube[pos2]);
								long long newDist = distance(cube);

								if(newDist < curDist) {
										curDist = newDist;

										if(curDist < mini) {
												ans = cube;
												mini = curDist;
										}
										decreasingVal = true;
								} else if(newDist == curDist && max_side > 0) {
										max_side--;
										curDist = newDist;
										if(curDist == mini) {
												ans = cube;
												mini = curDist;
										}
								} else {
										swap(cube[pos1], cube[pos2]);
								}
						}
				}
				steps++;
				cout << curDist << " " << steps << endl;
				logs << curDist << " " << steps << endl;
    }
    logs.close();

		ofstream sc("start_cube.txt");
		ofstream fc("final_cube.txt");

		for(auto &x: startingCube){
				sc << x << " ";
		}
		sc << endl;
		sc.close();

		for(auto &x: ans){
				fc << x << " ";
		}
		fc << endl;
		fc.close();

		cout << endl;
		cout << "Final objective function value: " << mini << endl;
		auto en = high_resolution_clock::now();
		auto dur = duration_cast<microseconds>(en - beg);
		cout << "Duration (in microsec): " << dur.count() << endl;

		system("python3 plot_cube.py start_cube.txt \"Starting Cube\"  && python3 plot_cube.py final_cube.txt \"Final Cube\"");

		///** Sesuaikan dengan sistem anda! **/
		system("python3 plot_annealing.py hill-climbing_log.txt I \"Objective function vs steps\"");

		return 0;
}
