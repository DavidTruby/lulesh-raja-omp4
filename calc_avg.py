import sys

size = sys.argv[1]
num_threads = sys.argv[2]

def calc_avg_version(version_name) :
    files = []
    for rs in range(0,5) :
        files.append(version_name+"_r"+str(rs)+"_s"+str(size)+"_t_"+str(num_threads))

    sum_time_dict = {}

    for rs in range(0,5) :
        with open(files[rs]) as f :
            lines = f.readlines()
            # scan content until we find a line that starts with "Kernel"
            line_no = -1
            for fl in lines :
                line_no = line_no + 1
                if fl.startswith("Kernel ") :
                    break

            #now scan until end of file and record times in dictionary
            for next_line in range(line_no, len(lines)) :
                #line_no points to the first line with a Kernel
                #print(lines[next_line])
                full_line = lines[next_line]
                # first eliminate "Kernel "
                subline = (full_line[7:])
                #print(subline)
                kernel_name_only_index = subline.index('_') - 1
                kernel_name = subline[:kernel_name_only_index]
                #print(kernel_name)
                kernel_name_end_index = subline.index('-')
                kernel_name_end_index  = kernel_name_end_index - 1
                times_called_start_index = subline.index('_') +1
                times_called = subline[times_called_start_index:kernel_name_end_index]
                #print(times_called)
                avg_time_index = subline.index("avg time =")
                actual_time_index = avg_time_index + 11
                avg_time_line = subline[actual_time_index:]
                #print(avg_time_line)
                tup = (kernel_name,times_called)
                if kernel_name in sum_time_dict :
                    update_time = (sum_time_dict[tup] + float(avg_time_line)) / 2
                else :
                    update_time = float(avg_time_line)
                sum_time_dict.update({tup:update_time})

    #print all dictionary out
    print(version_name)
    for (k1,k2),t in sum_time_dict.iteritems() :
        line = k1 + "\t\t\t" + k2 + "\t\t\t" + str(t)
        print (line)

calc_avg_version("raja-domain")
calc_avg_version("raja-array")
calc_avg_version("plain")
