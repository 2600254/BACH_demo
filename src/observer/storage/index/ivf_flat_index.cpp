#include "storage/index/ivf_flat_index.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/db/db.h"

IvfFlatIndex::~IvfFlatIndex() noexcept { close(); }

RC IvfFlatIndex::create(const IndexMeta &index_meta, const vector<const FieldMeta *> &field_metas)
{
  if (inited_) {
    return RC::SUCCESS;
  }
  is_vector_ = true;

  Index::init(index_meta, field_metas);

  inited_ = true;
  return RC::SUCCESS;
}

RC IvfFlatIndex::insert_entry(const char *record, const RID *rid) { return RC::SUCCESS; }

RC IvfFlatIndex::delete_entry(const char *record, const RID *rid) { return RC::SUCCESS; }

IndexScanner *IvfFlatIndex::create_scanner(
    const char *left_key, int left_len, bool left_inclusive, const char *right_key, int right_len, bool right_inclusive)
{
  return nullptr;
}

RC IvfFlatIndex::sync() { return RC::SUCCESS; }

void IvfFlatIndex::destroy() {}

RC IvfFlatIndex::close() { return RC::SUCCESS; }