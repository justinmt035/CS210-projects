#Justin M Taylor
#Professor Chan
#CS210 Project 3
#6-19-2022

#read daily sales data and displays it on screen
def PrintSales():
    with open("CS210_Project_Three_Input_File.txt","r") as f:
        contents = f.read().splitlines()

    #just print one occurance and then the # of occurances
    for i in set(contents):
        print(i, contents.count(i))
    print()

#find occurance of user input, if any
def SearchSales(userInput):
    with open("CS210_Project_Three_Input_File.txt","r") as f:
        contents = f.read().splitlines()

    #look for word in the set
    if userInput.capitalize() in set(contents):
        return contents.count(userInput.capitalize())
    #if not found
    else:
        return 0
   
#clean data and write to new .dat file
def WriteFile():
    with open("CS210_Project_Three_Input_File.txt","r") as rf:
        contents = rf.read().splitlines()

    #only write each occurance once, along with frequency
    with open("frequency.dat", "w") as wf:
        for i in set(contents):
            wf.write(str(i + " " + str(contents.count(i))))
            wf.write("\n")
