#include <bits/stdc++.h>
#include <ctime>

using namespace std;
using namespace std::chrono;

int n, c;

// notation: https://drive.google.com/file/d/1GC2jjehBaVT8eMVL-qbUNi2qrkReFUAY/view?usp=sharing
// [R1, R2, R3, diagonal D1, diagonal D2, DR1, DR2, DR3, DR4]
vector<int> sumVec;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_real_distribution<double> distribution (0,1);

long long unitDist(long long x, long long c){
    return (x - c) * (x - c) * (x - c) * (x - c) * (x - c) * (x - c);
}

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

long long distanceEff(int pos1, int pos2, long long curDist, vector<int> &cube, vector<int> &sumVec){
    int i1, j1, k1;
    int i2, j2, k2;
    k1 = pos1 / (n * n);
    k2 = pos2 / (n * n);
    i1 = (pos1 / n) % n;
    i2 = (pos2 / n) % n;
    j1 = pos1 % n;
    j2 = pos2 % n;
    long long dE = curDist;
    long long bef1 = cube[k1 * n * n + i1 * n + j1];
    long long bef2 = cube[k2 * n * n + i2 * n + j2];
    dE -= unitDist(sumVec[k1 * 5 + i1], c);
    dE += unitDist(sumVec[k1 * 5 + i1] - bef1 + bef2, c);
    sumVec[k1 * 5 + i1] += bef2 - bef1;
    dE -= unitDist(sumVec[25 + k1 * 5 + j1], c);
    dE += unitDist(sumVec[25 + k1 * 5 + j1] - bef1 + bef2, c);
    sumVec[25 + k1 * 5 + j1] += bef2 - bef1;
    dE -= unitDist(sumVec[50 + i1 * 5 + j1], c);
    dE += unitDist(sumVec[50 + i1 * 5 + j1] - bef1 + bef2, c);
    sumVec[50 + i1 * 5 + j1] += bef2 - bef1;

    dE -= unitDist(sumVec[k2 * 5 + i2], c);
    dE += unitDist(sumVec[k2 * 5 + i2] - bef2 + bef1, c);
    sumVec[k2 * 5 + i2] += bef1 - bef2;
    dE -= unitDist(sumVec[25 + k2 * 5 + j2], c);
    dE += unitDist(sumVec[25 + k2 * 5 + j2] - bef2 + bef1, c);
    sumVec[25 + k2 * 5 + j2] += bef1 - bef2;
    dE -= unitDist(sumVec[50 + i2 * 5 + j2], c);
    dE += unitDist(sumVec[50 + i2 * 5 + j2] - bef2 + bef1, c);
    sumVec[50 + i2 * 5 + j2] += bef1 - bef2;

    // D1
    if(i1 == j1){
        dE -= unitDist(sumVec[75 + 2 * k1], c);
        dE += unitDist(sumVec[75 + 2 * k1] - bef1 + bef2, c);
        sumVec[75 + 2 * k1] += bef2 - bef1;
    }
    if(i1 + j1 == n - 1){
        dE -= unitDist(sumVec[75 + 2 * k1 + 1], c);
        dE += unitDist(sumVec[75 + 2 * k1 + 1] - bef1 + bef2, c);
        sumVec[75 + 2 * k1 + 1] += bef2 - bef1;
    }
    // D2
    if(j1 == k1){
        dE -= unitDist(sumVec[85 + 2 * i1], c);
        dE += unitDist(sumVec[85 + 2 * i1] - bef1 + bef2, c);
        sumVec[85 + 2 * i1] += bef2 - bef1;
    }
    if(j1 + k1 == n - 1){
        dE -= unitDist(sumVec[85 + 2 * i1 + 1], c);
        dE += unitDist(sumVec[85 + 2 * i1 + 1] - bef1 + bef2, c);
        sumVec[85 + 2 * i1 + 1] += bef2 - bef1;
    }

    // D1
    if(i2 == j2){
        dE -= unitDist(sumVec[75 + 2 * k2], c);
        dE += unitDist(sumVec[75 + 2 * k2] - bef2 + bef1, c);
        sumVec[75 + 2 * k2] += bef1 - bef2;
    }
    if(i2 + j2 == n - 1){
        dE -= unitDist(sumVec[75 + 2 * k2 + 1], c);
        dE += unitDist(sumVec[75 + 2 * k2 + 1] - bef2 + bef1, c);
        sumVec[75 + 2 * k2 + 1] += bef1 - bef2;
    }
    // D2
    if(j2 == k2){
        dE -= unitDist(sumVec[85 + 2 * i2], c);
        dE += unitDist(sumVec[85 + 2 * i2] - bef2 + bef1, c);
        sumVec[85 + 2 * i2] += bef1 - bef2;
    }
    if(j2 + k2 == n - 1){
        dE -= unitDist(sumVec[85 + 2 * i2 + 1], c);
        dE += unitDist(sumVec[85 + 2 * i2 + 1] - bef2 + bef1, c);
        sumVec[85 + 2 * i2 + 1] += bef1 - bef2;
    }

    // DR1
    if(i1 == j1 && j1 == k1){
        dE -= unitDist(sumVec[95], c);
        dE += unitDist(sumVec[95] - bef1 + bef2, c);
        sumVec[95] += bef2 - bef1;
    }
    // DR2
    if(i1 == k1 && i1 + j1 == n - 1){
        dE -= unitDist(sumVec[96], c);
        dE += unitDist(sumVec[96] - bef1 + bef2, c);
        sumVec[96] += bef2 - bef1;
    }
    // DR3
    if(j1 == k1 && i1 + j1 == n - 1){
        dE -= unitDist(sumVec[97], c);
        dE += unitDist(sumVec[97] - bef1 + bef2, c);
        sumVec[97] += bef2 - bef1;
    }
    // DR4
    if(i1 == j1 && i1 + k1 == n - 1){
        dE -= unitDist(sumVec[98], c);
        dE += unitDist(sumVec[98] - bef1 + bef2, c);
        sumVec[98] += bef2 - bef1;
    }

    // DR1
    if(i2 == j2 && j2 == k2){
        dE -= unitDist(sumVec[95], c);
        dE += unitDist(sumVec[95] - bef2 + bef1, c);
        sumVec[95] += bef1 - bef2;
    }
    // DR2
    if(i2 == k2 && i2 + j2 == n - 1){
        dE -= unitDist(sumVec[96], c);
        dE += unitDist(sumVec[96] - bef2 + bef1, c);
        sumVec[96] += bef1 - bef2;
    }
    // DR3
    if(j2 == k2 && i2 + j2 == n - 1){
        dE -= unitDist(sumVec[97], c);
        dE += unitDist(sumVec[97] - bef2 + bef1, c);
        sumVec[97] += bef1 - bef2;
    }
    // DR4
    if(i2 == j2 && i2 + k2 == n - 1){
        dE -= unitDist(sumVec[98], c);
        dE += unitDist(sumVec[98] - bef2 + bef1, c);
        sumVec[98] += bef1 - bef2;
    }
    return dE;
}


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

