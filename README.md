# Headlands

## Scenario - Job Runner
Each day a distributed computing platform generates a daily log of job runs. Each job has a unique integer id, the time it took to run (in seconds), and the next job's id. We call a sequence of jobs a chain; if a job represents the end of the chain, its next id will be `0`. Given the daily log (from a csv file), generate a report summarizing the chains run during the day. Your job is to detect if the input data is an union of single linked list; then compute the total time to finish all jobs, the total number of jobs, average time per job. If the input is malformed in any way then an error should be reported.

### Input (CSV format via STDIN)
* The first line is a header.
* Each subsequent line provides the properties for a given job
  ```csv
  #job_id,runtime_in_seconds,next_job_id
  1,60,23
  2,23,3
  3,12,0
  23,30,0
  ```

### Output (emitted via STDOUT) 
* Each section in the report describes a chain and should be in descending order based on the total runtime of the chain.
```markdown
start_job: id of the first job in the chain
last_job: id of the last job in the chain
number_of_jobs: number of jobs in the chain
job_chain_runtime: total runtime of the chain (in HH:MM:SS)
average_job_time: average per job runtime (in HH:MM:SS)
```

## Build and Run:
1. Create a `build` directory: 
  ```mkdir build && cd build```
2. Configure CMake: 
  ```cmake .. && make```
3. Run Main:
  ```./main```
4. Run Unit Tests:
  ```./main```

## Performance and Complexity 
### Reading and Parsing CSV File:
* Time Complexity: `O(n)`, where n is the number of lines in the CSV file. Each line is processed once to extract the job details.
* Space Complexity: `O(n)` where n is the number of lines in the CSV file. This is for storing the jobs in memory.
* Efficiency Considerations: The parsing is done in a single pass, making it efficient in terms of both time and space.
### Detecting Union of Single Linked Lists:
* Time Complexity: `O(n)`, where n is the number of jobs. We iterate over the list of jobs to build the graph and check for duplicates.
* Space Complexity: `O(n)`, where n is the number of jobs. We use two sets (seenStartJobs and seenNextJobs) to keep track of the jobs, and a map (jobGraph) to store the job details.
* Efficiency Considerations: Using sets provides average O(1) time complexity for insertions and lookups, making this step efficient.
### Computing Job Statistics:
* Time Complexity: `O(n)`, where n is the number of jobs. We traverse the job graph once to compute the total time, number of jobs, and average time.
* Space Complexity: `O(n)`, where n is the number of jobs. We use a set (visited) to keep track of the visited jobs.
* Efficiency Considerations: The single traversal of the job graph ensures that the computation is efficient.
### Summary
* The overall time complexity for the complete process is `O(n)`, dominated by the need to process each job and its details.
* The overall space complexity is `O(n)`, as we need to store the job details, sets for tracking job IDs, and the job graph.

