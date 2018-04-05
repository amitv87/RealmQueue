#include <realm/group_shared.hpp>
#include "impl/object_accessor_impl.hpp"

using namespace realm;
using namespace std::string_literals;

using AnyDict = std::map<std::string, util::Any>;
using AnyVec = std::vector<util::Any>;


#include <sys/time.h>

inline uint64_t getTS() {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  uint64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
  return milliseconds;
  // return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

uint64_t getTimeDiff(uint64_t& t_prev){
  if(t_prev == 0){
    t_prev = getTS();
    return 0;
  }
  long long t_now = getTS();
  long long diff = t_now - t_prev;
  t_prev = t_now;
  return diff;
}

int COUNT = 10000000;

void testWrite(Object& q1, CppContext& ctx){
  auto events = any_cast<List>(q1.get_property_value<util::Any>(ctx, "events"));
  uint64_t ts = getTS();
  int i = 0;
  while(i < COUNT){
    events.add(ctx, util::Any("auto events = any_cast<List>(q1.get_property_value<util::Any>auto events = any_cast<List>"s));
    // events.insert(ctx, 0, util::Any("auto events = any_cast<List>(q1.get_property_value<util::Any>auto events = any_cast<List>"s));
    i += 1;
  }
  std::cout << "push/ms " << COUNT / getTimeDiff(ts) << std::endl;

  
  int ndx = events.size() - 1;
  while(ndx >= 0){
    auto evt = events.get(ndx);
    // events.remove(ndx);
    // ndx = events.size() - 1;
    ndx -= 1;
  }

  // while(events.size()){
  //   auto evt = events.get(0);
  //   events.remove(0);
  // }
  std::cout << "pop/ms " << COUNT / getTimeDiff(ts) << std::endl;
}

int main(int argc, char const *argv[]){
  Schema schema = {
    {"queue", {
      {"idx", PropertyType::String, Property::IsPrimary{true}},
      {"events", PropertyType::Array | PropertyType::Data},
    }},
    // {"event", {
    //   {"ts", PropertyType::Int},
    //   {"did", PropertyType::Int},
    //   {"buff", PropertyType::Data},
    // }}
  };

  Realm::Config config;
  config.path = "./db/hello.realm";
  config.schema = schema;
  config.schema_version = 1;

  SharedRealm realm = Realm::get_shared_realm(config);
  CppContext ctx(realm);


  // auto tbl = realm->read_group().get_table("class_queue");
  realm::TableRef qtable = ObjectStore::table_for_object_type(realm->read_group(), "queue");
  // realm::TableRef etable = ObjectStore::table_for_object_type(realm->read_group(), "event");

  // auto etable = r->read_group().get_table("class_target");

  // etable->add_empty_row(1);

  realm->begin_transaction();

  std::string idx = "q1"s;
  util::Any value = util::Any(AnyDict{
    {"idx", idx},
    // {"events", AnyVec{"a"s, "b"s, "c"s}},
  });

  Object q1 = Object::create(ctx, realm, "queue", value, true);
  auto events = any_cast<List>(q1.get_property_value<util::Any>(ctx, "events"));

  printf("total queues %zu\n", qtable->size());
  printf("q1 size %zu\n", events.size());
  // printf("events size %zu\n", etable->size());

  // auto evt = Object::create(ctx, realm, "event", util::Any(AnyDict{
  //   {"ts", INT64_C(123123)},
  //   {"did", INT64_C(2)},
  //   {"buff", "hello world"s},
  // }), false);

  testWrite(q1, ctx);

  // if(events.size() > 0){
  //   auto evt = events.get(0);
  //   events.remove(0);
  // }
  // events.add(ctx, util::Any("hello"s));

  // auto obj = events.get(0);

  // etable->move_last_over(obj->row().get_index());


  printf("total queues %zu\n", qtable->size());
  printf("q1 size %zu\n", events.size());

  realm->commit_transaction();  
  realm->compact();
  // printf("events size %zu\n", etable->size());

  printf("hello world\n");
  return 0;
}
