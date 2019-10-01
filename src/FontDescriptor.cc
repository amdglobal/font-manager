#include "FontDescriptor.h"
#include <nan.h>

FontDescriptor::FontDescriptor(Local<Object> obj) {
    path           = NULL;
    postscriptName = getString(obj, "postscriptName");
    family         = getString(obj, "family");
    style          = getString(obj, "style");
    weight         = (FontWeight)getNumber(obj, "weight");
    width          = (FontWidth)getNumber(obj, "width");
    italic         = getBool(obj, "italic");
    monospace      = getBool(obj, "monospace");
}

FontDescriptor::FontDescriptor() {
    path           = NULL;
    postscriptName = NULL;
    family         = NULL;
    style          = NULL;
    weight         = FontWeightUndefined;
    width          = FontWidthUndefined;
    italic         = false;
    monospace      = false;
}

FontDescriptor::FontDescriptor(const char* path,
                               const char* postscriptName,
                               const char* family,
                               const char* style,
                               FontWeight  weight,
                               FontWidth   width,
                               bool        italic,
                               bool        monospace) {
    this->path           = copyString(path);
    this->postscriptName = copyString(postscriptName);
    this->family         = copyString(family);
    this->style          = copyString(style);
    this->weight         = weight;
    this->width          = width;
    this->italic         = italic;
    this->monospace      = monospace;
}

FontDescriptor::FontDescriptor(FontDescriptor* desc) {
    path           = copyString(desc->path);
    postscriptName = copyString(desc->postscriptName);
    family         = copyString(desc->family);
    style          = copyString(desc->style);
    weight         = desc->weight;
    width          = desc->width;
    italic         = desc->italic;
    monospace      = desc->monospace;
}

FontDescriptor::~FontDescriptor() {
    if (path)
        delete path;

    if (postscriptName)
        delete postscriptName;

    if (family)
        delete family;

    if (style)
        delete style;

    postscriptName = NULL;
    family         = NULL;
    style          = NULL;
}

Local<Object> FontDescriptor::toJSObject() {
    Nan::EscapableHandleScope scope;
    Local<Object>             res = Nan::New<Object>();
    res->Set(Nan::New<String>("path").ToLocalChecked(), Nan::New<String>(path).ToLocalChecked());
    res->Set(Nan::New<String>("postscriptName").ToLocalChecked(),
             Nan::New<String>(postscriptName).ToLocalChecked());
    res->Set(Nan::New<String>("family").ToLocalChecked(),
             Nan::New<String>(family).ToLocalChecked());
    res->Set(Nan::New<String>("style").ToLocalChecked(), Nan::New<String>(style).ToLocalChecked());
    res->Set(Nan::New<String>("weight").ToLocalChecked(), Nan::New<Number>(weight));
    res->Set(Nan::New<String>("width").ToLocalChecked(), Nan::New<Number>(width));
    res->Set(Nan::New<String>("italic").ToLocalChecked(), Nan::New<v8::Boolean>(italic));
    res->Set(Nan::New<String>("monospace").ToLocalChecked(), Nan::New<v8::Boolean>(monospace));
    return scope.Escape(res);
}

char* FontDescriptor::copyString(const char* input) {
    if (!input)
        return NULL;

    char* str = new char[strlen(input) + 1];
    strcpy(str, input);
    return str;
}

char* FontDescriptor::getString(Local<Object> obj, const char* name) {
    Nan::HandleScope scope;
    Local<Value>     value = obj->Get(Nan::New<String>(name).ToLocalChecked());

    if (value->IsString()) {
        return copyString(*Nan::Utf8String(value));
    }

    return NULL;
}

int FontDescriptor::getNumber(Local<Object> obj, const char* name) {
    Nan::HandleScope scope;
    Local<Value>     value = obj->Get(Nan::New<String>(name).ToLocalChecked());

    if (value->IsNumber()) {
        return value->Int32Value(Nan::GetCurrentContext()).FromJust();
    }

    return 0;
}

bool FontDescriptor::getBool(Local<Object> obj, const char* name) {
    Nan::HandleScope scope;
    Local<Value>     value = obj->Get(Nan::New<String>(name).ToLocalChecked());

    if (value->IsBoolean()) {
        return value->BooleanValue(Nan::GetCurrentContext()).FromJust();
    }

    return false;
}
