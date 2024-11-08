#include <bits/stdc++.h>

using namespace std;

tuple<vector<float>, vector<float>, vector<vector<float>>> input() {
    vector<float> S, d, b;
    vector<vector<float>> C;

    string s;
    int n;

    //the coefficients of supply
    while (true) {
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        stringstream ss(s);
        while (ss >> n) {
            S.push_back(n);
        }
    }

    //the coefficients of demand
    while (true) {
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        stringstream ss(s);
        while (ss >> n) {
            d.push_back(n);
        }
    }

    // the cost matrix C
    while (true) {
        getline(cin, s);
        if (s.empty()) {
            break;
        }

        stringstream ss(s);
        while (ss >> n) {
            b.push_back(n);
        }
        C.push_back(b);
        b.clear();
    }

    return {S, d, C};
}

void format_print (const vector<float> &S, const vector<float> &d, const vector<vector<float>> &C) {
    float sum = 0;
    for (int i = 0; i < C.size(); i++) {
        cout << std::setw(9) << "r" << i + 1; 
        for (int j = 0; j < C[i].size(); j++) {
            cout << std::setw(5) << C[i][j];
        }
        cout<< std::setw(7) << S[i] << endl;
    }
    cout << std::setw(10) <<"Demand"; 
    for (int i = 0; i < d.size(); i++) {
        sum += d[i]; 
        cout << std::setw(5) << d[i];
    }
    cout<< std::setw(7) << sum << endl;
    cout << endl;
}

//all values are positive and not all are zeros (if methods applicalable)
int check (const vector<float> &S, const vector<float> &d, const vector<vector<float>> &C){
    int k = 0;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] < 0) {
            return 0;
        }
        if (S[i] > 0) {
            k = 1;
        }
    }
    if (k == 0) {
        return 0;
    }
    for (int i = 0; i < d.size(); i++) {
        if (d[i] < 0) {
            return 0;
        }
        if (d[i] > 0) {
            k = 1;
        }
    }
    if (k == 0) {
        return 0;
    }
    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[i].size(); j++) {
            if (C[i][j] < 0) {
                return 0;
            }
            if (C[i][j] > 0) {
                k = 1;
            }
        }
    }
    if (k == 0) {
        return 0;
    }
    return 1;
}

//is problem balanced or not
int balanced (const vector<float> &S, const vector<float> &d) {
    int s1 = 0, s2 = 0;
    for (int i = 0; i < S.size(); i++) {
        s1 += S[i];
        s2 += d[i];
    }
    if (s1 != s2) {
        return 0;
    }
    return 1;
}

//North-West corner method
float northwest (const vector<float> &S, const vector<float> &d, const vector<vector<float>> &C) {
    vector<vector<float>> x(S.size(), vector<float>(d.size(), 0));
    vector<float> s = S;
    vector<float> D = d;
    int row = 0;
    int col = 0;
    while (row < s.size() && col < D.size()) {
        if (s[row] < D[col]) {
            x[row][col] = s[row];
            D[col] -= s[row];
            s[row] = 0;
        } 
        else{
            if (s[row] > D[col]) {
                x[row][col] = D[col];
                s[row] -= D[col];
                D[col] = 0;
            }
            else {
                x[row][col] = s[row];
                s[row] = 0;
                D[col] = 0;
            }
        }

        if (s[row] == 0) {
            row++;
        }
        if (D[col] == 0) {
            col++;
        }
    }

    vector<vector<float>> c = C;
    float cost = 0;
    for (int row = 0; row < x.size(); row++) {
        for (int col = 0; col < x[row].size(); col++) {
            cost += x[row][col] * c[row][col];
        }
    }
    format_print(S, d, x);
    cout << "Total cost:";
    return cost;
}

//Russell’s approximation method
float russell (const vector<float> &S, const vector<float> &d, const vector<vector<float>> &C) {
    vector<vector<float>> x(S.size(), vector<float>(d.size(), 0));
    vector<vector<float>> c = C;
    vector<float> s = S;
    vector<float> D = d;
    while (accumulate(s.begin(), s.end(), 0) != 0 && accumulate(d.begin(), d.end(), 0) != 0) {
        vector<int> max_row(s.size(), 0);
        vector<int> max_col(d.size(), 0);
        
        for (int row = 0; row < s.size(); row++) {
            if (s[row] == 0) {
                continue;
            }
            for (int col = 0; col < D.size(); col++) {
                if (D[col] == 0) {
                    continue;
                }
                if (c[row][col] > max_row[row]) {
                    max_row[row] = c[row][col];
                }
                if (c[row][col] > max_col[col]) {
                    max_col[col] = c[row][col];
                }
            }
        }
        int max_diff = 0;
        int row = 0, col = 0;
        bool found = false;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 0) {
                continue;
            }
            for (int j = 0; j < d.size(); j++) {
                if (D[j] == 0) {
                    continue;
                }
                int diff = c[i][j] - max_row[i] - max_col[j];
                if (!found || diff < max_diff) {
                    max_diff = diff;
                    row = i;
                    col = j;
                    found = true;
                }
            }
        }

        if (s[row] < D[col]) {
            x[row][col] = s[row];
            D[col] -= s[row];
            s[row] = 0;
        } else if (s[row] > D[col]) {
            x[row][col] = D[col];
            s[row] -= D[col];
            D[col] = 0;
        } else {
            x[row][col] = s[row];
            s[row] = 0;
            D[col] = 0;
        }
    }

    c = C;
    float cost = 0;
    for (int row = 0; row < x.size(); row++) {
        for (int col = 0; col < x[row].size(); col++) {
            cost += x[row][col] * c[row][col];
        }
    }
    format_print(S, d, x);
    cout << "Total cost:";
    return cost;
   
}

