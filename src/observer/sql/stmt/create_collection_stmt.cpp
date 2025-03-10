#include "sql/stmt/create_collection_stmt.h"


RC CreateCollectionStmt::create(Db *db, const CreateCollectionNode &create_collection, Stmt *&stmt){
    stmt = new CreateCollectionStmt(db, create_collection.collection_name);
    return RC::SUCCESS;
}
