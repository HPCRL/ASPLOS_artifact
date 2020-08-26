def nextloop(cur_lv,  rangelist, allkey, curkey):
    if cur_lv >= len(rangelist):
        allkey.append(list(curkey))
        return
    for i in range(0,rangelist[cur_lv]):
        curkey.append(i)
        nextloop(cur_lv+1, rangelist, allkey, curkey)
        curkey.pop()
    return
    


def main():
    allkey = []
    curkey = []
    rangelist = [2,3,4]
    nextloop(cur_lv=0, rangelist=rangelist, allkey=allkey, curkey=curkey)

    for k in allkey:
        print(k)
        
if __name__ == "__main__":
    main()    