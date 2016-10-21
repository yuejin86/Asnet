// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: WorldSession.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "WorldSession.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace TestSession {

namespace {

const ::google::protobuf::Descriptor* TestMsg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TestMsg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_WorldSession_2eproto() {
  protobuf_AddDesc_WorldSession_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "WorldSession.proto");
  GOOGLE_CHECK(file != NULL);
  TestMsg_descriptor_ = file->message_type(0);
  static const int TestMsg_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMsg, msgid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMsg, user_name_),
  };
  TestMsg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TestMsg_descriptor_,
      TestMsg::default_instance_,
      TestMsg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMsg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMsg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TestMsg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_WorldSession_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TestMsg_descriptor_, &TestMsg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_WorldSession_2eproto() {
  delete TestMsg::default_instance_;
  delete TestMsg_reflection_;
}

void protobuf_AddDesc_WorldSession_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022WorldSession.proto\022\013TestSession\".\n\007Tes"
    "tMsg\022\020\n\005msgid\030\001 \001(\r:\0011\022\021\n\tuser_name\030\002 \001("
    "\t", 81);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "WorldSession.proto", &protobuf_RegisterTypes);
  TestMsg::default_instance_ = new TestMsg();
  TestMsg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_WorldSession_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_WorldSession_2eproto {
  StaticDescriptorInitializer_WorldSession_2eproto() {
    protobuf_AddDesc_WorldSession_2eproto();
  }
} static_descriptor_initializer_WorldSession_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TestMsg::kMsgidFieldNumber;
const int TestMsg::kUserNameFieldNumber;
#endif  // !_MSC_VER

TestMsg::TestMsg()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:TestSession.TestMsg)
}

void TestMsg::InitAsDefaultInstance() {
}

TestMsg::TestMsg(const TestMsg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:TestSession.TestMsg)
}

void TestMsg::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  msgid_ = 1u;
  user_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TestMsg::~TestMsg() {
  // @@protoc_insertion_point(destructor:TestSession.TestMsg)
  SharedDtor();
}

void TestMsg::SharedDtor() {
  if (user_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete user_name_;
  }
  if (this != default_instance_) {
  }
}

void TestMsg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestMsg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TestMsg_descriptor_;
}

const TestMsg& TestMsg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_WorldSession_2eproto();
  return *default_instance_;
}

TestMsg* TestMsg::default_instance_ = NULL;

TestMsg* TestMsg::New() const {
  return new TestMsg;
}

void TestMsg::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    msgid_ = 1u;
    if (has_user_name()) {
      if (user_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        user_name_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TestMsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:TestSession.TestMsg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 msgid = 1 [default = 1];
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &msgid_)));
          set_has_msgid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_user_name;
        break;
      }

      // optional string user_name = 2;
      case 2: {
        if (tag == 18) {
         parse_user_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_user_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->user_name().data(), this->user_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "user_name");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:TestSession.TestMsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:TestSession.TestMsg)
  return false;
#undef DO_
}

void TestMsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:TestSession.TestMsg)
  // optional uint32 msgid = 1 [default = 1];
  if (has_msgid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->msgid(), output);
  }

  // optional string user_name = 2;
  if (has_user_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->user_name().data(), this->user_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "user_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->user_name(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:TestSession.TestMsg)
}

::google::protobuf::uint8* TestMsg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:TestSession.TestMsg)
  // optional uint32 msgid = 1 [default = 1];
  if (has_msgid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->msgid(), target);
  }

  // optional string user_name = 2;
  if (has_user_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->user_name().data(), this->user_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "user_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->user_name(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:TestSession.TestMsg)
  return target;
}

int TestMsg::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 msgid = 1 [default = 1];
    if (has_msgid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->msgid());
    }

    // optional string user_name = 2;
    if (has_user_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->user_name());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestMsg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TestMsg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TestMsg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TestMsg::MergeFrom(const TestMsg& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_msgid()) {
      set_msgid(from.msgid());
    }
    if (from.has_user_name()) {
      set_user_name(from.user_name());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TestMsg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestMsg::CopyFrom(const TestMsg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestMsg::IsInitialized() const {

  return true;
}

void TestMsg::Swap(TestMsg* other) {
  if (other != this) {
    std::swap(msgid_, other->msgid_);
    std::swap(user_name_, other->user_name_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TestMsg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TestMsg_descriptor_;
  metadata.reflection = TestMsg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace TestSession

// @@protoc_insertion_point(global_scope)
