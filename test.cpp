#include <cassert>
#include <iostream>
#include <vector>
#include <tuple>
#include "main.cpp"  // Ensure this includes the definitions of readCSV, isUnionOfSingleLinkedLists, computeJobStatistics

void testReadCSV() {
    auto jobs = readCSV("test_jobs.csv");
    assert(jobs.size() == 3);
    assert(jobs[0] == std::make_tuple("job1", 5, "job2"));
    assert(jobs[1] == std::make_tuple("job2", 3, "job3"));
    assert(jobs[2] == std::make_tuple("job3", 7, ""));
}

void testIsUnionOfSingleLinkedLists() {
    std::vector<Job> jobs = {
        {"job1", 5, "job2"},
        {"job2", 3, "job3"},
        {"job3", 7, ""}
    };
    JobGraph jobGraph;
    assert(isUnionOfSingleLinkedLists(jobs, jobGraph));
}

void testComputeJobStatistics() {
    JobGraph jobGraph = {
        {"job1", {5, "job2"}},
        {"job2", {3, "job3"}},
        {"job3", {7, ""}}
    };
    int totalTime, totalJobs;
    double averageTime;
    computeJobStatistics(jobGraph, totalTime, totalJobs, averageTime);
    assert(totalTime == 15);
    assert(totalJobs == 3);
    assert(averageTime == 5.0);
}

int main() {
    testReadCSV();
    testIsUnionOfSingleLinkedLists();
    testComputeJobStatistics();
    std::cout << "All tests passed.\n";
    return 0;
}
