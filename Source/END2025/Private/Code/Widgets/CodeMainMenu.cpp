// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/CodeMainMenu.h"
#include "Both/CodeButtonWithText.h"
#include "Code/Utility/CodeGameInstance.h"

void UCodeMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartGameButton)
    {
        StartGameButton->OnClickedEvent.AddDynamic(this, &UCodeMainMenu::HandleStartClicked);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClickedEvent.AddDynamic(this, &UCodeMainMenu::HandleQuitClicked);
    }
}

void UCodeMainMenu::HandleStartClicked()
{
    if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(GetGameInstance()))
    {
        GameInstance->LoadFirstLevel();
    }
}

void UCodeMainMenu::HandleQuitClicked()
{
    if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(GetGameInstance()))
    {
        GameInstance->QuitTheGame();
    }
}
