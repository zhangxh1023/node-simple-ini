#include "nan.h"
#include "miniini-0.9/miniini.h"

INIFile file;
namespace __simple_ini__
{
  using namespace v8;
  NAN_METHOD(Open)
  {
    Isolate *isolate = info.GetIsolate();
    if (info.Length() < 1)
    {
      Nan::ThrowTypeError("Wrong number of arguments.");
      return;
    }
    if (!info[0]->IsString())
    {
      Nan::ThrowTypeError("The first argument must be a string.");
      return;
    }
    char *filename = new char[Local<String>::Cast(info[0])->Length() + 1];
    Local<String>::Cast(info[0])->WriteUtf8(isolate, filename);
    Local<Value> res = Local<Value>::New(isolate, Nan::New<Boolean>(file.OpenFile(filename)));

    delete[] filename;

    return info.GetReturnValue().Set(res);
  }

  NAN_METHOD(Read)
  {
    Isolate *isolate = info.GetIsolate();
    if (info.Length() < 2)
    {
      Nan::ThrowTypeError("Wrong number of arguments.");
      return;
    }

    if (!info[0]->IsString() || !info[1]->IsString())
    {
      Nan::ThrowTypeError("The first and second arguments must be string.");
    }

    char *sectionName = new char[Local<String>::Cast(info[0])->Length() + 1];
    char *name = new char[Local<String>::Cast(info[1])->Length() + 1];

    Local<String>::Cast(info[0])->WriteUtf8(isolate, sectionName);
    Local<String>::Cast(info[1])->WriteUtf8(isolate, name);

    INISection *section = file.GetSection(sectionName);
    if (!section)
    {
      delete[] sectionName;
      delete[] name;

      if (info.Length() >= 3)
      {
        return info.GetReturnValue().Set(info[2]);
      }
      else
      {
        return info.GetReturnValue().Set(Nan::EmptyString());
      }
    }

    const char *value;
    if (!section->ReadString(name, value))
    {
      delete[] sectionName;
      delete[] name;

      if (info.Length() >= 3)
      {
        return info.GetReturnValue().Set(info[2]);
      }
      else
      {
        return info.GetReturnValue().Set(Nan::EmptyString());
      }
    }
    return info.GetReturnValue().Set(Nan::New<String>(value).ToLocalChecked());
  }

  NAN_MODULE_INIT(Init)
  {
    Nan::Export(target, "read", Read);
    Nan::Export(target, "open", Open);
  }

  NODE_MODULE(SimpleIni, Init)

} // namespace __simple_ini__
