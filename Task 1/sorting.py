def quicksort(lst: list) -> None:
    pass

def insertionsort(lst: list) -> None:
    for i in range(1, (len(lst))):           #dubbelkolla så denna ser ok ut från fake koden i boken
        value = lst[i]
        previousIndex = i-1
        while previousIndex >= 0 and value < lst[previousIndex]:
            lst[previousIndex+1] = lst[previousIndex]
            previousIndex -= 1
        lst[previousIndex+1] = value

def mergesort(lst: list) -> None:
    pass

def mergesort_hybrid(lst: list) -> None:
    pass

def quicksort_hybrid(lst: list) -> None:
    pass 