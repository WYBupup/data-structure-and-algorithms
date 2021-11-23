# encoding:utf-8
import numpy as np

INFINITY = float("inf")
replace = 0
insert = 1
delete = 2


def OperationCost(code, char_x=np.nan, char_y=np.nan):
    if code == insert:
        cost = 1
    elif code == delete:
        cost = 1
    elif code == replace:
        if char_x == char_y:
            cost = 0
        else:
            cost = 1
    else:
        print("Error format of code for computing operation cost!\n")
        exit(0)
    return cost


def EditDistanceDP_Recursion(str1_, str2_, index_str1, index_str2, cost_matrix, operation):
    if cost_matrix[index_str1][index_str2] >= 0:
        return cost_matrix[index_str1][index_str2]
    if index_str1 == len(str1_) and index_str2 == len(str2_):
        cost_matrix[index_str1][index_str2] = 0
        return cost_matrix[index_str1][index_str2]
    mini = INFINITY
    code = -1
    # insertion
    if index_str2 + 1 <= len(str2_):
        temp = EditDistanceDP_Recursion(str1_, str2_, index_str1, index_str2 + 1, cost_matrix,
                                        operation) + OperationCost(code=insert)
        if temp < mini:
            mini = temp
            code = insert
    # delete
    if index_str1 + 1 <= len(str1_):
        temp = EditDistanceDP_Recursion(str1_, str2_, index_str1 + 1, index_str2, cost_matrix,
                                        operation) + OperationCost(code=delete)
        if temp < mini:
            mini = temp
            code = delete
    # replace
    if index_str1 + 1 <= len(str1_) and index_str2 + 1 <= len(str2_):
        temp = EditDistanceDP_Recursion(str1_, str2_, index_str1 + 1, index_str2 + 1, cost_matrix,
                                        operation) + OperationCost(code=replace, char_x=str1_[index_str1],
                                                                   char_y=str2_[index_str2])
        if temp < mini:
            mini = temp
            code = replace
    cost_matrix[index_str1][index_str2] = mini
    operation[index_str1][index_str2] = code
    return cost_matrix[index_str1][index_str2]


def EditDistanceDP_Wrapper(str1_, str2_):
    # store the smallest cost to make str1_[i:]&str[j:] the same
    cost_matrix = np.ones(shape=(len(str1_) + 1, len(str2_) + 1), dtype=np.int32) * -1
    # store the operation on str1[i:]'s first character to make str1[i:] and str[j:] same with minimal cost
    operation = np.ones(shape=(len(str1_) + 1, len(str2_) + 1), dtype=np.int32) * -1
    EditDistanceDP_Recursion(str1_, str2_, 0, 0, cost_matrix, operation)
    return cost_matrix, operation


def EditDistanceDP_Iteration(str1_, str2_):
    cost_matrix = np.ones(shape=(len(str1_) + 1, len(str2_) + 1), dtype=np.int32) * INFINITY
    operation = np.ones(shape=(len(str1_) + 1, len(str2_) + 1), dtype=np.int32) * -1

    for index_str1 in range(len(str1_), -1, -1):
        for index_str2 in range(len(str2_), -1, -1):
            if index_str2 == len(str2_) and index_str1 == len(str1_):
                cost_matrix[index_str1][index_str2] = 0
                continue
            mini = INFINITY
            code = -1
            # delete
            if index_str1 + 1 <= len(str1_):
                temp = cost_matrix[index_str1 + 1][index_str2] + OperationCost(delete)
                if temp < mini:
                    mini = temp
                    code = delete
            # insert
            if index_str2 + 1 <= len(str2_):
                temp = cost_matrix[index_str1][index_str2 + 1] + OperationCost(insert)
                if temp < mini:
                    mini = temp
                    code = insert
            # replace
            if index_str1 + 1 <= len(str1_) and index_str2 + 1 <= len(str2_):
                temp = cost_matrix[index_str1 + 1][index_str2 + 1] + OperationCost(replace, str1_[index_str1],
                                                                                   str2_[index_str2])
                if temp < mini:
                    mini = temp
                    code = replace
            cost_matrix[index_str1][index_str2] = mini
            operation[index_str1][index_str2] = code
    return cost_matrix, operation


def show_result(str1_: list, str2_: list, operation):
    print(f"str1:{str(str1_)}")
    index_str1 = 0
    index_str2 = 0
    index_str1_copy = 0
    index_str2_copy = 0
    str1_copy = str1_.copy()
    while index_str1 < len(str1_) or index_str2 < len(str2):
        if operation[index_str1][index_str2] == insert:
            str1_copy.insert(index_str1_copy, str2_[index_str2_copy])
            index_str2 += 1
            index_str2_copy += 1
            index_str1_copy += 1
        elif operation[index_str1][index_str2] == delete:
            str1_copy.pop(index_str1_copy)
            index_str1 += 1
        elif operation[index_str1][index_str2] == replace:
            str1_copy[index_str1_copy] = str2_[index_str2_copy]
            index_str1 += 1
            index_str2 += 1
            index_str1_copy += 1
            index_str2_copy += 1
        else:
            print("during show result, wrong code of operation occurs in the operation matrix!\n")
            exit(0)
    print(f"str1:{str(str1_copy)}")
    print(f"str2:{str(str2_)}")


if __name__ == "__main__":
    str1 = "bashuvfgvahsbdjbhau"  
    str2 = "ahshvfgwvhevfhsgugcuhvbsh"
    # cost_matrix_, operation_ = EditDistanceDP_Wrapper(str1, str2)
    cost_matrix_, operation_ = EditDistanceDP_Iteration(str1, str2)
    # show result
    show_result(list(str1), list(str2), operation_)
