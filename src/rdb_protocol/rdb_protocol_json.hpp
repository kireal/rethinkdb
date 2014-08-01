// Copyright 2010-2013 RethinkDB, all rights reserved.
#ifndef RDB_PROTOCOL_RDB_PROTOCOL_JSON_HPP_
#define RDB_PROTOCOL_RDB_PROTOCOL_JSON_HPP_

#include <memory>

#include "containers/archive/versioned.hpp"
#include "http/json.hpp"
#include "rdb_protocol/datum.hpp"

/* This file is for storing a few extensions to json that are useful for
 * implementing the rdb_protocol. */

template <cluster_version_t W>
void serialize(write_message_t *wm, const std::shared_ptr<const scoped_cJSON_t> &cjson);
template <cluster_version_t W>
MUST_USE archive_result_t deserialize(read_stream_t *s, std::shared_ptr<const scoped_cJSON_t> *cjson);

namespace query_language {

int json_cmp(cJSON *l, cJSON *r);

} // namespace query_language


class counted_datum_less_t {
public:
    counted_datum_less_t() { }
    bool operator()(const counted_t<const ql::datum_t> &a,
                    const counted_t<const ql::datum_t> &b) const {
        return a->compare_lt(reql_version_t::RSI, *b);
    }
};

#endif /* RDB_PROTOCOL_RDB_PROTOCOL_JSON_HPP_ */
