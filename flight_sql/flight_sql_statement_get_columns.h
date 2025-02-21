/*
 * Copyright (C) 2020-2022 Dremio Corporation
 *
 * See "LICENSE" for license information.
 */

#include "record_batch_transformer.h"
#include <arrow/array/builder_binary.h>
#include <arrow/array/builder_primitive.h>
#include <arrow/status.h>
#include <odbcabstraction/types.h>

namespace driver {
namespace flight_sql {

using odbcabstraction::MetadataSettings;

class GetColumns_RecordBatchBuilder {
private:
  odbcabstraction::OdbcVersion odbc_version_;

  StringBuilder TABLE_CAT_Builder_;
  StringBuilder TABLE_SCHEM_Builder_;
  StringBuilder TABLE_NAME_Builder_;
  StringBuilder COLUMN_NAME_Builder_;
  Int16Builder DATA_TYPE_Builder_;
  StringBuilder TYPE_NAME_Builder_;
  Int32Builder COLUMN_SIZE_Builder_;
  Int32Builder BUFFER_LENGTH_Builder_;
  Int16Builder DECIMAL_DIGITS_Builder_;
  Int16Builder NUM_PREC_RADIX_Builder_;
  Int16Builder NULLABLE_Builder_;
  StringBuilder REMARKS_Builder_;
  StringBuilder COLUMN_DEF_Builder_;
  Int16Builder SQL_DATA_TYPE_Builder_;
  Int16Builder SQL_DATETIME_SUB_Builder_;
  Int32Builder CHAR_OCTET_LENGTH_Builder_;
  Int32Builder ORDINAL_POSITION_Builder_;
  StringBuilder IS_NULLABLE_Builder_;
  int64_t num_rows_{0};

public:
  struct Data {
    std::optional<std::string> table_cat;
    std::optional<std::string> table_schem;
    std::string table_name;
    std::string column_name;
    std::string type_name;
    std::optional<int32_t> column_size;
    std::optional<int32_t> buffer_length;
    std::optional<int16_t> decimal_digits;
    std::optional<int16_t> num_prec_radix;
    std::optional<std::string> remarks;
    std::optional<std::string> column_def;
    int16_t sql_data_type{};
    std::optional<int16_t> sql_datetime_sub;
    std::optional<int32_t> char_octet_length;
    std::optional<std::string> is_nullable;
    int16_t data_type;
    int16_t nullable;
    int32_t ordinal_position;
  };

  explicit GetColumns_RecordBatchBuilder(
      odbcabstraction::OdbcVersion odbc_version);

  Result<std::shared_ptr<RecordBatch>> Build();

  Status Append(const Data &data);
};

class GetColumns_Transformer : public RecordBatchTransformer {
private:
  const MetadataSettings& metadata_settings_;
  odbcabstraction::OdbcVersion odbc_version_;
  std::optional<std::string> column_name_pattern_;

public:
  explicit GetColumns_Transformer(const MetadataSettings& metadata_settings,
                                  odbcabstraction::OdbcVersion odbc_version,
                                  const std::string *column_name_pattern);

  std::shared_ptr<RecordBatch>
  Transform(const std::shared_ptr<RecordBatch> &original) override;

  std::shared_ptr<Schema> GetTransformedSchema() override;
};

} // namespace flight_sql
} // namespace driver
