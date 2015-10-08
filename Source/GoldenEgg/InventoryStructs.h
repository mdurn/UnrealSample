//
//  InventoryStructs.h
//  GoldenEgg
//
//  Created by Michael Durnhofer on 7/22/15.
//  Copyright (c) 2015 EpicGames. All rights reserved.
//

#pragma once

struct Icon {
  FString name;
  UTexture2D* tex;
  Icon() { name = "UNKNOWN ICON"; tex = 0; }
  Icon(FString& name_, UTexture2D* tex_) : name(name_), tex(tex_) {}
};

struct Widget {
  Icon icon;
  FVector2D pos, size;
  
  Widget(Icon icon_) : icon(icon_) {}
  
  float left() { return pos.X; }
  float right() { return pos.X + size.X; }
  float top() { return pos.Y; }
  float bottom() { return pos.Y + size.Y; }
  
  bool hit(FVector2D p) {
    return p.X > left() && p.X < right() &&
      p.Y > top() && p.Y < bottom();
  }
};