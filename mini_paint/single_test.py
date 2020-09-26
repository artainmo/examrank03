import sys
import os
import subprocess
from termcolor import colored

def test_original(test):
    if test.find(' ') != -1:
        test = test.split()
        return (subprocess.run(["./our_mini_paint", "mini_paint_tester/examples/" + test[1], "mini_paint_tester/examples/" + test[1]], stdout=subprocess.PIPE)).stdout
    command = "mini_paint_tester/examples/" + test
    return ((subprocess.run(["./our_mini_paint", command], stdout=subprocess.PIPE)).stdout).decode("utf-8")


def test_my(test):
    if test.find(' ') != -1:
        test = test.split()
        return (subprocess.run(["./my_mini_paint", "mini_paint_tester/examples/" + test[1], "mini_paint_tester/examples/" + test[1]], stdout=subprocess.PIPE)).stdout
    command = "mini_paint_tester/examples/" + test
    return ((subprocess.run(["./my_mini_paint", command], stdout=subprocess.PIPE)).stdout).decode("utf-8")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Error: file arguments")
        exit()
    output = test_original(sys.argv[1]);
    my_output = test_my(sys.argv[1]);
    if output == my_output:
        print(colored("CORRECT", "green"))
        print("\n****************************************\n%s\n****************************************\n" % (sys.argv[1]))
        print("==========output==========\nYOU:\n%s\nOUR:\n%s" % (my_output, output))
    else:
        print(colored("WRONG", "red"))
        print("\n****************************************\n%s\n****************************************\n" % (sys.argv[1]))
        print("==========output==========\nYOU:\n%s\nOUR:\n%s" % (my_output, output))
