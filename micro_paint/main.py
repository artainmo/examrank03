import os
import subprocess
from termcolor import colored

def test_original(test):
    if test.find(' ') != -1:
        test = test.split()
        return ((subprocess.run(["./our_micro_paint", "micro_paint_tester/examples/" + test[1], "micro_paint_tester/examples/" + test[1]], stdout=subprocess.PIPE)).stdout).decode("utf-8")
    command = "micro_paint_tester/examples/" + test
    return ((subprocess.run(["./our_micro_paint", command], stdout=subprocess.PIPE)).stdout).decode("utf-8")


def test_my(test):
    if test.find(' ') != -1:
        test = test.split()
        return ((subprocess.run(["./my_micro_paint", "micro_paint_tester/examples/" + test[1], "micro_paint_tester/examples/" + test[1]], stdout=subprocess.PIPE)).stdout).decode("utf-8")
    command = "micro_paint_tester/examples/" + test
    return ((subprocess.run(["./my_micro_paint", command], stdout=subprocess.PIPE)).stdout).decode("utf-8")


if __name__ == "__main__":
    print(colored("TEST ARGUMENTS".ljust(65) + "RESULT", "yellow"))
    try:
        os.remove("correct_log.txt")
        os.remove("errors_log.txt")
    except:
        pass
    with open("tests.txt", "r") as fd_tests, open("answers/errors_log.txt", "a+") as fd_error_log, open("answers/correct_log.txt", "a+") as fd_correct_log:
        tests = fd_tests.readlines()
        for test in tests:
            if test[0] != '#':
                output = test_original(test[0:-1]);
                my_output = test_my(test[0:-1]);
                if output == my_output:
                    print(test[0:-1].ljust(65), end="")
                    print(colored("CORRECT", "green"))
                    fd_correct_log.write("\n****************************************\n%s\n****************************************\n" % (test))
                    fd_correct_log.write("==========output==========\nYOU:\n%s\nOUR:\n%s" % (my_output, output))
                else:
                    print(test[0:-1].ljust(65), end="")
                    print(colored("WRONG", "red"))
                    fd_error_log.write("\n****************************************\n%s\n****************************************\n" % (test))
                    fd_error_log.write("==========output==========\nYOU:\n%s\nOUR:\n%s\n" % (my_output, output))
