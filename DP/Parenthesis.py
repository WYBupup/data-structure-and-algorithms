# encoding:utf-8
import numpy as np

INFINITY = float("inf")


def MatrixMultiplicationCost(left_shape_0, left_shape_1, right_shape_0, right_shape_1):
    if left_shape_1 != right_shape_0:
        print("the left matrix and right matrix doesn't meet the ,atrix multiplication rule!\n")
        exit(0)
    return left_shape_0 * right_shape_1 * left_shape_1


def ParenthesisDP_Recursion(Matrix_list, start_index, end_index, split_indexes, cost):
    if start_index >= end_index:
        print("Error during recursion the start_index >=end_index\n")
        exit(0)
    if start_index + 1 == end_index:
        cost[start_index][end_index] = 0
        return cost[start_index][end_index]
    if cost[start_index][end_index] >= 0:
        return cost[start_index][end_index]
    mini = INFINITY
    split_index = -1
    for k in range(start_index + 1, end_index):
        temp = ParenthesisDP_Recursion(Matrix_list, start_index, k, split_indexes, cost) + \
               ParenthesisDP_Recursion(Matrix_list, k, end_index, split_indexes, cost) + \
               MatrixMultiplicationCost(Matrix_list[start_index].shape[0], Matrix_list[k - 1].shape[1],
                                        Matrix_list[k].shape[0], Matrix_list[end_index - 1].shape[1])
        if temp < mini:
            mini = temp
            split_index = k
    cost[start_index][end_index] = mini
    split_indexes[start_index][end_index] = split_index
    return cost[start_index][end_index]


def ParenthesisDP_Wrapper(Matrix_list):
    split_indexes = np.ones(shape=(len(Matrix_list), len(Matrix_list) + 1), dtype=np.int32)
    cost = np.ones(shape=(len(Matrix_list), len(Matrix_list) + 1), dtype=np.int32) * -1
    ParenthesisDP_Recursion(Matrix_list, 0, len(Matrix_list), split_indexes, cost)
    return cost, split_indexes


def ParenthesisDP_Iteration(Matrix_list):
    # the split index for Matrix_list[i:j]
    split_indexes = np.ones(shape=(len(Matrix_list), len(Matrix_list) + 1), dtype=np.int32) * -1
    # minimal multiplication cost for Matrix_list[i:j]
    cost = np.ones(shape=(len(Matrix_list), len(Matrix_list) + 1), dtype=np.int32) * -1
    # when there is only one element in the segment then the cost is zero
    for i in range(0, len(Matrix_list)):
        cost[i][i + 1] = 0

    for start_index in range(len(Matrix_list) - 2, -1, -1):
        for end_index in range(start_index + 2, len(Matrix_list) + 1):
            mini = INFINITY
            split_index = -1
            for k in range(start_index + 1, end_index):
                temp = cost[start_index][k] + cost[k][end_index] + \
                       MatrixMultiplicationCost(Matrix_list[start_index].shape[0], Matrix_list[k - 1].shape[1],
                                                Matrix_list[k].shape[0], Matrix_list[end_index - 1].shape[1])
                if temp < mini:
                    mini = temp
                    split_index = k
            cost[start_index][end_index] = mini
            split_indexes[start_index][end_index] = split_index
    return cost, split_indexes


def show_result(Matrix_list, split_indexes, start_index, end_index):
    if start_index + 1 == end_index:
        print(f"A[{Matrix_list[start_index].shape[0]},{Matrix_list[start_index].shape[1]}]", end="")
        return

    split_index = split_indexes[start_index][end_index]
    if start_index + 1 != split_index:
        print("(", end="")
    show_result(Matrix_list, split_indexes, start_index, split_index)
    if start_index + 1 != split_index:
        print(")", end="")
    if split_index + 1 != end_index:
        print("(", end="")
    show_result(Matrix_list, split_indexes, split_index, end_index)
    if split_index + 1 != end_index:
        print(")", end="")


if __name__ == "__main__":
    Matrix_list_ = [np.zeros(shape=(30, 35)), np.zeros(shape=(35, 15)), np.zeros(shape=(15, 5)),
                    np.zeros(shape=(5, 10)), np.zeros(shape=(10, 20)), np.zeros(shape=(20, 25))]
    # cost_, split_indexes_ = ParenthesisDP_Wrapper(Matrix_list_)
    cost_, split_indexes_ = ParenthesisDP_Iteration(Matrix_list_)
    show_result(Matrix_list_, split_indexes_, 0, len(Matrix_list_))
