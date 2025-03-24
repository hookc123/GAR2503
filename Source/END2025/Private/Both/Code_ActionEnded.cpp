// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/Code_ActionEnded.h"
#include "Code/Actors/BaseCharacter.h"


void UCode_ActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}

void UCode_ActionEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
    {
        Anim->OnActionEnded.Broadcast();
    }

}
