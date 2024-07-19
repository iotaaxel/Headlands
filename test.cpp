#include <cassert>
#include <iostream>
#include <vector>
#include <tuple>
#include "main.cpp"  // Ensure this includes the definitions of readCSV, isUnionOfSingleLinkedLists, computeJobStatistics

void testReadCSV() {
    auto jobs = readCSV("daily_log.csv");
    assert(jobs.size() == 5);
    assert(jobs[0] == std::make_tuple(1, 5, 2));
    assert(jobs[1] == std::make_tuple(2, 3, 3));
    assert(jobs[2] == std::make_tuple(3, 7, 0));
    assert(jobs[3] == std::make_tuple(4, 2, 5));
    assert(jobs[4] == std::make_tuple(5, 4, 0));
}

void testIsUnionOfSingleLinkedLists() {
    std::vector<Job> jobs = {
        {1, 5, 2},
        {2, 3, 3},
        {3, 7, 0},
        {4, 2, 5},
        {5, 4, 0}
    };
    JobGraph jobGraph;
    assert(isUnionOfSingleLinkedLists(jobs, jobGraph));
}

void testComputeJobStatistics() {
    JobGraph jobGraph = {
        {1, {5, 2}},
        {2, {3, 3}},
        {3, {7, 0}},
        {4, {2, 5}},
        {5, {4, 0}}
    };
    int totalTime, totalJobs;
    double averageTime;
    computeJobStatistics(jobGraph, totalTime, totalJobs, averageTime);
    assert(totalTime == 21);
    assert(totalJobs == 5);
    assert(averageTime == 4.2);
}

int main() {
    testReadCSV();
    testIsUnionOfSingleLinkedLists();
    testComputeJobStatistics();
    std::cout << "All tests passed.\n";
    return 0;
}
