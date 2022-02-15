// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCont
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& PlayerInput) override;
	void SetupGame();
	void EndGame();
	void Won();
	void Lost();
	void LossLive();
	bool SameWords(const FString& Word) const;
	bool SameLen(const FString& Word) const;
	bool IsIsogram(const FString& Word) const;
	FString SelectWord_recursion();
	void SelectWord();
	void GetValidWords();
	bool CehckGuessValidity(const FString& Guess) const;
	void ProcessGuess(const FString& Guess);
	void GetBullCows(const FString& Guess) const;
	

	// Your declarations go below!
	private:
	FString HiddenWord;
	TArray<FString> ValidWords;
	int32 Lives, Damage;
	bool bGameOver;

};
