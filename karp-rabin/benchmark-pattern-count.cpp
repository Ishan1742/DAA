#include <bits/stdc++.h>
using namespace std;

long long int hash_func(string pattern, int prime, int multiplier, int limit)
{
    long long int hash = 0;
    for (int i=0; i<limit; i++)
    {
        hash = (hash * multiplier + pattern[i]) % prime;
    }

    return hash;
}

long long int bench_rabin_karp(string text_string, vector<string> patterns) {
	long long int count = 0;
    
    int p = int(1e9) + 7;
    int x = rand() % (p - 1) + 1;

    int k = INT_MAX;
    for(int i=0; i<patterns.size(); i++)
    {
        if(patterns[i].length() < k)
            k = patterns[i].length();
    }

    map<long long int, vector<string>> pattern_hash;
    for(long long int i=0; i<patterns.size(); i++)
    {
        long long int pHash = hash_func(patterns[i], p, x, k);

        if(pattern_hash.find(pHash) != pattern_hash.end())
        {
            vector<string> v = pattern_hash[pHash];
            v.push_back(patterns[i]);
            pattern_hash.insert(pair<long long int, vector<string>> (pHash, v));
        }
        else
        {
            vector<string> v;
            v.push_back(patterns[i]);
            pattern_hash.insert(pair<long long int, vector<string>> (pHash, v));
        }
        //cout<<pHash<<" "<<patterns[i]<<"\n";
    }

    //cout<<"\n";

    for(long long int i = 0; i < text_string.length() - k + 1; i++)
    {
        long long int tHash = hash_func(text_string.substr(i, k), p, x, k);

        //cout<<tHash<<" "<<text_string.substr(i, k)<<"\n";

        if( pattern_hash.find(tHash) != pattern_hash.end())
        {
            vector<string> match = pattern_hash[tHash];
            for(int j=0; j<match.size(); j++)
            {
                //cout<<match[j]<<" "<<text_string.substr(i, match[j].length())<<"\n";
                if(match[j] == text_string.substr(i, match[j].length()))
                {
                    count++;
                }
            }
        }
    }

	return count;
}

int main() {

	map<size_t, tuple<chrono::high_resolution_clock::duration, chrono::high_resolution_clock::duration>> timings;

    fstream ft;
    ft.open("../tests/pattern-count/text_0.txt");
    string text;
    ft >> text;
    ft.close();
    for (int i = 0; i < 100; i++)
    {
        set<string> patterns;
        fstream fp;
        fp.open("../tests/pattern-count/pattern_" + to_string(i) + ".txt");
        while(fp.good())
        {
            string a;
            fp >> a;
            patterns.insert(a);
        }
        vector<string> pattern_vector(patterns.begin(), patterns.end());
	    

        cout << "Running loop: " + to_string(i);
		auto start_time = chrono::high_resolution_clock::now();
		auto end_time = chrono::high_resolution_clock::now();
		auto time_1 = end_time - start_time;

		start_time = chrono::high_resolution_clock::now();
		size_t count_2 = bench_rabin_karp(text, pattern_vector);
		end_time = chrono::high_resolution_clock::now();
		auto time_2 = end_time - start_time;

		timings[i] = make_tuple(time_1, time_2);
        cout << "Done\n";

    }

	cout << "Results: " << endl;
    ofstream fout;
    fout.open("benchmark_rabin_pattern_count.txt");
    // fout<<"iteration, time\n";
	for (auto& i : timings) {
		cout << "  loop #" << i.first;
		cout << "ac: " << chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << "ms";
		cout << endl;

        fout<<to_string((i.first+1)) << ", "<< chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << endl;
	}
    fout.close();

	return 0;
}