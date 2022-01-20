// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();

    // PrintLine(FString::Printf(TEXT("The HiddenWords is: %s"), *HiddenWord)); // Debug line
}

void UBullCowCartridge::OnInput(const FString& Input)// When the player hits enter
{
    /*
    If game is not over then do else Checking PlayerGuess
    ClearScreen() and SetupGame() the game
    */
    if(bGameOver)
    {
        ClearScreen(); 
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }  
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!")); 
    
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    Damage = 1;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i latter word!"), HiddenWord.Len()); // Debug line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress Enter to continue..."));

    // const char HW[] = "cakes";
    // const TCHAR HWa[] = TEXT("cakes");
    // const TCHAR HWb[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0')};
     
}
 
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("The hidden word was: %s."), *HiddenWord);
    PrintLine(TEXT("Press Enter to play again!"));
}

void UBullCowCartridge::Won()
{
    ClearScreen();
    PrintLine(TEXT("You have Won!")); // Won
    EndGame();
}

void UBullCowCartridge::Lost()
{
    ClearScreen();
    PrintLine(TEXT("You have Lost!")); // Lost
    EndGame();
}

void UBullCowCartridge:: LossLive()
{
    Lives -= Damage;
    PrintLine(TEXT("Less a life, %i left"), Lives);
}

bool UBullCowCartridge::SameWords(const FString& Word) const
{
    if (HiddenWord.Equals(Word))
    {
        return true;
    }else
    {
        return false;
    }
}

bool UBullCowCartridge::SameLen(const FString& Word) const
{
    if (HiddenWord.Len() == Word.Len())
    {
        return true;
    }else
    {
        return false;
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    TSet<char> HS;

    for(auto& y : Word)
    {
        if(HS.Contains(y))
        {
            // PrintLine(TEXT("Não é isograma")); // Debug
            return false;
        }
        else
        {
            HS.Emplace(y);
        }
    }

    // PrintLine(TEXT("É isograma")); // Debug
    return true;
}

bool UBullCowCartridge::CehckGuessValidity(const FString& Guess) const
{
    bool bValidity = true;

    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        bValidity = false;
    }

    if(!SameLen(Guess))
    {
        PrintLine(TEXT("The Hidden Word is %i characters Long, try again!"), HiddenWord.Len());
        bValidity = false;
    }

    return bValidity;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(SameWords(Guess))
    {
        Won();
    }
    else if(CehckGuessValidity(Guess))
    {
        if(Lives > Damage)
        {
            LossLive();
        }
        else
        {
            Lost();
        }
    }
}