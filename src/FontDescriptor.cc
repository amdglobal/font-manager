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
    Local<Object>             res = Nan::New<Object>();
    Nan::Set(
        res, Nan::New<String>("path").ToLocalChecked(), Nan::New<String>(path).ToLocalChecked());
    Nan::Set(res,
             Nan::New<String>("postscriptName").ToLocalChecked(),
             Nan::New<String>(postscriptName).ToLocalChecked());
    Nan::Set(res,
             Nan::New<String>("family").ToLocalChecked(),
             Nan::New<String>(family).ToLocalChecked());
    Nan::Set(
        res, Nan::New<String>("style").ToLocalChecked(), Nan::New<String>(style).ToLocalChecked());
    Nan::Set(res, Nan::New<String>("weight").ToLocalChecked(), Nan::New<Number>(weight));
    Nan::Set(res, Nan::New<String>("width").ToLocalChecked(), Nan::New<Number>(width));
    Nan::Set(res, Nan::New<String>("italic").ToLocalChecked(), Nan::New<v8::Boolean>(italic));
    Nan::Set(res, Nan::New<String>("monospace").ToLocalChecked(), Nan::New<v8::Boolean>(monospace));
    return res;
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
    MaybeLocal<Value> value = Nan::Get(obj, Nan::New<String>(name).ToLocalChecked());

    if (!value.IsEmpty() && value.ToLocalChecked()->IsString()) {
        return copyString(*Nan::Utf8String(value.ToLocalChecked()));
    }

    return NULL;
}

int FontDescriptor::getNumber(Local<Object> obj, const char* name) {
    Nan::HandleScope scope;
    MaybeLocal<Value> value = Nan::Get(obj, Nan::New<String>(name).ToLocalChecked());

    if (!value.IsEmpty() && value.ToLocalChecked()->IsNumber()) {
        return value.ToLocalChecked()->Int32Value(Nan::GetCurrentContext()).FromJust();
    }

    return 0;
}

bool FontDescriptor::getBool(Local<Object> obj, const char* name) {
    Nan::HandleScope scope;
    MaybeLocal<Value> value = Nan::Get(obj, Nan::New<String>(name).ToLocalChecked());
    Local<Value> checked;

    if (!value.IsEmpty()) {
        checked = value.ToLocalChecked();
        if (checked->IsBoolean()) {
            return checked->BooleanValue(Nan::GetCurrentContext()->GetIsolate());
        } else {
            return false;
        }
    } else {
        return false;
    }
}