//Vogel’s approximation method
float vogel (const vector<float> &S, const vector<float> &d, const vector<vector<float>> &C) {
    vector<vector<float>> x(S.size(), vector<float>(d.size(), 0));
    vector<vector<float>> c = C;
    vector<float> s = S;
    vector<float> D = d;


    while (accumulate(s.begin(), s.end(), 0) != 0 && accumulate(D.begin(), D.end(), 0) != 0) {
        vector<int> diff_row(s.size(), 0);
        for (size_t row = 0; row < s.size(); ++row) {
            if (s[row] == 0) {
                diff_row[row] = -1;
                continue;
            }
            int min1 = numeric_limits<int>::max();
            int min2 = numeric_limits<int>::max();
            for (size_t col = 0; col < D.size(); ++col) {
                if (D[col] == 0) {
                    continue;
                }
                if (c[row][col] < min1) {
                    min2 = min1;
                    min1 = c[row][col];
                } else if (c[row][col] < min2) {
                    min2 = c[row][col];
                }
            }

            if (min1 == -1) {
                diff_row[row] = numeric_limits<int>::max();
            } else if (min2 == numeric_limits<int>::max()) {
                diff_row[row] = min1;
            } else {
                diff_row[row] = min2 - min1;
            }
        }

        std::vector<int> diff_col(D.size(), 0);
        for (size_t col = 0; col < D.size(); ++col) {
            if (D[col] == 0) {
                diff_col[col] = -1;
                continue;
            }
            int min1 = numeric_limits<int>::max();
            int min2 = numeric_limits<int>::max();
            for (size_t row = 0; row < s.size(); ++row) {
                if (s[row] == 0) {
                    continue;
                }
                if (c[row][col] < min1) {
                    min2 = min1;
                    min1 = c[row][col];
                } else if (c[row][col] < min2) {
                    min2 = c[row][col];
                }
            }

            if (min1 == -1) {
                diff_col[col] = numeric_limits<int>::max();
            } else if (min2 == numeric_limits<int>::max()) {
                diff_col[col] = min1;
            } else {
                diff_col[col] = min2 - min1;
            }
        }

        int max_diff_row = *max_element(diff_row.begin(), diff_row.end());
        int max_diff_col = *max_element(diff_col.begin(), diff_col.end());
        size_t row, col;

        if (max_diff_row > max_diff_col) {
            row = distance(diff_row.begin(), find(diff_row.begin(), diff_row.end(), max_diff_row));
            col = numeric_limits<size_t>::max();
            for (size_t i = 0; i < c[row].size(); ++i) {
                if (D[i] == 0) {
                    continue;
                }
                if (col == numeric_limits<size_t>::max() || c[row][i] < c[row][col]) {
                    col = i;
                }
            }
        } else {
            col = distance(diff_col.begin(), find(diff_col.begin(), diff_col.end(), max_diff_col));
            row = numeric_limits<size_t>::max();
            for (size_t i = 0; i < c.size(); ++i) {
                if (s[i] == 0) {
                    continue;
                }
                if (row == numeric_limits<size_t>::max() || c[i][col] < c[row][col]) {
                    row = i;
                }
            }
        }

        if (s[row] < D[col]) {
            x[row][col] = s[row];
            D[col] -= s[row];
            s[row] = 0;

            for (size_t i = 0; i < D.size(); ++i) {
                c[row][i] = 0;
            }
        } else if (s[row] > D[col]) {
            x[row][col] = D[col];
            s[row] -= D[col];
            D[col] = 0;

            for (size_t i = 0; i < s.size(); ++i) {
                c[i][col] = 0;
            }
        } else {
            x[row][col] = s[row];
            s[row] = 0;
            D[col] = 0;

            for (size_t i = 0; i < D.size(); ++i) {
                c[row][i] = 0;
            }

            for (size_t i = 0; i < s.size(); ++i) {
                c[i][col] = 0;
            }
        }
    }
    c = C;
    float cost = 0;
    for (int row = 0; row < x.size(); row++) {
        for (int col = 0; col < x[row].size(); col++) {
            cost += x[row][col] * c[row][col];
        }
    }
    format_print(S, d, x);
    cout << "Total cost:";
    return cost;
}

int main() {
    auto [S, d, C] = input();

    if(check(S, d, C) == 0){
        cout << "The method is not applicable:()";
        return 0;
    }

    if(balanced(S, d) == 0){
        cout << "The problem is not balanced:()";
        return 0;
    }
    cout << "Transportation problem:"<< endl;
    format_print(S, d, C);
    cout << "Russell’s approximation method:\n"  << russell(S, d, C) << endl;
    cout << "Vogel’s approximation method:\n"<< vogel(S, d, C) << endl;
    cout << "North-West corner method:\n" << northwest(S, d, C) << endl;

    return 0;
}
