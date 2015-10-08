// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "NPC_HUD.h"
#include "NpcHp.h"
#include "NPC.h"

void ANPC_HUD::DrawHUD()
{
  Super::DrawHUD();
  DrawMessages(Canvas);
  DrawHpBars();
  
  dims.X = Canvas->SizeX;
  dims.Y = Canvas->SizeY;
  DrawWidgets();
}

void ANPC_HUD::DrawMessages(UCanvas* canvas)
{
  for (int c = Messages.Num() - 1; c >= 0; c--)
  {
    float OutputWidth, OutputHeight, pad = 10.f;
    GetTextSize(Messages[c].message, OutputWidth, OutputHeight, HudFont, 1.f);
    
    float MessageH = OutputHeight + 2.f * pad;
    float x = 0, y = c * MessageH;
    if (Cast<UTexture2D>(Messages[c].texture) != nullptr)
    {
      DrawTexture(Messages[c].texture, x, y, MessageH, MessageH, 0, 0, 1, 1);
      x += MessageH;
    }
    DrawRect(FLinearColor::Black, x, y, canvas->SizeX - x, MessageH);
    DrawText(Messages[c].message, Messages[c].color, x + pad, y + pad, HudFont);
    
    Messages[c].time -= GetWorld()->GetDeltaSeconds();
    
    if (Messages[c].time < 0)
    {
      Messages.RemoveAt(c);
    }
  }
}

void ANPC_HUD::DrawHpBars() {
  for (int i = hps.Num() - 1; i >= 0; i--) {
    FVector2D screen_pos = hps[i]->GetScreenPosition();
    if (screen_pos.X == -1.f) { continue; }
    
    float bar_width = 100.f;
    float bar_height = 6.f;
    float x = screen_pos.X;
    float y = screen_pos.Y - 10.f;
    float percent_hp = (float)hps[i]->current_hp / hps[i]->max_hp;
    float current_hp_width = bar_width * percent_hp;
    
    DrawRect(FLinearColor::Red, x, y, bar_width, bar_height);
    DrawRect(FLinearColor::Green, x, y, current_hp_width, bar_height);
    
    if (hps[i]->is_visible == false)
    {
      hps.RemoveAt(i);
    }
  }
}

void ANPC_HUD::AddMessage(Message msg) {
  Messages.Add(msg);
}

void ANPC_HUD::AddHpBar(UNpcHp* hp) {
  hps.Add(hp);
}

void ANPC_HUD::DrawWidgets() {
  
  for (int i = 0; i < widgets.Num(); i++) {
    DrawTexture(widgets[i].icon.tex, widgets[i].pos.X, widgets[i].pos.Y, widgets[i].size.X, widgets[i].size.Y, 0, 0, 1, 1);
    DrawText(widgets[i].icon.name, FLinearColor::Yellow, widgets[i].pos.X, widgets[i].pos.Y, HudFont, 0.6f, false);
  }
}

void ANPC_HUD::AddWidget(Widget widget) {
  FVector2D start(200, 00), pad(12, 12);
  widget.size = FVector2D(100, 100);
  widget.pos = start;
  for (int i = 0; i < widgets.Num(); i++) {
    widget.pos.X += widget.size.X + pad.X;
    if (widget.pos.X + widget.size.X > dims.X) {
      widget.pos.X = start.X;
      widget.pos.Y += widget.size.Y + pad.Y;
    }
  }
  widgets.Add(widget);
}

void ANPC_HUD::ClearWidgets() {
  for (int i = widgets.Num() - 1; i >= 0; i--) {
    widgets.RemoveAt(i);
  }
}

void ANPC_HUD::MouseClicked() {
  APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
  if (!p_controller) { return; }
  FVector2D mouse;

  p_controller->GetMousePosition(mouse.X, mouse.Y);
  held_widget = NULL;
  for (int i = 0; i < widgets.Num(); i++) {
    held_widget = &widgets[i];
    return;
  }
}

void ANPC_HUD::MouseMoved() {
  APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
  if (!p_controller) { return; }
  
  static FVector2D last_mouse;
  FVector2D this_mouse, d_mouse;
  p_controller->GetMousePosition(this_mouse.X, this_mouse.Y);
  d_mouse = this_mouse - last_mouse;
  float time = p_controller->GetInputKeyTimeDown(EKeys::LeftMouseButton);
  
  if (time > 0.f && held_widget) {
    held_widget->pos.X += d_mouse.X;
    held_widget->pos.Y += d_mouse.Y;
  }
  
  last_mouse = this_mouse;
}
