#include "jobrequestmodel.h"
#include <utils/Util.h>

// clang-format off
const QLatin1String CHANGE_STATE("UPDATE job_requests SET status = ? WHERE request_id = ?");
// clang-format on

void JobRequestModel::accept() { util(true); }

void JobRequestModel::reject() { util(false); }

void JobRequestModel::util(bool v) {
  CREATE_SQL(CHANGE_STATE);
  SQL_BIND(v);
  SQL_BIND(request_id);
  if (!query.exec())
    SQL_THROW;
}
