#ifndef FONT_DESCRIPTOR_H
#define FONT_DESCRIPTOR_H
/* #include <nan.h> */
#include <node/node.h>
#include <node/v8.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace v8;

enum FontWeight {
    FontWeightUndefined  = 0,
    FontWeightThin       = 100,
    FontWeightUltraLight = 200,
    FontWeightLight      = 300,
    FontWeightNormal     = 400,
    FontWeightMedium     = 500,
    FontWeightSemiBold   = 600,
    FontWeightBold       = 700,
    FontWeightUltraBold  = 800,
    FontWeightHeavy      = 900
};

enum FontWidth {
    FontWidthUndefined      = 0,
    FontWidthUltraCondensed = 1,
    FontWidthExtraCondensed = 2,
    FontWidthCondensed      = 3,
    FontWidthSemiCondensed  = 4,
    FontWidthNormal         = 5,
    FontWidthSemiExpanded   = 6,
    FontWidthExpanded       = 7,
    FontWidthExtraExpanded  = 8,
    FontWidthUltraExpanded  = 9
};

struct FontDescriptor {
   public:
    const char* path;
    const char* postscriptName;
    const char* family;
    const char* style;
    FontWeight  weight;
    FontWidth   width;
    bool        italic;
    bool        monospace;

    FontDescriptor(Local<Object> obj);

    FontDescriptor();

    FontDescriptor(const char* path,
                   const char* postscriptName,
                   const char* family,
                   const char* style,
                   FontWeight  weight,
                   FontWidth   width,
                   bool        italic,
                   bool        monospace);

    FontDescriptor(FontDescriptor* desc);

    ~FontDescriptor();

    Local<Object> toJSObject();

   private:
    char* copyString(const char* input);

    char* getString(Local<Object> obj, const char* name);

    int getNumber(Local<Object> obj, const char* name);

    bool getBool(Local<Object> obj, const char* name);
};

class ResultSet : public std::vector<FontDescriptor *> {
   public:
    ~ResultSet() {
        for (ResultSet::iterator it = this->begin(); it != this->end(); it++) {
            delete *it;
        }
    }
};

#endif
