#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>

using Job = std::tuple<int, int, int>;
using JobGraph = std::unordered_map<int, std::pair<int, int>>;

std::vector<Job> readCSV(const std::string& filename) {
    std::vector<Job> jobs;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id_str, time_str, next_id_str;
        if (std::getline(ss, id_str, ',') &&
            std::getline(ss, time_str, ',') &&
            std::getline(ss, next_id_str, ',')) {
            int id = std::stoi(id_str);
            int time = std::stoi(time_str);
            int next_id = std::stoi(next_id_str);
            jobs.emplace_back(id, time, next_id);
        }
    }
    return jobs;
}

bool isUnionOfSingleLinkedLists(const std::vector<Job>& jobs, JobGraph& jobGraph) {
    std::unordered_set<int> seenStartJobs;
    std::unordered_set<int> seenNextJobs;
    
    for (const auto& job : jobs) {
        int id, time, next_id;
        std::tie(id, time, next_id) = job;

        if (seenStartJobs.find(id) != seenStartJobs.end()) {
            return false;  // Duplicate start job
        }
        seenStartJobs.insert(id);
        if (next_id != 0) {
            seenNextJobs.insert(next_id);
        }
        jobGraph[id] = {time, next_id};
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
    std::unordered_set<int> visited;
    
    for (const auto& [id, _] : jobGraph) {
        if (visited.find(id) == visited.end()) {
            int current_job = id;
            while (current_job != 0 && visited.find(current_job) == visited.end()) {
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
        const std::string filename = "daily_log.csv";
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
