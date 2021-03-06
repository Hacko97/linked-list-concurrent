import subprocess
import statistics
import math

NO_OF_SAMPLES = 100     # Number of samples used

# Compiling the source codes in C
def compileAll():
    subprocess.call(['gcc', '-g', '-Wall', '-o', 'linkedlist_serial', 'linkedlist_serial.c'])
    subprocess.call(['gcc', '-g', '-Wall', '-o', 'linkedlist_mutex', 'linkedlist_mutex.c', '-lm', '-lpthread'])
    subprocess.call(['gcc', '-g', '-Wall', '-o', 'linkedlist_rw_lock', 'linkedlist_rw_lock.c', '-lm', '-lpthread'])

# Execution and calculation
# Finding average and standard deviation
def execute(command):
    elapsed_times = []
    for i in range(NO_OF_SAMPLES):
        time = subprocess.Popen(command, stdout=subprocess.PIPE).communicate()[0]
        elapsed_times.append(float(time))

    print('Average: ' + str(statistics.mean(elapsed_times)))
    print('Standard Deviation: ' + str(statistics.stdev(elapsed_times)))

    avg = statistics.mean(elapsed_times)
    standardDeviation = statistics.stdev(elapsed_times)
    samples = math.ceil(math.pow(((100 * 1.96 * standardDeviation) / (5 * avg)), 2))

    print('Samples: ' + str(samples))

#  list of commands
def executeCommands(cmds):
    for i in range(len(cmds)):
        print("Number of Threads: " + str(2**i))
        execute(cmds[i])
        print("")

# Commands to be excuted based on the Case
serial = [['./linkedlist_serial', '1000', '10000', '0.99', '0.005', '0.005'], ['./linkedlist_serial', '1000', '10000', '0.9', '0.05', '0.05'], ['./linkedlist_serial', '1000', '10000', '0.5', '0.25', '0.25']]
mutex_1 = [['./linkedlist_mutex', '1000', '10000', '0.99', '0.005', '0.005', '1'], ['./linkedlist_mutex', '1000', '10000', '0.99', '0.005', '0.005', '2'], ['./linkedlist_mutex', '1000', '10000', '0.99', '0.005', '0.005', '4'], ['./linkedlist_mutex', '1000', '10000', '0.99', '0.005', '0.005', '8']]
mutex_2 = [['./linkedlist_mutex', '1000', '10000', '0.9', '0.05', '0.05', '1'], ['./linkedlist_mutex', '1000', '10000', '0.9', '0.05', '0.05', '2'], ['./linkedlist_mutex', '1000', '10000', '0.9', '0.05', '0.05', '4'], ['./linkedlist_mutex', '1000', '10000', '0.9', '0.05', '0.05', '8']]
mutex_3 = [['./linkedlist_mutex', '1000', '10000', '0.5', '0.25', '0.25', '1'], ['./linkedlist_mutex', '1000', '10000', '0.5', '0.25', '0.25', '2'], ['./linkedlist_mutex', '1000', '10000', '0.5', '0.25', '0.25', '4'], ['./linkedlist_mutex', '1000', '10000', '0.5', '0.25', '0.25', '8']]
rw_1 = [['./linkedlist_rw_lock', '1000', '10000', '0.99', '0.005', '0.005', '1'], ['./linkedlist_rw_lock', '1000', '10000', '0.99', '0.005', '0.005', '2'], ['./linkedlist_rw_lock', '1000', '10000', '0.99', '0.005', '0.005', '4'], ['./linkedlist_rw_lock', '1000', '10000', '0.99', '0.005', '0.005', '8']]
rw_2 = [['./linkedlist_rw_lock', '1000', '10000', '0.9', '0.05', '0.05', '1'], ['./linkedlist_rw_lock', '1000', '10000', '0.9', '0.05', '0.05', '2'], ['./linkedlist_rw_lock', '1000', '10000', '0.9', '0.05', '0.05', '4'], ['./linkedlist_rw_lock', '1000', '10000', '0.9', '0.05', '0.05', '8']]
rw_3 = [['./linkedlist_rw_lock', '1000', '10000', '0.5', '0.25', '0.25', '1'], ['./linkedlist_rw_lock', '1000', '10000', '0.5', '0.25', '0.25', '2'], ['./linkedlist_rw_lock', '1000', '10000', '0.5', '0.25', '0.25', '4'], ['./linkedlist_rw_lock', '1000', '10000', '0.5', '0.25', '0.25', '8']]

mutex = [mutex_1, mutex_2, mutex_3]
rw = [rw_1, rw_2, rw_3]

# Compiling files
compileAll()

# the output
for i in range(3):
    print('=============== CASE: ' + str(i + 1) + ' ===============')
    print('Serial linked list ')
    print('=======')
    execute(serial[i])
    print('')
    print('Mutex linked list ')
    print('=======')
    executeCommands(mutex[i])
    print('')
    print('ReadWrite linked list')
    print('=======')
    executeCommands(rw[i])
