def test_original(test):
    command = "/our_micro_paint micro_paint_tester/examples/" + test
    return subprocess.run([shell_command], shell=True, capture_output=True, timeout=1)


def test_my(test):
    command = "./our_micro_paint micro_paint_tester/examples/" + test
    return subprocess.run([shell_command], shell=True, capture_output=True, timeout=1)


if __name__ == "__main__":
    print(colored("\nDIRECTORY".ljust(15) + "TEST".ljust(65) + "RESULT", "yellow"))
    try:
        os.remove("correct_log.txt")
        os.remove("correct_log.txt")
    except:
        pass
    with open("tests.txt", "r") as fd_test, open("errors_log.txt", "a+") as fd_error_log, open("correct_log.txt", "a+") as fd_correct_log:
        tests = fd_tests.readlines()
        for test in tests:
            if test[0] != '#':
                output = test_original(test[0:-1]);
                my_output = test_my(test[0:-1]);
                if output == my_output:
                    print(test.ljust(65), end = "")
                    print(colored("CORRECT", "green"))
                    fd_correct_log.write("\n****************************************\n%s\n****************************************\n" % (test))
                    fd_correct_log.write("==========output==========\nYOU:\n%s\nBASH:\n%s" % (my_output, output))
                else:
                    print(test.ljust(65), end= "")
                    print(colored("WRONG", "red"))
                    fd_result.write("\n****************************************\n%s\n****************************************\n" % (test))
                    fd_result.write("==========output==========\nYOU:\n%s\n\nBASH:\n%s\n" % (output_m, output_b))
