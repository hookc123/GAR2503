// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeButtonWithText.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedEvent);

/**
 *
 */
UCLASS()
class END2025_API UCodeButtonWithText : public UUserWidget
{
	GENERATED_BODY()

public:

	UCodeButtonWithText(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnClickedEvent OnClickedEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText Info;

	UPROPERTY(meta = (BindWidget))
	UButton* BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Information;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleClickButton();

private:

};
