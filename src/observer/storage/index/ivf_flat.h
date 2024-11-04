
#pragma once

#include <string.h>

#include "common/lang/comparator.h"
#include "common/lang/memory.h"
#include "common/lang/sstream.h"
#include "common/lang/functional.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/record/record_manager.h"

#define MAX_VECTOR_INDEX_FIELD_NUM 1

class IvfFlatHandler;
class IvfFlatMiniTransaction;

enum class IvfFlatOperationType
{
  READ,
  INSERT,
  DELETE
};

enum class VectorDistanceType
{
  L2_DISTANCE,
  COSINE_DISTANCE,
  INNER_PRODUCT
};

class VList
{
public:
  VList()  = default;
  ~VList() = default;

  RC init(BufferPoolManager &bpm, const char *file_name, const FieldMeta *field);
  RC open(BufferPoolManager &bpm, const char *file_name);
  RC open(DiskBufferPool &buffer_pool);
  RC next(RID &rid);
  RC insert_entry(const char *key, const RID *rid);
  RC close();
  RC destroy();

private:
  DiskBufferPool *buffer_pool_ = nullptr;
  int             nlist_       = 0;
  vector<RID *>   rids_;
};

class VListHandler
{
public:
  RC create(BufferPoolManager &bpm, const char *file_name, const FieldMeta *field, int nlist,
      VectorDistanceType distance_type = VectorDistanceType::L2_DISTANCE);
  RC open(BufferPoolManager &bpm, const char *file_name);
  RC open(DiskBufferPool &buffer_pool);

  RC close();
  RC destroy();

  RC insert_entry(const char *key, const RID *rid);
  RC delete_entry(const char *key, const RID *rid);

  RC kmeans_partition(int nlist);

  RC search(const char *key, int key_len, vector<VList *> &lists, int nprobe = 1);

private:
  int                nlist_         = 0;
  DiskBufferPool    *buffer_pool_   = nullptr;
  VectorDistanceType distance_type_ = VectorDistanceType::L2_DISTANCE;
};

class IvfFlatHandler
{
public:
  RC create(BufferPoolManager &bpm, const char *file_name, const FieldMeta *field, int nlist, int probes,
      VectorDistanceType distance_type = VectorDistanceType::L2_DISTANCE);
  RC open(BufferPoolManager &bpm, const char *file_name);
  RC open(DiskBufferPool &buffer_pool);

  RC close();
  RC destroy();

  RC search(const char *key, int key_len,list<RID> &rids);

  RC insert_entry(const char *key, const RID *rid);
  RC delete_entry(const char *key, const RID *rid);

  RC reconstruct();

  bool is_empty() const;

  RC sync();

public:
  DiskBufferPool &buffer_pool() { return *buffer_pool_; }
  VListHandler   &vlist_handler() { return *vlist_handler_; }

protected:
  RC find_lists(const char *key, std::vector<VList *> &list);

private:
  DiskBufferPool    *buffer_pool_   = nullptr;
  VListHandler      *vlist_handler_ = nullptr;
  VectorDistanceType distance_type_ = VectorDistanceType::L2_DISTANCE;
};
