#include <string>
#include <vector>
#include <memory>

class Expression;

/**
 * @brief 描述一个insert语句
 * 示例1：insert {name: “andy”, dender: “m”,} into users
 * 示例2：
 */
struct InsertAqlNode
{
    std::string collection;
    std::vector<std::shared_ptr<Expression>> values;
};

/**
 * @brief 描述一个filter语句
 * 示例1: FILTER c.name == "Ned"
 * 示例2: FILTER c.age < 13 AND c.age != null
 */
struct filterAqlNode
{
    Expression *condition = nullptr; // 过滤条件
};

/**
 * @brief 描述一个update语句
 * 示例1: UPDATE "2861650" WITH { alive: false } IN Characters
 * 示例2: FOR c IN Characters
 *          UPDATE c WITH { season: 1 } IN Characters
 */
struct updateAqlNode
{
    std::string collection; // 集合名
    Expression* ids; // 更新的id
    std::vector<Expression*> values; // 更新的值
};

/**
 * @brief 描述一个remove语句
 * 示例1: REMOVE "2861650" IN Characters
 * 示例2: FOR c IN Characters
 *          REMOVE c IN Characters
 */
struct removeAqlNode
{
    std::string collection; // 集合名
    std::vector<Expression*> ids; // 删除的id
};

/**
 * @brief 描述一个return语句
 * 示例1: RETURN c.name
 * 示例2: RETURN c.name, c.age
 */
struct returnAqlNode
{
    std::vector<Expression*> values; // 返回的值
};

struct forAqlNode
{
    std::string collection; // 集合名
    std::string alias; // 集合别名
};
