// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "InventoryStructs.h"
#include "NPC_HUD.generated.h"

class UNpcHp;
struct Widget;

struct Message
{
  FString message;
  float time;
  FColor color;
  UTexture2D* texture;
  
  Message()
  {
    // Set the default time.
    time = 5.f;
    color = FColor::White;
  }
  
  Message(FString iMessage, float iTime, FColor iColor, UTexture2D* iTexture)
  {
    message = iMessage;
    time = iTime;
    color = iColor;
    texture = iTexture;
  }
};

/**
 * 
 */
UCLASS()
class GOLDENEGG_API ANPC_HUD : public AHUD
{
	GENERATED_BODY()
  TArray<Message> Messages;
  TArray<UNpcHp*> hps;
  TArray<Widget> widgets;
  FVector2D dims;
  Widget* held_widget;
  
  virtual void DrawHUD() override;
  void DrawMessages(UCanvas* canvas);
  void DrawHpBars();
  void DrawWidgets();
  
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
  UFont* HudFont;
  
  void AddMessage(Message msg);
  void AddHpBar(UNpcHp* hp);
  void AddWidget(Widget widget);
  void ClearWidgets();
  void MouseClicked();
  void MouseMoved();
};
