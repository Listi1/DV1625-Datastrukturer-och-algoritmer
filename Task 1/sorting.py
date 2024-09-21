def quicksort(lst: list) -> None:
    if len(lst) > 1:
        pivot = lst[len(lst) // 2]

        larger_elements = []
        equal_elements = []
        smaller_elements = []

        for element in lst:
            if element < pivot:
                smaller_elements.append(element)
            elif element == pivot:
                equal_elements.append(element)
            else:
                larger_elements.append(element)

        quicksort(smaller_elements)
        quicksort(larger_elements)

        lst[:] = smaller_elements + equal_elements + larger_elements

def insertionsort(lst: list) -> None:
    if len(lst) > 1:
        for i in range(1, len(lst)):
            x = i-1
            current_value = lst[i]

            while(x >= 0 and current_value < lst[x]):
                lst[x+1] = lst[x]
                x = x-1

            lst[x+1] = current_value


def mergesort(lst: list) -> None:
    if len(lst) > 1:
        middle = len(lst) // 2
        left_half = lst[:middle]
        right_half = lst[middle:]

        mergesort(left_half)
        mergesort(right_half)

        merged_list = []
        left_index = 0
        right_index = 0

        while left_index < len(left_half) and right_index < len(right_half):
            if left_half[left_index] >= right_half[right_index]:
                merged_list.append(right_half[right_index])
                right_index += 1
            else:
                merged_list.append(left_half[left_index])
                left_index += 1

        merged_list.extend(left_half[left_index:])
        merged_list.extend(right_half[right_index:])
        lst[:] = merged_list


def mergesort_hybrid(lst: list) -> None:
    if len(lst) > 1:
        if len(lst) > 13:
            middle = len(lst) // 2
            left_half = lst[:middle]
            right_half = lst[middle:]

            mergesort_hybrid(left_half)
            mergesort_hybrid(right_half)

            merged_list = []
            left_index = 0
            right_index = 0

            while left_index < len(left_half) and right_index < len(right_half):
                if left_half[left_index] >= right_half[right_index]:
                    merged_list.append(right_half[right_index])
                    right_index += 1
                else:
                    merged_list.append(left_half[left_index])
                    left_index += 1

            merged_list.extend(left_half[left_index:])
            merged_list.extend(right_half[right_index:])
            lst[:] = merged_list
        else:
            insertionsort(lst)


def quicksort_hybrid(lst: list) -> None:
    if len(lst) > 1:
        if len(lst) > 12:
            pivot = lst[len(lst) // 2]

            larger_elements = []
            equal_elements = []
            smaller_elements = []

            for element in lst:
                if element < pivot:
                    smaller_elements.append(element)
                elif element == pivot:
                    equal_elements.append(element)
                else:
                    larger_elements.append(element)

            quicksort_hybrid(smaller_elements)
            quicksort_hybrid(larger_elements)

            lst[:] = smaller_elements + equal_elements + larger_elements
        else:
            insertionsort(lst)
