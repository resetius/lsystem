Hiwaymed {
; mgl setsize 150 150
; order 10
  Angle 8  ; Smallest turn is 45=360/8 degrees
  Axiom -X ; Turn whole thing 45 degrees so that all lines of X are horizontal or vertical
  X=X+F+Y  ; Do X, turn left, forward, turn left, do Y
  Y=X-F-Y  ; Do X backwards
  }
