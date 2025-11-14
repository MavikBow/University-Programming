set JOBS;
set ARCS within {JOBS, JOBS};

param t_max {JOBS};
param t_min {JOBS}; 
param cost_per_day {JOBS};
param project_cost_per_day;
param deadline;

var t {JOBS} >= 0;  # time per job
var start {JOBS} >= 0; # starting time of a job
var finish >= 0; # time for the project

minimize Total_Cost:
    sum{j in JOBS} cost_per_day[j] * (t_max[j] - t[j]) + 
    project_cost_per_day * finish;

# Deadline
subject to Finish_Time_Definition{j in JOBS}:
    finish >= start[j] + t[j] ;

# Job relations
subject to Precedence {(i,j) in ARCS}:
    start[j] >= start[i] + t[i];

# minmax time restraints per job
subject to Duration_Min {j in JOBS}:
    t[j] >= t_min[j];
    
subject to Duration_Max {j in JOBS}:
    t[j] <= t_max[j];

# Deadline
subject to Deadline_Constraint:
    finish <= deadline;
