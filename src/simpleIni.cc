#include "nan.h"
#include "miniini-0.9/miniini.h"

INIFile file;
namespace __simple_ini__
{
    using v8::Isolate;
    using v8::Local;
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
        Local<v8::String> filename_handle = Nan::To<v8::String>(info[0]).ToLocalChecked();
        char *filename = new char[filename_handle->Length() + 1];
        filename_handle->WriteUtf8(isolate, filename);
        Local<v8::Value> ret = Nan::New<v8::Value>(Nan::New(file.OpenFile(filename)));

        delete[] filename;

        return info.GetReturnValue().Set(ret);
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

        Local<v8::String> sectionName_handle = Nan::To<v8::String>(info[0]).ToLocalChecked();
        Local<v8::String> name_handle = Nan::To<v8::String>(info[1]).ToLocalChecked();
        char *sectionName = new char[sectionName_handle->Length() + 1];
        char *name = new char[name_handle->Length() + 1];

        sectionName_handle->WriteUtf8(isolate, sectionName);
        name_handle->WriteUtf8(isolate, name);

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
        return info.GetReturnValue().Set(Nan::New<v8::String>(value).ToLocalChecked());
    }

    NAN_MODULE_INIT(Init)
    {
        Nan::Export(target, "read", Read);
        Nan::Export(target, "open", Open);
    }

    NODE_MODULE(SimpleIni, Init)

} // namespace __simple_ini__
