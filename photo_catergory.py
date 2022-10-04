import shutil
import os
import pathlib as path
sourcePath = "E:/In_0217/"
#sourcePath = "E:/In_0217/2022_02_18 樸農生技"
targetPath = "E:/In_0217_Gin/"
Indate = "In_0217_"
date = []
count = 0
num_perday = 15

for root, dirs, files in os.walk(sourcePath):
    #if not files:
    #   continue
    #print(date)
    for i,filename in enumerate(files):
        if i % 2 == 1:          
            #print(targetPath + str(math.ceil(i/2)+1))
            if count > num_perday: count = 1
            else: count += 1
            if not os.path.exists(targetPath + str(count).zfill(2)):
                os.mkdir(targetPath + str(count).zfill(2))
            type = filename.split('.')[1] 
            if type == 'jpg':
                cur_root = root.split("_")[-2]
                filename2 = root + "/" + Indate + cur_root + "_" + str(count).zfill(2) +".jpg"
                os.rename( root + "/" + filename, filename2 )
                #target_file = os.path.abspath(root + "/" + filename)
                target_file = os.path.abspath(root + "/" + filename2)
                print ("Copy ", target_file, "...")

                shutil.copy(target_file, targetPath + str(count).zfill(2))
