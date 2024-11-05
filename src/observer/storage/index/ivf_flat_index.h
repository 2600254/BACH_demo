#pragma once

#include "storage/index/index.h"

class IvfFlatIndex : public Index
{
public:
  IvfFlatIndex() = default;
  virtual ~IvfFlatIndex() noexcept;
  RC create(const IndexMeta &index_meta, const vector<const FieldMeta *> &field_metas);

  RC            insert_entry(const char *record, const RID *rid) override;
  RC            delete_entry(const char *record, const RID *rid) override;
  IndexScanner *create_scanner(const char *left_key, int left_len, bool left_inclusive, const char *right_key,
      int right_len, bool right_inclusive) override;
  RC            sync() override;
  void          destroy() override;
  RC            close();

private:
  bool   inited_ = false;
  Table *table_  = nullptr;
};