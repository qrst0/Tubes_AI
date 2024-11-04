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

long long unitDist(long long x, long long c, int srs = 0){
    /*
    if(srs){
        return (x - c) * (x - c);
    }
    if(abs(x - c) <= n) return 0;*/
    //return x != c;
    return (x - c) * (x - c) * (x - c) * (x - c) * (x - c) * (x - c);
}

long long distanceMat(vector<int> arr, int srs = 0){
    vector<int> sumHor(n, 0);
    vector<int> sumVer(n, 0);
    assert(arr.size() == n * n);
    for(int i = 0; i < n * n; i++){
        sumHor[i / n] += arr[i];
        sumVer[i % n] += arr[i];
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans += unitDist(sumHor[i], c, srs);
        ans += unitDist(sumVer[i], c, srs);
    }
    return ans;
}

vector<int> distanceMatVec(vector<int> arr, int srs = 0){
    vector<int> sumHor(n, 0);
    vector<int> sumVer(n, 0);
    assert(arr.size() == n * n);
    for(int i = 0; i < n * n; i++){
        sumHor[i / n] += arr[i];
        sumVer[i % n] += arr[i];
    }
    sumHor.insert(sumHor.end(), sumVer.begin(), sumVer.end());
    return sumHor;
}

vector<int> distanceVec(vector<int> arr, int srs = 0){
    vector<int> sumPillar(n * n, 0);
    vector<int> ans;
    for(int i = 0; i < arr.size(); i += n * n){
        vector<int> temp;
        vector<int> sumHor(n, 0);
        for(int j = i; j < i + n * n; j++){
            sumPillar[j % (n * n)] += arr[j];
            sumHor[(j / n) % n] += arr[j];
        }
        //vector<int> dm = distanceMatVec(temp, srs);
        ans.insert(ans.end(), sumHor.begin(), sumHor.end());
    }
    for(int i = 0; i < arr.size(); i += n * n){
        vector<int> temp;
        vector<int> sumVer(n, 0);
        for(int j = i; j < i + n * n; j++){
            sumVer[j % n] += arr[j];
        }
        //vector<int> dm = distanceMatVec(temp, srs);
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

long long distanceEff(int pos1, int pos2, long long curDist, vector<int> cube, vector<int> &sumVec){
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


long long distance(vector<int> &arr, int srs = 0){
    int cnt = 0;
    vector<int> sumPillar(n * n, 0);
    long long ans = 0;
    for(int i = 0; i < arr.size(); i += n * n){
        vector<int> temp;
        for(int j = i; j < i + n * n; j++){
            sumPillar[j % (n * n)] += arr[j];
            temp.push_back(arr[j]);
        }
        ans += distanceMat(temp, srs);
    }
    for(int i = 0; i < n * n; i++){
        ans += unitDist(sumPillar[i], c, srs);
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
    ans += unitDist(s1, c, srs);
    ans += unitDist(s2, c, srs);
    ans += unitDist(s3, c, srs);
    ans += unitDist(s4, c, srs);
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
        ans += unitDist(st1, c, srs);
        ans += unitDist(st2, c, srs);
        ans += unitDist(st3, c, srs);
        ans += unitDist(st4, c, srs);
        //ans += unitDist(st5, c, srs);
        //ans += unitDist(st6, c, srs);
    }
    return ans;
}

double getRandomNumber(double min,double max){
    random_device rd;
    mt19937 rng(rd());

    uniform_real_distribution<double> distribution(min, max);

    return double(distribution(rng));
}

int getRandomInt(int mini, int maxi){
    random_device dev;
    mt19937 rng(dev());

    uniform_int_distribution<mt19937::result_type> dist(mini, maxi);
    return dist(rng);
}

void evalAnswer(){
    cin >> n;
    vector<int> arr(n * n * n);
    for(auto &x: arr) cin >> x;
    int mini = INT_MAX;
    c = n * (n * n * n + 1);
    c /= 2;
    int u = distance(arr);
    for(int i = 0; i < n * n * n; i++){
        for(int j = i + 1; j < n * n * n; j++){
            swap(arr[i], arr[j]);
            int k = distance(arr);
            mini = min(mini, k);
            swap(arr[i], arr[j]);
        }
    }
    for(auto &x: distanceVec(arr)){
        cout << x << " ";
    }
    cout << endl;
    cout << u << endl;
    cout << endl << " " << mini << endl;
}

// utility func
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

void printCube(vector<int> cube) {
    for (int i = 0; i < cube.size(); i++) {
        cout << cube[i] << " ";
    }
    cout << "\n";
}

vector<vector<int>> makePopulation(int nPop, int n) {
    vector<vector<int>> population;

    for (int i = 0; i < nPop; i++) {
        vector<int> cube = makeRandomCube(n);
        population.push_back(cube);
    }

    return population;
}

vector<vector<int>> selection(vector<vector<int>> population) {
    double total = 0;
    vector<double> fitnessArr;
    for (int i = 0; i < population.size(); i++) {
        vector<int> cube = population[i];
        double fitness = distance(cube);    // fitness function
        // cout << "Fitness[" << i << "]: " << fitness << "\n";

        total += fitness;
        fitnessArr.push_back(fitness);
    }
    // cout << "Total: " << total << "\n";

    double totalRev = 0;
    vector<double> fitnessArrRev;
    for (int i = 0; i < population.size(); i++) {
        double fitness = total-fitnessArr[i];;    // fitness function
        // cout << "Fitness[" << i << "]: " << fitness << "\n";

        totalRev += fitness;
        fitnessArrRev.push_back(fitness);
    }
    // cout << "Total: " << totalRev << "\n";

    // cout << "Boundaries: \n";
    vector<double> boundaries; 
    for (int i = 0; i < population.size(); i++) {
        double fitness = fitnessArrRev[i];
        double portion = fitness/totalRev;

        if (i == 0) {
            boundaries.push_back(portion);   
        } else {
            boundaries.push_back(boundaries[i-1]+portion);
        }
        // cout << fitness << "::";
        // cout << boundaries[i] << " ";
    }
    // cout << "\n";

    vector<vector<int>> selection;
    for (int i = 0; i < population.size(); i++) {
        int min = 0;
        int max = 100;
        double x = getRandomInt(min, max)/100.0;
        // cout << "Random Select: " << x << " ";

        bool found = false;
        int j = 0;
        while (!found && j < boundaries.size())
        {
            if (x <= boundaries[j]) {
                selection.push_back(population[j]);
                found = true;
            }
            j++;
        }

        if (!found && x == 1) {
            selection.push_back(population[population.size()-1]);
        }
    }

    return selection;
}

vector<vector<int>> crossOver(vector<vector<int>> population) {
    // cross over using ordered cross over
    int nPop = population.size();

    if (nPop % 2 == 1) { // if population is odd
        // one-sided crossover
        int point1 = getRandomInt(0, n*n*n-2);
        int point2 = getRandomInt(0, n*n*n-2);  
        int start = min(point1, point2);
        int end = max(point1, point2);

        vector<int> parent1 = population[nPop-2];
        vector<int> parent2 = population[nPop-1];
        vector<int> slice(parent1.begin()+start, parent1.begin()+end+1);
        vector<int> child;

        // cross over to child
        int j = 0; // iterator for parent
        int p = 0; // iterator for next element to add
        int q = 0; // iterator for slice
        while (j < parent2.size() && p < parent2.size()) {
            // if between start and end, append slice
            if (p >= start && p <= end) {
                child.push_back(slice[q]);
                p++;
                q++;
                continue;
            }

            int num = parent2[j];
            auto it = find(slice.begin(), slice.end(), num);
            if (it != slice.end()) { // if slice contains num (duplicate), skip
                j++;
                continue;
            }

            // else add num to child
            child.push_back(num);
            p++;
            j++;
        }

        population[nPop-1] = child;
    }

    for (int i = 0; i < nPop-(nPop%2) // == nPop % 2 == 1 ? nPop-1 : nPop
    ; i += 2) {
        int point1 = getRandomInt(0, n*n*n-2);
        int point2 = getRandomInt(0, n*n*n-2);  
        int start = min(point1, point2);
        int end = max(point1, point2);
        // cout << "POINT: " << start << " " << end << endl;

        vector<int> parent1 = population[i];
        vector<int> parent2 = population[i+1];
        vector<int> slice1(parent2.begin()+start, parent2.begin()+end+1);
        vector<int> slice2(parent1.begin()+start, parent1.begin()+end+1);
        vector<int> child1;
        vector<int> child2;

        // cout << "PARENT-1: ";
        // for(int a = 0; a < parent1.size(); a++) {
        //     cout << parent1[a] << " ";
        // }
        // cout << endl;
        // cout << "PARENT-2: ";
        // for(int a = 0; a < parent2.size(); a++) {
        //     cout << parent2[a] << " ";
        // }
        // cout << endl;
        // cout << "SLICE-1: ";
        // for(int a = 0; a < slice1.size(); a++) {
        //     cout << slice1[a] << " ";
        // }
        // cout << endl;
        // cout << "SLICE-2: ";
        // for(int a = 0; a < slice2.size(); a++) {
        //     cout << slice2[a] << " ";
        // }
        // cout << endl;

        // cross over to child 1
        int j = 0; // iterator for parent
        int p = 0; // iterator for next element to add
        int q = 0; // iterator for slice
        while (j < parent1.size() && p < parent1.size()) {
            // if between start and end, append slice
            if (p >= start && p <= end) {
                child1.push_back(slice1[q]);
                p++;
                q++;
                continue;
            }

            int num = parent1[j];
            auto it = find(slice1.begin(), slice1.end(), num);
            if (it != slice1.end()) { // if slice contains num (duplicate), skip
                j++;
                continue;
            }

            // else add num to child
            child1.push_back(num);
            p++;
            j++;
        }

        // cross over to child 2
        j = 0; // iterator for parent
        p = 0; // iterator for next element to add
        q = 0; // iterator for slice
        while (j < parent2.size() && p < parent2.size()) {
            // if between start and end, append slice
            if (p >= start && p <= end) {
                child2.push_back(slice2[q]);
                p++;
                q++;
                continue;
            }

            int num = parent2[j];
            auto it = find(slice2.begin(), slice2.end(), num);
            if (it != slice2.end()) { // if slice contains num (duplicate), skip
                j++;
                continue;
            }


            // else add num to child
            child2.push_back(num);
            p++;
            j++;
        }

        population[i] = child1;
        population[i+1] = child2;

        // cout << "CHILD-1: ";
        // for(int a = 0; a < population[i].size(); a++) {
        //     cout << population[i][a] << " ";
        // }
        // cout << endl;
        // cout << "CHILD-2: ";
        // for(int a = 0; a < population[i+1].size(); a++) {
        //     cout << population[i+1][a] << " ";
        // }
        // cout << endl;
    }

    return population;
}

vector<vector<int>> mutation(vector<vector<int>> population) {
    for (int i = 0; i < population.size(); i++) {
        int y = getRandomInt(1, n*n*n-1); // num of mutations

        for (int j = 0; j < y; j++) {
            int x = getRandomInt(1, 100);

            if (x < 5) { // 5 chance
                int pos1 = getRandomInt(0, n * n * n - 1);
                int pos2 = getRandomInt(0, n * n * n - 1);
                while(pos1 == pos2 || pos1 == 62 || pos2 == 62){
                    pos1 = getRandomInt(0, n * n * n - 1);
                    pos2 = getRandomInt(0, n * n * n - 1);
                }

                for (int j = 0; j < population.size(); j++) {
                    swap(population[j][pos1], population[j][pos2]);
                }
            }
        }
    }

    return population;
}

long long findOptimum(vector<vector<int>> population) {
    long long optimum = distance(population[0]);

    for (int i = 1; i < population.size(); i++) {
        long long fitness = distance(population[i]);
        if (fitness < optimum) {
            optimum = fitness;
        }
    }

    return optimum;
}

long long findAverage(vector<vector<int>> population) {
    long long average = 0;

    for (int i = 0; i < population.size(); i++) {
        long long fitness = distance(population[i]);
        average += fitness;
    }

    return average/population.size();
}

int32_t main(){
    //evalAnswer();
    cout << "Ukuran Kubus: ";
    cin >> n;

    int nPop;
    cout << "Banyak Populasi: ";
    cin >> nPop;

    int maxIter;
    cout << "Banyak Iterasi: ";
    cin >> maxIter;
    auto beg = high_resolution_clock::now();
    c = n * (n * n * n + 1);
    c /= 2;

    // make the cube
    vector<vector<int>> population = makePopulation(nPop, n);
    cout << "Start Population: \n";
    for (int i = 0; i < population.size(); i++) {
        printCube(population[i]);
    }
    
    for (int i = 0; i < population.size(); i++) {
        long long fitness = distance(population[i]);

        cout << "Fitness Cube " << i+1 << ": " << fitness << "\n";
    }
    long long averageStart = findAverage(population);
    cout << "Average Fitness: " << averageStart << endl;
    long long optimumStart = findOptimum(population);
    cout << "Optimum: " << optimumStart << endl;

    ofstream logs("genetic_log.txt");
    logs << optimumStart << " " << averageStart << " " << 0 << endl;

    for (int itr = 0; itr < maxIter; itr++){
        // selection
        // cout << "Selection: \n";
        
        vector<vector<int>> selectionRes = selection(population);
        
        // for (int i = 0; i < selectionRes.size(); i++) {
        //     printCube(selectionRes[i]);
        // }

        // Cross-Over
        // cout << "Cross Over: \n";

        vector<vector<int>> crossOverRes = crossOver(selectionRes);
        
        // for (int i = 0; i < crossOverRes.size(); i++) {
        //     printCube(crossOverRes[i]);
        // }

        // mutation
        // cout << "Mutation: \n";

        vector<vector<int>> mutationRes = mutation(crossOverRes);

        // for (int i = 0; i < mutationRes.size(); i++) {
        //     cout << "Cube-" << i << ":\n";
        //     printCube(mutationRes[i]);
        // }

        // for (int i = 0; i < mutationRes.size(); i++) {
        //     cout << "Cube " << i << ": " << distance(mutationRes[i]) << "\n";
        // }

        // Redo iteration
        population = mutationRes;

        if (itr > 0 && itr != maxIter-1 && (itr+1) % 20 == 0) {
            cout << "Iteration-" << itr+1 << ": \n";
            // cout << "Population: \n";
            // for (int i = 0; i < population.size(); i++) {
            //     printCube(population[i]);
            //     cout << "Fitness Cube " << i+1 << ": " << distance(population[i]) << "\n";
            // }

            long long averageItr = findAverage(population);
            cout << "Average Fitness: " << averageItr << endl;

            long long optimumItr = findOptimum(population);
            cout << "Optimum: " << optimumItr << endl;

            logs << optimumItr << " " << averageItr << " " << itr+1 << endl;
        }
    }

    cout << "Final Population: \n";
    for (int i = 0; i < population.size(); i++) {
        printCube(population[i]);
    }

    for (int i = 0; i < population.size(); i++) {
        cout << "Fitness Cube " << i+1 << ": " << distance(population[i]) << "\n";
    }

    long long averageEnd = findAverage(population);
    cout << "Average Fitness: " << averageEnd << endl;

    long long optimumEnd = findOptimum(population);
    cout << "Optimum: " << optimumEnd << endl;

    logs << optimumEnd << " " << averageEnd << " " << maxIter << endl;

    auto en = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(en - beg);
    cout << "Duration (in microsec): " << dur.count() << endl;
    
    ///** Sesuaikan dengan sistem anda! **/
    system("C:/Python312/python.exe plot_genetic.py genetic_log.txt I log");\

    int u = 1;
    while(u != 2){ cin >> u; }
    return 0;
}
