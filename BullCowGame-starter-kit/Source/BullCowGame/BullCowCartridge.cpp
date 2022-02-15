// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
// #include "Math/UnrealMathUtility.h"


/* 
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
 */

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    /* 
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    */

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput)// When the player hits enter
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
        ProcessGuess(PlayerInput);
    }  
}

void UBullCowCartridge::SetupGame()
{
    // Slect only isograms from the words list - First method
    // GetValidWords();
    // SelectWord();

    
    // Slect only isograms from the words list - Second method
    HiddenWord = SelectWord_recursion();
    PrintLine(TEXT("***The HiddenWords is: %s."), *HiddenWord); // Debug
    Lives = HiddenWord.Len() * 2;
    Damage = 1;
    bGameOver = false;

    // Welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i latter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Press Tab to type your guess and \npress Enter to continue..."));

    // const char HW[] = "cakes";
    // const TCHAR HWa[] = TEXT("cakes");
    // const TCHAR HWb[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e'), TEXT('s'), TEXT('\0')};
     
}

FString UBullCowCartridge::SelectWord_recursion()
{
    FString Word = WordList[FMath::RandRange(0,WordList.Num() - 1)];

    if (IsIsogram(Word) && Word.Len() >= 4 && Word.Len() <= 8)
    {
        return Word;
    }
    else
    {
        return SelectWord_recursion();
    }
}

void UBullCowCartridge::GetValidWords()
{
    TSet<FString> RepeatSet;

    for (FString Word : WordList)
    {
        if(IsIsogram(Word) && Word.Len() >= 4 && Word.Len() <= 8){

            if(!RepeatSet.Contains(Word))
            {
                ValidWords.Emplace(Word);
                RepeatSet.Emplace(Word);
            }
        }
    }

    // PrintLine(TEXT("***Words: %i"), WordList.Num()); // Debug
    // PrintLine(TEXT("***Valid words: %i"), ValidWords.Num()); // Debug
}

void UBullCowCartridge::SelectWord()
{
    //If not empty
    if(ValidWords.Num() > 0)
    {
        //Get a random word inside the bounds os the ValidWords range
        int RandomIndex = FMath::RandRange(0,ValidWords.Num() - 1);

        // PrintLine(TEXT("***The word is: %s"), *ValidWords[RandomIndex]); //Debug

        // Select the random isogram word
        HiddenWord =  ValidWords[RandomIndex];
        
        // Removing the selected word
        ValidWords.RemoveAt(RandomIndex);
    }
    else
    {
        // Default word
        HiddenWord =  TEXT("cake");
    }
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

void UBullCowCartridge::LossLive()
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
    TSet<char> LettersSet;

    for(auto& Letter : Word)
    {
        if(LettersSet.Contains(Letter))
        {
            // PrintLine(TEXT("Não é isograma")); // Debug
            return false;
        }
        else
        {
            LettersSet.Emplace(Letter);
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

void UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCont Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(SameWords(Guess))
    {
        Won();
    }
    else if(CehckGuessValidity(Guess))
    {
        GetBullCows(Guess);

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