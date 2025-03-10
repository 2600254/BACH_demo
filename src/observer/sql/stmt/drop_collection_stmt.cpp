#include "sql/stmt/drop_collection_stmt.h"

RC  DropCollectionStmt::create(Db *db, const DropCollectionNode &drop_collection, Stmt *&stmt){
    stmt = new DropCollectionStmt(drop_collection.collection_name);
    return RC::SUCCESS;
}