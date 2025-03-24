// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/Code_ReloadNow.h"
#include "Code/Actors/BaseCharacter.h"


void UCode_ReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}

void UCode_ReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (UCharacterAnimation* Anim = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance()))
    {
        Anim->OnReloadNow.Broadcast();
    }

}
