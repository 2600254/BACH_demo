#include <span>

#include "common/lang/lower_bound.h"
#include "common/log/log.h"
#include "common/global_context.h"
#include "sql/parser/parse_defs.h"
#include "storage/buffer/disk_buffer_pool.h"
#include "storage/index/ivf_flat.h"

using namespace common;

