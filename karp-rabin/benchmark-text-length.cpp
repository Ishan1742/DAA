#include<bits/stdc++.h>
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

std::vector<long long> PrecomputeHashes(string T, int k, int p, int x) 
{
    int lenT = T.length();
    std::vector<long long> H;
    string S = T.substr(0, k);
    H.push_back(hash_func(S, p, x, k));
    //cout<<S<<" "<<H[0]<<"\n";
    long long y = 1; 
    for (int i = 0; i < k - 1; i++)
        y = (y * x) % p;
    //cout<<y<<"\n\n";
    for (int i = 1; i < lenT - k + 1; i++)
    {   
        //cout<<H[i-1]<<" "<<T[i-1]<<" "<<T[i+k-1]<<"\n";
        long long int val = (x * (H[i-1] - T[i - 1]*y) + T[i + k - 1])%p;
        if(val < 0)
            val = val + p;
        H.push_back(val);
    }
    //cout<<"\n";
    return H;
}

long long int bench_rabin_karp(string text_string, vector<string> patterns) {
	long long int count = 0;
    
    int p = int(1e9) + 7;
    int x = rand() % (p - 1) + 1;

    int k = INT_MAX;
    for(int i=0; i<patterns.size(); i++)
    {
        if(patterns[i].length() < k && patterns[i].length() != 0)
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

    std::vector<long long> H = PrecomputeHashes(text_string, k, p, x);
    for (size_t i = 0; i <= text_string.length() - k; ++i) 
    {
        //cout<<H[i]<<" "<<text_string.substr(i, k)<<" ""\n";
        if( pattern_hash.find(H[i]) != pattern_hash.end())
        {
            vector<string> match = pattern_hash[H[i]];
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

int main()
{
    map<size_t, tuple<chrono::high_resolution_clock::duration, chrono::high_resolution_clock::duration>> timings;

    for (int i = 0; i < 51; i++)
    {
        fstream ft;
        ft.open("../tests/text-length/text_" + to_string(i) + ".txt");
        string text;
        ft >> text;
        ft.close();

        set<string> patterns;
        fstream fp;
        fp.open("../tests/text-length/pattern_" + to_string(i) + ".txt");
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
		long long int count_2 = bench_rabin_karp(text, pattern_vector);
		end_time = chrono::high_resolution_clock::now();
		auto time_2 = end_time - start_time;

		timings[i] = make_tuple(time_1, time_2);
        cout << "Done\n";

    }

	cout << "Results: " << endl;
    ofstream fout;
    fout.open("benchmark_rabin_text_length.txt");
    // fout<<"iteration, time\n";
	for (auto& i : timings) {
		cout << "  loop #" << i.first;
		cout << "ac: " << chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << "ms";
		cout << endl;

        fout<<to_string(i.first+1) << ", "<< chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << endl;
	}
    fout.close();

    // string text = "GEEKS FOR GEEKS";
    // vector<string> patterns;
    // patterns.push_back("GEEKS");
    // patterns.push_back("EEKS");
    // patterns.push_back("FOR");
    // patterns.push_back("ABCD");

    // long long int count = bench_rabin_karp(text, patterns);

    // cout<<count<<"\n";

	return 0;
}