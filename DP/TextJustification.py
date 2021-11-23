import numpy as np

INFINITY = float("inf")


def Badness(text_length_list, start_index, end_index, page_width):
    line_width = np.sum(text_length_list[start_index:end_index]) + end_index - start_index - 1
    if line_width > page_width:
        result = INFINITY
    else:
        result = (page_width - line_width) ** 3
    return result


def TextJustificationDP_Recursion(text_length_list_, start_index, page_width, parent_, badness_list):
    if badness_list[start_index] > 0:
        return badness_list[start_index]
    if start_index == len(text_length_list_):
        badness_list[start_index] = 0
        return badness_list[start_index]
    mini_badness = INFINITY
    mini_next_start_index = -1
    for next_start_index in np.arange(start_index + 1, len(text_length_list_) + 1):
        temp = TextJustificationDP_Recursion(text_length_list_, next_start_index, page_width, parent_, badness_list) + \
               Badness(text_length_list_, start_index, next_start_index, page_width)
        if temp < mini_badness:
            mini_badness = temp
            mini_next_start_index = next_start_index
    parent_[start_index] = mini_next_start_index
    badness_list[start_index] = mini_badness
    return badness_list[start_index]


def TextJustification_Wrapper(text_list_, page_width):
    parent_ = np.ones(len(text_list_), np.int32) * -1  # store the best next start index for text_list[index:]
    text_length_list = [len(word) for word in text_list_]
    badness_list = np.ones(len(text_list_) + 1,
                           dtype=np.float32) * -1  # store the minimum badness for text_list[index:]
    TextJustificationDP_Recursion(text_length_list, 0, page_width, parent_, badness_list)
    return parent_, badness_list


def TextJustificationDP_Iteration(word_list, page_width):
    word_length_list = [len(word) for word in word_list]
    parent_ = np.ones(len(word_list),dtype=np.int32) * -1
    badness_list_ = np.zeros(len(word_list) + 1, dtype=np.float32)
    badness_list_[len(word_list)] = 0

    for i in np.arange(len(word_list) - 1, -1, -1):
        mini_ = INFINITY
        mini_next_start_index = -1
        for next_start_index in range(i + 1, len(word_list) + 1):
            temp = badness_list_[next_start_index] + Badness(word_length_list, i, next_start_index, page_width)
            if temp < mini_:
                mini_ = temp
                mini_next_start_index = next_start_index
        badness_list_[i] = mini_
        parent_[i] = mini_next_start_index
    return parent_, badness_list_


def show_result(text_list_, parent_):
    start_index = 0
    while start_index < len(text_list_):
        end_index = parent_[start_index]
        for i in range(start_index, end_index):
            print(f"{text_list_[i]}", end=" ")
        print("")
        start_index = end_index


if __name__ == '__main__':
    text = "Text messaging is most often used between private mobile phone users, as a substitute for voice calls in " \
           "situations where voice communication is impossible or undesirable (e.g., during a school class or a work " \
           "meeting). Texting is also used to communicate very brief messages, such as informing someone that you will " \
           "be late or reminding a friend or colleague about a meeting. As with e-mail, informality and brevity have " \
           "become an accepted part of text messaging. Some text messages such as SMS can also be used for the remote " \
           "control of home appliances. It is widely used in domotics systems. Some amateurs have also built their own " \
           "systems to control (some of) their appliances via SMS.[16][17] Other methods such as group messaging, " \
           "which was patented in 2012 by the GM of Andrew Ferry, Devin Peterson, Justin Cowart, Ian Ainsworth, " \
           "Patrick Messinger, Jacob Delk, Jack Grande, Austin Hughes, Brendan Blake, and Brooks Brasher are used to " \
           "involve more than two people into a text messaging conversation[citation needed]. A Flash SMS is a type[18] " \
           "of text message that appears directly on the main screen without user interaction and is not automatically " \
           "stored in the inbox. It can be useful in cases such as an emergency (e.g., fire alarm) or confidentiality (" \
           "e.g., one-time password) "
    text_list = text.split()
    # parent, badness_array = TextJustification_Wrapper(text_list, page_width=40)
    parent, badness_array = TextJustificationDP_Iteration(text_list, 40)

    # show the splited text
    show_result(text_list, parent)
