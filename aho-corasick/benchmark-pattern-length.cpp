#include "aho_corasick.hpp"
#include <bits/stdc++.h>

namespace ac = aho_corasick;
using trie = ac::trie;

using namespace std;

size_t bench_aho_corasick(string text_string, trie& t) {
	size_t count = 0;
	auto matches = t.parse_text(text_string);
	count += matches.size();
	return count;
}

int main(int argc, char** argv) {

	map<size_t, tuple<chrono::high_resolution_clock::duration, chrono::high_resolution_clock::duration>> timings;

    fstream ft;
    ft.open("../tests/pattern-length/text_0.txt");
    string text;
    ft >> text;
    ft.close();
    for (int i = 2; i < 51; i++)
    {
        set<string> patterns;
        fstream fp;
        fp.open("../tests/pattern-length/pattern_" + to_string(i) + ".txt");
        while(fp.good())
        {
            string a;
            fp >> a;
            patterns.insert(a);
        }
        vector<string> pattern_vector(patterns.begin(), patterns.end());
	    auto start_time = chrono::high_resolution_clock::now();
		auto end_time = chrono::high_resolution_clock::now();
		auto time_1 = end_time - start_time;

        start_time = chrono::high_resolution_clock::now();
        trie t;
	    for (auto& pattern : patterns) 
        {
		    t.insert(pattern);
	    }

        cout << "Running loop: " + to_string(i);
		// auto start_time = chrono::high_resolution_clock::now();
		// auto end_time = chrono::high_resolution_clock::now();
		// auto time_1 = end_time - start_time;

		size_t count_2 = bench_aho_corasick(text, t);
		end_time = chrono::high_resolution_clock::now();
		auto time_2 = end_time - start_time;

        timings[i] = make_tuple(time_1, time_2);
        cout << "Done\n";

    }

	cout << "Results: " << endl;
    ofstream fout;
    fout.open("benchmark_aho_pattern_length.txt");
    // fout<<"iteration, time\n";
	for (auto& i : timings) {
		cout << "  loop #" << i.first;
		cout << "ac: " << chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << "ms";
		cout << endl;

        fout<<to_string((i.first+1)*2) << ", "<< chrono::duration_cast<chrono::milliseconds>(get<1>(i.second)).count() << endl;
	}
    fout.close();

	return 0;
}