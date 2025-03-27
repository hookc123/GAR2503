// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeResultsWidget.generated.h"

class UCodeButtonWithText;
class UWidgetSwitcher;
class UVerticalBox;
class UCodeGameInstance;

/**
 * 
 */
UCLASS()
class END2025_API UCodeResultsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetWin(); 

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UCodeButtonWithText* MenuButton;

    UPROPERTY(meta = (BindWidget))
    UCodeButtonWithText* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UWidgetSwitcher* ResultSwitch;

    UPROPERTY(meta = (BindWidgetOptional)) 
    UVerticalBox* ButtonArea;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing")
    float TimeToMenu;

private:
    UCodeGameInstance* GameInstance = nullptr;

    UFUNCTION()
    void LoadMenu();

};
