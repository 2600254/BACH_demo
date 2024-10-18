import random 
seed = random.randint(1, 100)
print("seed: {}".format(seed))
random.seed(seed)
template_insert = "INSERT INTO unique_table2 VALUES ({}, {}, {}, {});"
template_update = "UPDATE unique_table2 SET id1={}, id2={}, col1={}, col2={} where id2={};"


id1_id2_set = set()
id2_set = set()

def custom_unique_test(init_num, update_num, invalid_num):
    
    insert_values = []
    while len(insert_values) < init_num:
        nums = [random.randint(1, 100) for _ in range(4)]
        if nums[1] in id2_set or (nums[0], nums[1]) in id1_id2_set:
            continue
        id1_id2_set.add((nums[0], nums[1]))
        id2_set.add(nums[1])
        insert_values.append(nums)

    with open('custom_unique_test.txt', 'w') as f:
        f.write("CREATE TABLE unique_table2(id1 int, id2 int, col1 int, col2 int);" + '\n')
        f.write("-----------insert-------------\n")
        for i in insert_values:
            f.write(template_insert.format(i[0], i[1], i[2], i[3]) + '\n')
        f.write("create unique index index_id1 on unique_table2(id2);" + '\n')
        f.write("create unique index index_id2 on unique_table2(id1, id2);" + '\n')

    update_values = []
    while len(update_values) < update_num:
        nums = [random.randint(1, 100) for _ in range(5)]
        if nums[-1] not in id2_set:
            continue
        if nums[-1] != nums[1] and (nums[0], nums[1]) in id1_id2_set:
            continue
        if nums[-1] != nums[1] and nums[1] in id2_set:
            continue

        for i in id1_id2_set:
            if i[1] == nums[-1]:
                id1_id2_set.remove(i)
                break

        id2_set.remove(nums[-1])

        id1_id2_set.add((nums[0], nums[1]))
        id2_set.add(nums[1])
        update_values.append(nums)
    with open('custom_unique_test.txt', 'a') as f:
        f.write("select * from unique_table2;\n")
        f.write("-----------update_success-------------\n")
        for i in update_values:
            f.write(template_update.format(i[0], i[1], i[2], i[3], i[4]) + '\n')
    
    invalid_values = []
    while len(invalid_values) < invalid_num:
        nums = [random.randint(1, 100) for _ in range(5)]
        if nums[-1] not in id2_set:
            continue 
        if nums[-1]!= nums[1] and ((nums[0], nums[1]) in id1_id2_set or nums[1] in id2_set):
            invalid_values.append(nums)

    with open('custom_unique_test.txt', 'a') as f:
        f.write("-----------update_failed-------------\n")
        for i in invalid_values:
            f.write(template_update.format(i[0], i[1], i[2], i[3], i[4]) + '\n')

if __name__ == '__main__':
    custom_unique_test(20, 20, 20)