double getProbability(long long difference, double temperature){
    return exp(-1 * difference / temperature);
}

int32_t main(){
    cout << "Type 5 and hit Enter to start." << endl;
    cin >> n;
    auto beg = high_resolution_clock::now();
    c = n * (n * n * n + 1);
    c /= 2;
    random_device rd;
    mt19937 rng(rd());

    vector<int> cube;
    for(int i = 1; i <= n * n * n; i++){
        cube.push_back(i);
    }
    shuffle(begin(cube), std::end(cube), rng);
    sumVec = distanceVec(cube);

    uniform_int_distribution<mt19937::result_type> dist1(0, n * n * n - 1);
    uniform_int_distribution<mt19937::result_type> dist2(0, n * n * n - 2);

    vector<int> ans;
    vector<int> startingCube = cube;
    long long curDist = distance(cube);
    double temperature = 1e11, coolingRate = 0.9999993, constTemp = 5, absoluteZero = 1e-7;
    long long difference;
    int pos1, pos2;
    int steps = 0;
    int maxFail = 2e6;
    int minToRestart = 64;
    int stuck = 0;
    long long mini = LLONG_MAX;

    ofstream logs("annealing_log.txt");
    ofstream delog("annealing_delta_e_log.txt");

    for(; temperature > absoluteZero && curDist != 0; temperature *= coolingRate){
        pos1 = dist1(rng);
        pos2 = dist2(rng);
        if(pos2 >= pos1) pos2++;
        int x1 = cube[pos1], x2 = cube[pos2];
        long long testingDist = distanceEff(pos1, pos2, curDist, cube, sumVec);

        swap(cube[pos1], cube[pos2]);

        long long newDist = testingDist;
        difference = newDist - curDist;
        double currentdE = 1;

        if(difference > 0){
            currentdE = getProbability(difference, temperature);
            stuck++;
        }

        if(difference < 0 or (difference > 0 and currentdE > double(distribution(generator)))) {
            curDist = newDist;
            if(mini > curDist){
                ans = cube;
                mini = curDist;
            }
        }else{
            distanceEff(pos1, pos2, testingDist, cube, sumVec);
            swap(cube[pos1], cube[pos2]);
        }

        if(steps % 1000000 == 0){
            cout << curDist << " " << steps << endl;
            logs << curDist << " " << steps << endl;
            delog << currentdE << " " << steps << endl;
        }
        steps++;
    }
    auto en = high_resolution_clock::now();
    assert(distance(ans) == mini);
    logs.close();
    delog.close();

    cout << endl;
    cout << "Final objective function value: " << mini << endl;
    cout << "Stuck frequency: " << stuck << endl;
    auto dur = duration_cast<microseconds>(en - beg);
    cout << "Duration (in microsec): " << dur.count() << endl;

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


    system("C:/Python312/python.exe plot_cube.py start_cube.txt \"Starting Cube\"  && C:/Python312/python.exe plot_cube.py final_cube.txt \"Final Cube\"");

    int u = 1;

    ///** Sesuaikan dengan sistem anda! **/
    system("C:/Python312/python.exe plot_annealing.py annealing_log.txt I \"Objective function vs steps\" && C:/Python312/python.exe plot_annealing.py annealing_delta_e_log.txt F \"e^delta E/T vs steps\"");

    while(u != 2){ cin >> u; }
    return 0;
}
