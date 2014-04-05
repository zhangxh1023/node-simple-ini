#include <node.h>
#include <v8.h>
#include "miniini-0.9/miniini.h"
using namespace v8;

INIFile file;

// Read a value
Handle<Value> Read(const Arguments& args)
{
    HandleScope scope;

    if(args.Length() < 2)
    {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments.")));
        return scope.Close(Undefined());
    }

    if(!args[0]->IsString() || !args[1]->IsString())
    {
        ThrowException(Exception::TypeError(String::New("The first and second arguments must be string.")));
        return scope.Close(Undefined());
    }

    char* sectionName = new char[args[0]->ToString()->Length() + 1];
    char* name = new char[args[1]->ToString()->Length() + 1];

    Local<String>::Cast(args[0])->WriteAscii(sectionName);
    Local<String>::Cast(args[1])->WriteAscii(name);

    INISection* section = file.GetSection(sectionName);
    if(!section)
    {
        delete []sectionName;
        delete []name;

        if(args.Length() >= 3)
        {
            return scope.Close(args[2]);
        }
        else
        {
            return scope.Close(String::New(""));
        }        
    }

    const char* value;
    if(!section->ReadString(name, value))
    {
        delete []sectionName;
        delete []name;

        if(args.Length() >= 3)
        {
            return scope.Close(args[2]);
        }
        else
        {
            return scope.Close(String::New(""));
        }       
    }

    return scope.Close(String::New(value));
}

// Open an INI file.
Handle<Value> Open(const Arguments& args)
{
    HandleScope scope;

    if(args.Length() < 1)
    {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments.")));
        return scope.Close(Undefined());
    }

    if(!args[0]->IsString())
    {
        ThrowException(Exception::TypeError(String::New("The first argument must be a string.")));
        return scope.Close(Undefined());
    }

    char* filename = new char[args[0]->ToString()->Length() + 1];

    Local<String>::Cast(args[0])->WriteAscii(filename);
    Local<Value> res = Local<Value>::New(Boolean::New(file.OpenFile(filename)));

    delete []filename;

    return scope.Close(res);
}

void Init(Handle<Object> exports)
{
    exports->Set(String::NewSymbol("open"),
        FunctionTemplate::New(Open)->GetFunction());
    exports->Set(String::NewSymbol("read"),
        FunctionTemplate::New(Read)->GetFunction());
}

NODE_MODULE(simpleIni, Init)
