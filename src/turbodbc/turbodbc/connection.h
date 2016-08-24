#pragma once

#include "turbodbc/cursor.h"
#include <cpp_odbc/connection.h>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace turbodbc {
class cursor;

/**
 * @brief This class is provides basic functionality required by python's
 *        connection class as specified by the database API version 2.
 *        Additional wrapping may be required.
 */
class connection : public boost::enable_shared_from_this<connection> {
public:
	/**
	 * @brief Construct a new connection based on the given low-level connection
	 */
	connection(std::shared_ptr<cpp_odbc::connection const> low_level_connection);

	/**
	 * @brief Commit all operations which have been performed since the last commit
	 *        or rollback
	 */
	void commit() const;

	/**
	 * @brief Roll back all operations which have been performed since the last commit
	 *        or rollback
	 */
	void rollback() const;

	/**
	 * @brief Create a new cursor object associated with this connection
	 */
	turbodbc::cursor make_cursor();

	bool is_current_result(const cursor* c) const;

	boost::shared_ptr<cpp_odbc::connection const> get_connection() const;

	/// Indicate number of rows which shall be buffered by result sets
	std::size_t rows_to_buffer;
	///< Indicate number of parameter sets which shall be buffered by queries
	std::size_t parameter_sets_to_buffer;
	///< Indicate whether asynchronous i/o should be used
	bool use_async_io;

private:
	boost::shared_ptr<cpp_odbc::connection const> connection_;
	turbodbc::cursor* active_cursor_;
};

}
