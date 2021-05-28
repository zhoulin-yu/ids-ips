#include <napi.h>

extern "C" int analysis_treatment(void);
extern "C" void all_block(void);
extern "C" void all_quarantine(void);
extern "C" void remove_analyse_and_listeContamine(void);
extern "C" int local_analysis(char *arg[]);

Napi::Number firstAnalysis(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, analysis_treatment());
}

Napi::Number folderAnalysis(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::string path = (std::string) info[0].ToString();
  char* cPath = &*path.begin();
  return Napi::Number::New(env, local_analysis(&cPath));
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

void removeAnalyseAndListeContamine(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  remove_analyse_and_listeContamine();
  return;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "firstAnalysis"),
    Napi::Function::New(env, firstAnalysis)
  );

  exports.Set(
    Napi::String::New(env, "folderAnalysis"),
    Napi::Function::New(env, folderAnalysis)
  );
  
  exports.Set(
    Napi::String::New(env, "allBlock"),
    Napi::Function::New(env, allBlock)
  );
  
  exports.Set(
    Napi::String::New(env, "allQuarantine"),
    Napi::Function::New(env, allQuarantine)
  );
  
  exports.Set(
    Napi::String::New(env, "removeAnalyseAndListeContamine"),
    Napi::Function::New(env, removeAnalyseAndListeContamine)
  );

  return exports;
}

NODE_API_MODULE(idsips, Init)
