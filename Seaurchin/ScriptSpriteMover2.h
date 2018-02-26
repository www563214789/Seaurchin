#pragma once
#include "Easing.h"
#include "Misc.h"
#include "MoverFunction.h"

struct SpriteMoverArgument {
    Easing::EasingFunction Ease;
    float X;
    float Y;
    float Z;
    double Duration;
    double Wait;

    SpriteMoverArgument();
};

struct SpriteMoverData {
    float Extra1;
    float Extra2;
    float Extra3;
    double Now;
    bool IsStarted;

    SpriteMoverData();
};

struct SpriteMoverObject {
    MoverFunction::Action Function;
    SpriteMoverArgument Argument;
    SpriteMoverData Data;
    ~SpriteMoverObject()
    {
        spdlog::get("main")->info(u8"MoverObject Destroyed");
    }
};

class SSprite;

class ScriptSpriteMover2 final {
private:
    SSprite *Target;
    std::list<std::unique_ptr<SpriteMoverObject>> moves;

    void ApplyProperty(const std::string &prop, const std::string &value);
    std::unique_ptr<SpriteMoverObject> BuildMoverObject(const std::string &func, const PropList &props);

public:
    ScriptSpriteMover2(SSprite *target);
    ~ScriptSpriteMover2();

    void Tick(double delta);

    void Apply(const std::string &application);
    void AddMove(const std::string &params);
    void Abort(bool completeMove);
};