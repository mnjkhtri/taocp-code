n = 4

#given n events with their start and end time, find max events you can attend
start_time = [1,2,3,6]
end_time = [3,5,9,8]

#Some greedy approaches:
#1) select the next shortest event
#2) select the event with earliest starting time
#3) select the event with earliest finish time

#some temporary sort array
temp = list(range(n))

def keyfunc(n):
    return end_time[n]

#the array is sorted on the basis of end time now
temp.sort(key = keyfunc)

#initializing the emtpy schedule
schedule = []

#now checking each task in the sorted manner
earlier_end_time = 0 #assuming that first itme of the task is 1
for each_task in temp:
    if start_time[each_task] >= earlier_end_time:
        schedule.append(each_task)
        earlier_end_time = end_time[each_task]

print(schedule)
