#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Job {
	ll time, min_start;
	ll min_end() const {
		return min_start + time;
	}	
};

struct {
    inline bool operator() (const Job& job_a, const Job& job_b) {
        if (job_a.min_end() != job_b.min_end()) {
        	return job_a.min_end() < job_b.min_end();
        } else {
        	return (job_a.min_start < job_b.min_start);
        }
    }
} comparator;

int main() {
	ll n;
	ifstream in("input.txt");
	ofstream out("output.txt");
	vector<Job> jobs;
	
	in >> n;
	
	for (ll i = 0; i < n; ++i) {
		Job job;
		in >> job.min_start >> job.time;
		jobs.push_back(job);
	}

	std::sort(jobs.begin(), jobs.end(), comparator);

	ll fine = 0ll;
	ll t = 0ll;
	for (int i = 0; i < n; ++i) {
		
		if(i != n - 1) {
            ll t2 = t, t3 = t;
            ll fine2 = fine, fine3 = fine;
 
            fine2 += max(0ll, t2 - jobs[i].min_start);
            t2 = max(t2, jobs[i].min_start) + jobs[i].time;

            fine2 += max(0ll, t2 - jobs[i + 1].min_start);
            t2 = max(t2, jobs[i + 1].min_start) + jobs[i + 1].time;

            fine3 += max(0ll, t3 - jobs[i + 1].min_start);
            t3 = max(t3, jobs[i + 1].min_start) + jobs[i + 1].time;

            fine3 += max(0ll, t3 - jobs[i].min_start);
            t3 = max(t3, jobs[i].min_start) + jobs[i].time;

            if (fine3 < fine2) swap(jobs[i], jobs[i+1]);
        }

		fine += max(0ll, t - jobs[i].min_start);
		t = max(t, jobs[i].min_start) + jobs[i].time;
	}
	out << n << ' ' << fine;
}