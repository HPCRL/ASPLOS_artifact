import sys
import time

def main():
    log_filename = sys.argv[1]
    old_llvm = "%s.ll" % log_filename
    new_llvm = "%s-new.ll" % log_filename

    file_input = open(old_llvm, 'r')
    Lines = file_input.readlines()

    print('Before modi lens of file : %d' % len(Lines))

    count = 0
    for line in Lines:
        #print("Line{}: {}".format(count, line))
        if (line.find('define dllexport i32 @fconv(') != -1 and Lines[count+1].strip() == 'entry:'):
            Lines.insert(count+2, '  call void @get_time(i32 1)\n')
        count += 1
    print ('First modi lens of file : %d' % len(Lines))

    count = 0
    for line in Lines:
        #print("Line{}: {}".format(count, line))
        if (line.find('tail call fastcc i32 @fconv_compute_(') != -1 and Lines[count + 1].find('ret i32') != -1):
            Lines[count] = Lines[count].replace('tail', '')
            Lines.insert(count+1, '  call void @get_time(i32 0)\n')
        count += 1
    print('Second modi lens of file : %d' % len(Lines))


    newLines = []
    count = 0
    for line in Lines:
        if (line.find('attributes #0 = {') != -1 and Lines[count + 1].find('attributes #1 = {') != -1):
            newLines.extend(Lines[0:count - 1])
            newLines.insert(count, 'declare void @get_time(i32)\n\n')
            newLines.extend(Lines[count :])
        count += 1
    file_input.close()

    time.sleep(8)

    # count = 0
    # for line in newLines:
    #     print("Line{}: {}".format(count, line))
    #     count += 1
    print('Final lens of file : %d' % len(newLines))

    file_output = open(new_llvm, 'w')
    file_output.writelines(newLines)
    file_output.close()


if __name__ == "__main__":
    main()
