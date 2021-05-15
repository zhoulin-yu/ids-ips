#include <napi.h>

extern "C" int first_analysis(void);
extern "C" void all_block(void);
extern "C" void all_quarantine(void);

Napi::Number firstAnalysis(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, first_analysis());
}

void allBlock(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  all_block();
  return;
}

void allQuarantine(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  all_quarantine();
  return;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "firstAnalysis"),
    Napi::Function::New(env, firstAnalysis)
  );
  
  exports.Set(
    Napi::String::New(env, "allBlock"),
    Napi::Function::New(env, allBlock)
  );
  
  exports.Set(
    Napi::String::New(env, "allQuarantine"),
    Napi::Function::New(env, allQuarantine)
  );
  
  return exports;
}

NODE_API_MODULE(idsips, Init)
