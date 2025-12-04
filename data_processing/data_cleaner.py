f = open("DATA.txt", mode ="r", encoding ="UTF-8")

# check for extra heading after initial heading
text = f.read()
corrected_text = ""
duplicated_heading_flag = False
time_flag = False
time_offset = 0
current_time_collection = ""
current_time = 0
for i in range(len(text)):

    # duplicated heading flag actions
    if duplicated_heading_flag and text[i] == "\n":
        duplicated_heading_flag = False
        time_offset = current_time

    # handling extra heading
    # this sequence will only appear if there's been an extra heading printed (first heading prints without \n)
    if i < len(text) -1:
        if text[i] + text[i+1] == "\nT":
            duplicated_heading_flag = True
    # handling time
        elif text[i] == "\n":
            time_flag = True
            corrected_text += "\n"

    # time flag actions
    if time_flag and text[i] == ",":
        current_time = int(current_time_collection) + time_offset
        corrected_text += str(current_time)
        current_time_collection = ""
        time_flag = False
    elif time_flag:
        current_time_collection += text[i]


    # normal writing
    if not duplicated_heading_flag and not time_flag:
        corrected_text += text[i]

f.close()

fn = open("L2cleaned.csv", mode ="x", encoding="UTF-8")
fn.write(corrected_text)
fn.close()