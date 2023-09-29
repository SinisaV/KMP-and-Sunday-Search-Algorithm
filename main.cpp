#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef unsigned int uint;
bool BranjeStevil(vector<string> &A, const char *filename);
bool ZapisStevil(vector<int> &A, const char *filename);

vector<int> KMPNextTabela(const string& iskaniNiz);
vector<int> KMPIskanje(vector<string> text, const string& iskaniNiz);

vector<int> BCHTabela(const string& iskaniNiz);
vector<int> BCHIskanje(vector<string> text, const string& iskaniNiz);

int main(int argc, const char** argv) {

    if (argc != 5) {
        return 0;
    }

    vector<string> vectorA;
    BranjeStevil(vectorA, argv[4]);

    /*cout << "Text\n";
    for (const string& a : vectorA) {
        cout << a << " ";
    }
    cout << "\n";*/

    if (argv[2][0] == '0') {
        cout << "KMP ALGORITEM\n";

        /*cout << "kmpNext tabela\n";
        vector<int> result;
        result = KMPNextTabela(argv[2]);
        for (int r : result) {
            cout << r << " ";
        }
        cout << "\n";*/

        // cout << "KMP iskanje\n";
        vector<int> ujemanja;
        ujemanja = KMPIskanje(vectorA, argv[3]);
        for (int u : ujemanja) {
            cout << u << " ";
        }
        ZapisStevil(ujemanja, "out.txt");
    }

    else if (argv[2][0] == '1') {
        cout << "Sunday ALGORITEM\n";

        vector<int> ujemanjaBCH;
        ujemanjaBCH = BCHIskanje(vectorA, argv[3]);
        for (int u : ujemanjaBCH) {
            cout << u << " ";
        }
        ZapisStevil(ujemanjaBCH, "out.txt");
    }

    return 0;
}

bool BranjeStevil(vector<string> &A, const char *filename) {
    ifstream input(filename);
    string st;

    if (!input.is_open()) {
        return false;
    }

    while (getline(input, st)) {
        // beremo vrstice na koncu vsake vrstice dodamo se \n
        A.push_back(st + "\n");
    }

    input.close();

    return true;
}

bool ZapisStevil(vector<int> &A, const char *filename) {
    ofstream output(filename);

    if (!output.is_open()) {
        return false;
    }

    for (uint i = 0; i<A.size(); i++)
        output << A[i] << ' ';

    output.close();

    return true;
}

vector<int> KMPNextTabela(const string& iskaniNiz) {
    vector<int> kmpNext(iskaniNiz.size());
    // cout << kmpNext.size() << "\n";

    int n = iskaniNiz.size();

    kmpNext[0] = -1;

    if (n > 1) {
        kmpNext[1] = 0;

        int j = 0;

        // gremo skozi niz
        for (int i = 2; i < iskaniNiz.size(); i++) {
            // preverimo ce znaka nista enaka
            while (j >= 0 && iskaniNiz[i-1] != iskaniNiz[j]) {
                // j predstavlja dolzino najdaljse predpone
                j = kmpNext[j];
            }
            j++;
            kmpNext[i] = j;
        }
    }

    return kmpNext;
}

vector<int> KMPIskanje(vector<string> text, const string& iskaniNiz) {
    vector<int> kmpTabela = KMPNextTabela(iskaniNiz);
    vector<int> ujemanja;

    int m = iskaniNiz.size();

    string novi_text;
    for (const auto& str : text) {
        novi_text += str;
    }
    /*cout << novi_text.size() << endl;
    cout << novi_text << endl;*/

    int i = 0;
    int j = 0;
    while (i < novi_text.size()) {
        // i + j, da ne primerjamo ponovno istih znakov
        if (novi_text[i + j] == iskaniNiz[j]) {
            j++;
            if (j == m) {
                ujemanja.push_back(i);
                j = 0;
                i += m;
            }
        }
        else {
            i += j - kmpTabela[j];
            j = 0;
        }
    }
    return ujemanja;
}

vector<int> BCHTabela(const string& iskaniNiz) {
    int m = iskaniNiz.size();
    vector<int> bch(256, m + 1);

    for (int i = 0; i < m; i++) {
        // m - i => razdalja za katero se vzorec premakne v desno
        bch[iskaniNiz[i]] = m - i;
    }

    /*cout << endl;
    for (char c : {'A', 'B', 'C', 'D'}) {
        cout << "BCH[" << c << "] = " << bch[c] << endl;
    }*/

    return bch;
}

vector<int> BCHIskanje(vector<string> text, const string& iskaniNiz) {
    vector<int> bchTabela = BCHTabela(iskaniNiz);
    vector<int> ujemanja;

    int m = iskaniNiz.size();

    string novi_text;
    for (const auto& str : text) {
        novi_text += str;
    }

    int n = novi_text.size();

    int i = 0;
    int j = 0;
    while (i <= n - m) {
        if (novi_text[i + j] == iskaniNiz[j]) {
            j++;
            if (j == m) {
                ujemanja.push_back(i);
                j = 0;
                i += m;
            }
        }
        else {
            // cout << bchTabela[novi_text[i + m]] << " ";
            // premaknemo se na znak za iskanimNizom z dolzino m
            i += bchTabela[novi_text[i + m]];
            j = 0;
        }
    }
    return ujemanja;
}