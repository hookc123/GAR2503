// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeMainMenu.generated.h"

class UCodeButtonWithText;
class UCodeGameInstance;

/**
 * 
 */
UCLASS()
class END2025_API UCodeMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

public:
	


protected:
    virtual void NativeConstruct() override;

    // These are your custom buttons (not plain UButton)
    UPROPERTY(meta = (BindWidget))
    UCodeButtonWithText* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UCodeButtonWithText* QuitGameButton;

private:
    UFUNCTION()
    void HandleStartClicked();

    UFUNCTION()
    void HandleQuitClicked();



};
