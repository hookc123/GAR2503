// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeButtonWithText.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

UCodeButtonWithText::UCodeButtonWithText(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer),
    Info(FText::FromString(TEXT("Default")))
{}

void UCodeButtonWithText::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (Information)
    {
        Information->SetText(Info);
    }
}

void UCodeButtonWithText::NativeConstruct()
{
    Super::NativeConstruct();

    if (BackgroundButton)
    {
        BackgroundButton->OnClicked.AddDynamic(this, &UCodeButtonWithText::HandleClickButton);
    }
}

void UCodeButtonWithText::HandleClickButton()
{
    OnClickedEvent.Broadcast();
}
