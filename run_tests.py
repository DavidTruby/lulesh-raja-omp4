from subprocess import call
import os

threads = [20, 40, 80, 160]
sizes = [12, 30, 60, 100]
for ompt in threads :
    os.environ['OMP_NUM_THREADS'] = str(ompt)
    for size in sizes :
        for rep in range(0, 5) :
            print os.getcwd()
            run_command = "helper.sh ./lulesh-plain -s " + str(size) + " > plain_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            filename = "plain_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            f = open(filename, "w")
            call(["/home/cbertol/scripts/helper.sh", "./lulesh-plain -s "+str(size)], stdout=f)

            run_command = "helper.sh ./lulesh-raja-array -s " + str(size) + " > raja-array_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            filename = "raja-array_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            f = open(filename, "w")
            call(["/home/cbertol/scripts/helper.sh", "./lulesh-raja-array -s "+str(size)], stdout=f)

            run_command = "helper.sh ./lulesh-raja-domain -s " + str(size) + " > raja-domain_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            filename = "raja-domain_r" + str(rep) +"_s" + str(size) + "_t_" + str(ompt)
            f = open(filename, "w")
            call(["/home/cbertol/scripts/helper.sh", "./lulesh-raja-domain -s "+str(size)], stdout=f)

