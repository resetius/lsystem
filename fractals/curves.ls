; mgl setsize 1024 1024
Cesaro { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 34
  Axiom FX
  F=
  X=----F!X!++++++++F!X!----
  }

CesaroDouble { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 4
  axiom D\90D\90D\90D\90
  D=\42!D!/84!D!\42
  }

Curve1 { ; Adrian Mariano, from the Algorithmic Beauty of Plants
    ; curve from figure 1.9a p.10
  angle 4
  axiom F-F-F-F-
  f=FF-F-F-F-F-F+F
  }

Curve2 { ; Adrian Mariano, from the Algorithmic Beauty of Plants
  angle 4
  axiom F-F-F-F-
  f=FF-F+F-F-FF
  }

Curve3 { ; Adrian Mariano, from the Algorithmic Beauty of Plants
    ; curve from figure 1.9e p.10
  axiom F-F-F-F-
  angle 4
  F=F-FF--F-F
  }

Curve4 { ; Adrian Mariano
   axiom yf
   x=YF+XF+Y
   y=XF-YF-X
   angle 6
   }

Dragon { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 8
  Axiom FX
  F=
  y=+FX--FY+
  x=-FX++FY-
  }

DragonCurve { ; Adrian Mariano
  Angle 4
  Axiom X
  X=X-YF-
  Y=+FX+Y
  }

Fass1 { ; Adrian Mariano, from the Algorithmic Beauty of Plants
   ; FASS curve (3x3 tiles form macrotile), Figure 1.16a p.17
  axiom -l
  angle 4
  L=LF+RFR+FL-F-LFLFL-FRFR+
  R=-LFLF+RFRFR+F+RF-LFL-FR
  }

Fass2 { ; Adrian Mariano, from the Algorithmic Beauty of Plants
   ; FASS curve (4x4 tiles form macrotile), Figure 1.16b p.17
; order 4
  angle 4
  axiom -l
  L=LFLF+RFR+FLFL-FRF-LFL-FR+F+RF-LFL-FRFRFR+
  R=-LFLFLF+RFR+FL-F-LF+RFR+FLF+RFRF-LFL-FRFR
  }

FlowSnake { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  angle 6
  axiom FL
  L=FL-FR--FR+FL++FLFL+FR-"
  R=+FL-FRFR--FR-FL++FL+FR"
  F=
  }

Hilbert { ; Ken Philip, from The Science of Fractal Images
  axiom x
  x=-YF+XFX+FY-
  y=+XF-YFY-FX+
  angle 4
  }

Koch1 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 6
  Axiom F--F--F
  F=F+F--F+F
  }

Koch2 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 12
  Axiom F---F---F---F
  F=-F+++F---F+
  }

Koch3 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 4
  Axiom F-F-F-F
  F=F-F+F+FF-F-F+F
  }

Koch4 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  angle 12
  axiom f++++f++++f
  f=+f--f++f-
  }

Koch5 {
  axiom f+F+F+F
  f=F+F-F-FFF+F+F-F
  angle 4
  }

Koch6 { ; Adrian Mariano
; order 3
   axiom f+f+f+f
   f=f-ff+ff+f+f-f-ff+f+f-f-ff-ff+f
   angle 4
    }

KochCurve { ; Adrian Mariano
  Angle 6
  Axiom F
  F=F+F--F+F
  }

Peano1 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 4
  Axiom F-F-F-F
  F=F-F+F+F+F-F-F-F+F
  }

Peano2 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 8
  Axiom FXY++F++FXY++F
  X=XY@Q2-F@IQ2-FXY++F++FXY
  Y=-@Q2F-@IQ2FXY
  }

Peano3 {
  axiom x
  x=XFYFX+F+YFXFY-F-XFYFX
  y=YFXFY-F-XFYFX+F+YFXFY
  angle 4
  }

QuadGosper { ; Adrian Mariano, from the Algorithmic Beauty of Plants
        ; Quadratic Gosper curve, Figure 1.11b p.12
; order 3
  angle 4
  axiom -Fr
  l=FlFl-Fr-Fr+Fl+Fl-Fr-FrFl+Fr+FlFlFr-Fl+Fr+FlFl+Fr-FlFr-Fr-Fl+Fl+FrFr-
  r=+FlFl-Fr-Fr+Fl+FlFr+Fl-FrFr-Fl-Fr+FlFrFr-Fl-FrFl+Fl+Fr-Fr-Fl+Fl+FrFr
  f=
  }

QuadKoch { ; Adrian Mariano, from the Algorithmic Beauty of Plants
      ; Quadratic Koch island, Figure 1.7a p.9
; order 3
  angle 4
  AXIOM F-F-F-F-
  F=F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F
  }

Quartet { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  angle 4
  axiom fb
  A=FBFA+HFA+FB-FA
  B=FB+FA-FB-JFBFA
  F=
  H=-
  J=+
  }

SnowFlake1 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  Angle 12
  Axiom FR
  R=++!FRFU++FU++FU!---@Q3FU|-@IQ3!FRFU!
  U=!FRFU!|+@Q3FR@IQ3+++!FR--FR--FRFU!--
  F=
  }

SnowFlake2 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  angle 12
  axiom F
  F=++!F!F--F--F@IQ3|+F!F--
  F=F--F!+++@Q3F@QI3|+F!F@Q3|+F!F
  }

SnowFlake3 { ; Adrian Mariano
; from The Fractal Geometry of Nature by Mandelbrot
  angle 12
  axiom fx
  x=++f!x!fy--fx--fy|+@iq3fyf!x!++f!y!++f!y!fx@q3+++f!y!fx
  y=fyf!x!+++@iq3fyf!x!++f!x!++f!y!fx@q3|+fx--fy--fxf!y!++
  f=
  }

;SnowFlakeColor { ; Adrian Mariano
  ; from The Fractal Geometry of Nature by Mandelbrot
;  angle 12
;  axiom F
;  F=--!F<1!F<1++F<1++F<1@IQ3|-F<1!F<1++
;  F=F<1++F<1!---@Q3F<1@QI3|-F<1!F<1@Q3|-F<1!F<1
;  <=
;  }
