n = 4

#given n tasks of durations and deadlines, with point system of time_you_finish-dealine, find max points
duration = [4,3,2,4]
deadlines = [2,5,7,5]
#note we start with time t = 0
#and we do all the tasks

#working greedy: to select the task in increasing order of their duration

temp = list(range(n))

def keyfunc(n):
    return duration[n]

temp.sort(key=keyfunc)

total = 0
current_time = 0
for each_task in temp:
    total += abs(deadlines[each_task]-current_time)
    current_time += duration[each_task]

print(total)