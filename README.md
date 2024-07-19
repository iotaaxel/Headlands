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
## Important Note
The code and test case were modified for a slightly different scenario and input.

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
* Time Complexity: `O(n)`, where n is the number of lines in the CSV file.
* Space Complexity: `O(n)` for storing the jobs in memory.
### Detecting Union of Single Linked Lists:
* Time Complexity: `O(n)` for iterating over the jobs to verify conditions.
* Space Complexity: `O(n)` for storing the job graph and auxiliary sets (seenStartJobs and seenNextJobs).
### Computing Job Statistics:
* Time Complexity: `O(n)` for traversing the job graph.
* Space Complexity: `O(n)` for storing visited jobs.
