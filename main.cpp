#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

using Job = std::tuple<std::string, int, std::string>;
using JobGraph = std::unordered_map<std::string, std::pair<int, std::string>>;

std::vector<Job> readCSV(const std::string& filename) {
    std::vector<Job> jobs;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string start_job, time_str, next_job;
        if (std::getline(ss, start_job, ',') &&
            std::getline(ss, time_str, ',') &&
            std::getline(ss, next_job, ',')) {
            int time = std::stoi(time_str);
            jobs.emplace_back(start_job, time, next_job);
        }
    }
    return jobs;
}

bool isUnionOfSingleLinkedLists(const std::vector<Job>& jobs, JobGraph& jobGraph) {
    std::unordered_set<std::string> seenStartJobs;
    std::unordered_set<std::string> seenNextJobs;
    
    for (const auto& job : jobs) {
        std::string start_job, next_job;
        int time;
        std::tie(start_job, time, next_job) = job;

        if (seenStartJobs.find(start_job) != seenStartJobs.end()) {
            return false;  // Duplicate start job
        }
        seenStartJobs.insert(start_job);
        if (!next_job.empty()) {
            seenNextJobs.insert(next_job);
        }
        jobGraph[start_job] = {time, next_job};
    }

    // Ensure no job appears as both start_job and next_job except for endpoint jobs
    for (const auto& job : seenStartJobs) {
        if (seenNextJobs.find(job) != seenNextJobs.end()) {
            return false;
        }
    }
    return true;
}

void computeJobStatistics(const JobGraph& jobGraph, int& totalTime, int& totalJobs, double& averageTime) {
    totalTime = 0;
    totalJobs = 0;
    std::unordered_set<std::string> visited;
    
    for (const auto& [start_job, _] : jobGraph) {
        if (visited.find(start_job) == visited.end()) {
            std::string current_job = start_job;
            while (!current_job.empty() && visited.find(current_job) == visited.end()) {
                visited.insert(current_job);
                totalTime += jobGraph.at(current_job).first;
                totalJobs++;
                current_job = jobGraph.at(current_job).second;
            }
        }
    }
    averageTime = static_cast<double>(totalTime) / totalJobs;
}

int main() {
    try {
        const std::string filename = "test_jobs.csv";
        auto jobs = readCSV(filename);

        JobGraph jobGraph;
        if (!isUnionOfSingleLinkedLists(jobs, jobGraph)) {
            throw std::runtime_error("Input data is not a union of single linked lists");
        }

        int totalTime, totalJobs;
        double averageTime;
        computeJobStatistics(jobGraph, totalTime, totalJobs, averageTime);

        std::cout << "Total Time: " << totalTime << "\n";
        std::cout << "Total Number of Jobs: " << totalJobs << "\n";
        std::cout << "Average Time per Job: " << averageTime << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
    return 0;
}
