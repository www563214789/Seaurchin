#pragma once

#include "AngelScriptManager.h"
#include "ScriptResource.h"
#include "Character.h"
#include "Skill.h"
#include "Result.h"

#define SU_CHAR_SMALL_WIDTH 280
#define SU_CHAR_SMALL_HEIGHT 170
#define SU_CHAR_FACE_SIZE 128

class CharacterInstance final {
private:
    std::shared_ptr<AngelScript> ScriptInterface;

    std::shared_ptr<CharacterParameter> CharacterSource;
    std::shared_ptr<SkillParameter> SkillSource;
    std::shared_ptr<Result> TargetResult;

    std::vector<asIScriptObject*> Abilities;
    std::vector<asITypeInfo*> AbilityTypes;
    asIScriptContext *context;

    SImage *ImageFull;
    SImage *ImageSmall;
    SImage *ImageFace;

    CharacterInstance(std::shared_ptr<CharacterParameter> character, std::shared_ptr<SkillParameter> skill, std::shared_ptr<AngelScript>);
    ~CharacterInstance();

    void MakeCharacterImages();
    void LoadAbilities();
    void SetResult(std::shared_ptr<Result> result);
    asIScriptObject* LoadAbilityObject(boost::filesystem::path filepath);

    void OnEvent(const char *name);
    void OnEvent(const char *name, AbilityNoteType type);

public:

    void OnStart();
    void OnFinish();
    void OnJusticeCritical(AbilityNoteType type);
    void OnJustice(AbilityNoteType type);
    void OnAttack(AbilityNoteType type);
    void OnFinish(AbilityNoteType type);

    static std::shared_ptr<CharacterInstance> CreateInstance(std::shared_ptr<CharacterParameter> character, std::shared_ptr<SkillParameter> skill, std::shared_ptr<AngelScript> script);
};

void RegisterCharacterSkillTypes(asIScriptEngine *engine);