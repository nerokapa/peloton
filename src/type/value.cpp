//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// value.h
//
// Identification: src/backend/type/value.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <include/type/value.h>
#include "type/value.h"

#include "type/boolean_type.h"
#include "type/decimal_type.h"
#include "type/numeric_type.h"
#include "type/timestamp_type.h"
#include "type/varlen_type.h"

namespace peloton {
namespace type {

Value::Value(const Value &other) {
  type_ = other.type_;
  size_ = other.size_;
  switch (type_->GetTypeId()) {
    case Type::VARCHAR:
    case Type::VARBINARY:
      if (size_.len == PELOTON_VALUE_NULL) {
        value_.varlen = nullptr;
      } else {
        value_.varlen = new char[size_.len];
        PL_MEMCPY(value_.varlen, other.value_.varlen,
                  size_.len);
      }
      break;
    default:
      value_ = other.value_;
  }
}

Value::Value(Value &&other) : Value() { swap(*this, other); }

Value &Value::operator=(Value other) {
  swap(*this, other);
  return *this;
}

// ARRAY is implemented in the header to ease template creation

// BOOLEAN and TINYINT
Value::Value(Type::TypeId type, int8_t i) : Value(type) {
  switch (type) {
    case Type::BOOLEAN:
      value_.boolean = i;
      size_.len = (value_.boolean == PELOTON_BOOLEAN_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TINYINT:
      value_.tinyint = i;
      size_.len = (value_.tinyint == PELOTON_INT8_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::SMALLINT:
      value_.smallint = i;
      size_.len = (value_.smallint == PELOTON_INT16_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::INTEGER:
    case Type::PARAMETER_OFFSET:
      value_.integer = i;
      size_.len = (value_.integer == PELOTON_INT32_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::BIGINT:
      value_.bigint = i;
      size_.len = (value_.bigint == PELOTON_INT64_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// SMALLINT
Value::Value(Type::TypeId type, int16_t i) : Value(type) {
  switch (type) {
    case Type::BOOLEAN:
      value_.boolean = i;
      size_.len = (value_.boolean == PELOTON_BOOLEAN_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TINYINT:
      value_.tinyint = i;
      size_.len = (value_.tinyint == PELOTON_INT8_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::SMALLINT:
      value_.smallint = i;
      size_.len = (value_.smallint == PELOTON_INT16_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::INTEGER:
    case Type::PARAMETER_OFFSET:
      value_.integer = i;
      size_.len = (value_.integer == PELOTON_INT32_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::BIGINT:
      value_.bigint = i;
      size_.len = (value_.bigint == PELOTON_INT64_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// INTEGER and PARAMETER_OFFSET
Value::Value(Type::TypeId type, int32_t i) : Value(type) {
  switch (type) {
    case Type::BOOLEAN:
      value_.boolean = i;
      size_.len = (value_.boolean == PELOTON_BOOLEAN_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TINYINT:
      value_.tinyint = i;
      size_.len = (value_.tinyint == PELOTON_INT8_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::SMALLINT:
      value_.smallint = i;
      size_.len = (value_.smallint == PELOTON_INT16_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::INTEGER:
    case Type::PARAMETER_OFFSET:
      value_.integer = i;
      size_.len = (value_.integer == PELOTON_INT32_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::BIGINT:
      value_.bigint = i;
      size_.len = (value_.bigint == PELOTON_INT64_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// BIGINT and TIMESTAMP
Value::Value(Type::TypeId type, int64_t i) : Value(type) {
  switch (type) {
    case Type::BOOLEAN:
      value_.boolean = i;
      size_.len = (value_.boolean == PELOTON_BOOLEAN_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TINYINT:
      value_.tinyint = i;
      size_.len = (value_.tinyint == PELOTON_INT8_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::SMALLINT:
      value_.smallint = i;
      size_.len = (value_.smallint == PELOTON_INT16_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::INTEGER:
    case Type::PARAMETER_OFFSET:
      value_.integer = i;
      size_.len = (value_.integer == PELOTON_INT32_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::BIGINT:
      value_.bigint = i;
      size_.len = (value_.bigint == PELOTON_INT64_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TIMESTAMP:
      value_.timestamp = i;
      size_.len = (value_.timestamp == PELOTON_TIMESTAMP_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// BIGINT
Value::Value(Type::TypeId type, uint64_t i) : Value(type) {
  switch (type) {
    case Type::BOOLEAN:
      value_.boolean = i;
      size_.len = (value_.boolean == PELOTON_BOOLEAN_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    case Type::TIMESTAMP:
      value_.timestamp = i;
      size_.len = (value_.timestamp == PELOTON_TIMESTAMP_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// DECIMAL
Value::Value(Type::TypeId type, double d) : Value(type) {
  switch (type) {
    case Type::DECIMAL:
      value_.decimal = d;
      size_.len = (value_.decimal == PELOTON_DECIMAL_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

Value::Value(Type::TypeId type, float f) : Value(type) {
  switch (type) {
    case Type::DECIMAL:
      value_.decimal = f;
      size_.len = (value_.decimal == PELOTON_DECIMAL_NULL ? PELOTON_VALUE_NULL : 0);
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

// VARCHAR and VARBINARY
Value::Value(Type::TypeId type, const char *data, uint32_t len) : Value(type) {
  switch (type) {
    case Type::VARCHAR:
    case Type::VARBINARY:
      if (data == nullptr) {
        value_.varlen = nullptr;
        size_.len = PELOTON_VALUE_NULL;
      } else {
        PL_ASSERT(len < PELOTON_VARCHAR_MAX_LEN);
        value_.varlen = new char[len];
        PL_ASSERT(value_.varlen != nullptr);
        size_.len = len;
        PL_MEMCPY(value_.varlen, data, len);
      }
      break;
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

Value::Value(Type::TypeId type, const std::string &data) : Value(type) {
  switch (type) {
    case Type::VARCHAR:
    case Type::VARBINARY: {
      // TODO: How to represent a null string here?
      uint32_t len = data.length() + (type == Type::VARCHAR);
      value_.varlen = new char[len];
      PL_ASSERT(value_.varlen != nullptr);
      size_.len = len;
      PL_MEMCPY(value_.varlen, data.c_str(), len);
      break;
    }
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for constructor");
  }
}

Value::Value() : Value(Type::INVALID) {}

Value::~Value() {
  switch (type_->GetTypeId()) {
    case Type::VARBINARY:
    case Type::VARCHAR:
      delete[] value_.varlen;
      break;
    default:
      break;
  }
}

const std::string Value::GetInfo() const {
  std::ostringstream os;
  os << "Value::" << Type::GetInstance(GetTypeId())->ToString() << "["
     << ToString() << "]";
  return os.str();
}

bool Value::IsNull() const {
  return size_.len == PELOTON_VALUE_NULL;
}

bool Value::CheckComparable(const Value &o) const {
  switch (GetTypeId()) {
    case Type::BOOLEAN:
      if (o.GetTypeId() == Type::BOOLEAN) return true;
      break;
    case Type::TINYINT:
    case Type::SMALLINT:
    case Type::INTEGER:
    case Type::BIGINT:
    case Type::DECIMAL:
      switch (o.GetTypeId()) {
        case Type::TINYINT:
        case Type::SMALLINT:
        case Type::INTEGER:
        case Type::BIGINT:
        case Type::DECIMAL:
          return true;
        default:
          break;
      }
      break;
    case Type::VARCHAR:
      if (o.GetTypeId() == Type::VARCHAR) return true;
      break;
    case Type::VARBINARY:
      if (o.GetTypeId() == Type::VARBINARY) return true;
      break;
    case Type::TIMESTAMP:
      if (o.GetTypeId() == Type::TIMESTAMP) return true;
      break;
    default:
      break;
  }
  return false;
}

bool Value::CheckInteger() const {
  switch (GetTypeId()) {
    case Type::TINYINT:
    case Type::SMALLINT:
    case Type::INTEGER:
    case Type::BIGINT:
    case Type::PARAMETER_OFFSET:
      return true;
    default:
      break;
  }

  return false;
}

Value Value::DeserializeFrom(const char *storage, const Type::TypeId type_id,
                             UNUSED_ATTRIBUTE const bool inlined,
                             UNUSED_ATTRIBUTE VarlenPool *pool) {
  return Type::GetInstance(type_id)->DeserializeFrom(storage, inlined, pool);
}

Value Value::DeserializeFrom(SerializeInput &in, const Type::TypeId type_id,
                             VarlenPool *pool UNUSED_ATTRIBUTE) {
  return Type::GetInstance(type_id)->DeserializeFrom(in, pool);
}

Value Value::CompareEquals(const Value &o) const {
  return type_->CompareEquals(*this, o);
}
Value Value::CompareNotEquals(const Value &o) const {
  return type_->CompareNotEquals(*this, o);
}
Value Value::Value::CompareLessThan(const Value &o) const {
  return type_->CompareLessThan(*this, o);
}
Value Value::CompareLessThanEquals(const Value &o) const {
  return type_->CompareLessThanEquals(*this, o);
}
Value Value::CompareGreaterThan(const Value &o) const {
  return type_->CompareGreaterThan(*this, o);
}
Value Value::CompareGreaterThanEquals(const Value &o) const {
  return type_->CompareGreaterThanEquals(*this, o);
}

// Other mathematical functions
Value Value::Add(const Value &o) const { return type_->Add(*this, o); }
Value Value::Subtract(const Value &o) const {
  return type_->Subtract(*this, o);
}
Value Value::Multiply(const Value &o) const {
  return type_->Multiply(*this, o);
}
Value Value::Divide(const Value &o) const { return type_->Divide(*this, o); }
Value Value::Modulo(const Value &o) const { return type_->Modulo(*this, o); }
Value Value::Min(const Value &o) const { return type_->Min(*this, o); }
Value Value::Max(const Value &o) const { return type_->Max(*this, o); }
Value Value::Sqrt() const { return type_->Sqrt(*this); }
Value Value::OperateNull(const Value &o) const {
  return type_->OperateNull(*this, o);
}
bool Value::IsZero() const { return type_->IsZero(*this); }

// Is the data inlined into this classes storage space, or must it be accessed
// through an indirection/pointer?
bool Value::IsInlined() const { return type_->IsInlined(*this); }

// Return a stringified version of this value
std::string Value::ToString() const { return type_->ToString(*this); }

// Compute a hash value
size_t Value::Hash() const { return type_->Hash(*this); }
void Value::HashCombine(size_t &seed) const {
  return type_->HashCombine(*this, seed);
}

// Serialize this value into the given storage space. The inlined parameter
// indicates whether we are allowed to inline this value into the storage
// space, or whether we must store only a reference to this value. If inlined
// is false, we may use the provided data pool to allocate space for this
// value, storing a reference into the allocated pool space in the storage.
void Value::SerializeTo(char *storage, bool inlined, VarlenPool *pool) const {
  type_->SerializeTo(*this, storage, inlined, pool);
}
void Value::SerializeTo(SerializeOutput &out) const {
  type_->SerializeTo(*this, out);
}

// Perform a shallow copy from a serialized varlen value to another serialized varlen value
// Only support VARCHAR/VARBINARY
void Value::ShallowCopyTo(char *dest, char *src, const Type::TypeId type_id, bool inlined, VarlenPool *src_pool) {
  Type::GetInstance(type_id)->DoShallowCopy(dest, src, inlined, src_pool);
}

// Create a copy of this value
Value Value::Copy() const { return type_->Copy(*this); }

Value Value::CastAs(const Type::TypeId type_id) const {
  return type_->CastAs(*this, type_id);
}

// Access the raw variable length data
const char *Value::GetData() const { return type_->GetData(*this); }

// Access the raw variable length data from a pointer pointed to a tuple storage
char *Value::GetDataFromStorage(Type::TypeId type_id, char *storage) {
  switch (type_id) {
    case Type::VARCHAR:
    case Type::VARBINARY: {
      return Type::GetInstance(type_id)->GetData(storage);
    }
    default:
      throw Exception(EXCEPTION_TYPE_INCOMPATIBLE_TYPE,
                      "Invalid Type for getting raw data pointer");
  }
}

// Get the length of the variable length data
uint32_t Value::GetLength() const { return type_->GetLength(*this); }

// Get the element at a given index in this array
Value Value::GetElementAt(uint64_t idx) const {
  return type_->GetElementAt(*this, idx);
}

Type::TypeId Value::GetElementType() const {
  return type_->GetElementType(*this);
}

// Does this value exist in this array?
Value Value::InList(const Value &object) const {
  return type_->InList(*this, object);
}

}  // namespace peloton
}  // namespace type
