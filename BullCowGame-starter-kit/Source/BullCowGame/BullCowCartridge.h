// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

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
	void SelectWord();
	void GetValidWords();
	bool CehckGuessValidity(const FString& Guess) const;
	void ProcessGuess(const FString& Guess);
	

	// Your declarations go below!
	private:
	FString HiddenWord;
	TArray<FString> ValidWords;
	int32 Lives;
	int32 Damage;
	bool bGameOver;

};
