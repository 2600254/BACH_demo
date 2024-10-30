create_table_sql_1 = "CREATE TABLE big_order_by_0(id int, num int, price float, addr char(10), birthday date);"
create_table_sql_2 = "CREATE TABLE big_order_by_1(id int, num int, price float, addr char(10), birthday date);"
create_table_sql_3 = "CREATE TABLE big_order_by_2(id int, num int, price float, addr char(10), birthday date);"
create_table_sql_4 = "CREATE TABLE big_order_by_3(id int, num int, price float, addr char(10), birthday date);"

template_insert_sql = "INSERT INTO big_order_by_{} values({}, {}, {}, {}, {});"
import random
import string
def generate_data():
    for i in range(4):
        insert_sqls = []
        for _ in range(20):
            int_value = random.randint(1, 1000)
            float_value = random.random() * 1000
            # 生成一个随机日期字符串，格式为"YYYY-MM-DD"
            date_value = f"{random.randint(2000, 2023)}-{random.randint(1, 12):02d}-{random.randint(1, 28):02d}"

            # 生成一个长度为10的随机字符串
            char_value = ''.join(random.choices(string.ascii_letters, k=9))
            insert_sql = template_insert_sql.format(i, int_value, int_value, float_value, "\'" + char_value + "\'", "\'"+date_value+ "\'")
            insert_sqls.append(insert_sql)
        with open(f"big_order_by.txt", "a") as f:
            f.write("\n".join(insert_sqls))
            f.write("\n")
if __name__ == '__main__':
    with open(f"big_order_by.txt", "w") as f:
        f.write(create_table_sql_1)
        f.write("\n")
        f.write(create_table_sql_2)
        f.write("\n")
        f.write(create_table_sql_3)
        f.write("\n")
        f.write(create_table_sql_4)
        f.write("\n")
    generate_data()