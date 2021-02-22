
; © Charlie Chernohorsky, 1998-2002; <fractint@oblivion.cz>
; tested on 1024 x 768 @ 256 colors; some do need floats on
; mgl setsize 1024 1024

.FractInt {; see FractInt.Pictorial: http://fractint.oblivion.cz/

  ; Take care of "best order"s. It's for 1024 x 768 and 256 colors.
  ; Then, "time" is for the best order, integer math at Pentium266.
  ; Sometimes, floating-point is needed. I'll always warn you then.

  ; best order 3
  ; time 0:09

    angle 8
    axiom !.[!.FractInt]>7.FractInt               ;o)

    F=G[++@2F[--@I2F]F--F]GGG                     ; F
    F=[[++@2F[--@I2F]F--@I2F]GG++F+@Q2F--F++F]GGG ; R
    F=[@2[++F[--F]@I2F-@Q2F]G++F@I2F+@Q2F]GGG     ; A
    F=[++G[---@Q2F++F]@2F-@IQ2F--F]GGG            ; C
    F=[G++@2FF++@I2G|@2F]GGG                      ; T
    F=[[@2F]G[++@2FF++@I2G|@2F]]GGG               ; I
    F=[@2[++FF|@I2G+@Q2@2F]G++FF]GGG              ; N
    F=[G++@2FF++@I2G|@2F]GG                       ; T
    G=@24G@I24
  }


Astral.1 {

  ; best order 4
  ; time 0:02

    angle 10
    axiom +W

    W=X--X--X--X--X
    X=[A]G+[C11@1.618034+F++++F++++F++++F++++F]FY++FY++FY++FY++FY-[C13@1.618034+F++++F++++F++++F++++F]FZ++FZ++FZ++FZ++FZ--G
    F=
    Y=+G--G+[C11@1.618034+F++++F++++F++++F++++F]FY++FY[++FY[--B]++FY++FY]-[C13@1.618034+F++++F++++F++++F++++F]FZ++FZ++FZ++FZ++FZ-G++G
    Z=+G--G+[C13@1.618034+F++++F++++F++++F++++F]FZ++FZ[++FZ[--A]++FZ++FZ]-[C11@1.618034+F++++F++++F++++F++++F]FY++FY++FY++FY++FY-G++G
    G=+GG-G-GG+
    A=+G--G+[C13@1.618034+F++++F++++F++++F++++F]FZ++FZ++FZ++FZ++FZ
    B=+G--G+[C11@1.618034+F++++F++++F++++F++++F]FY++FY++FY++FY++FY
  }


Astral.2 {

  ; best order 5
  ; time 0:06

    angle 10
    axiom FX++FX++FX++FX++FX++

    F=
    X=FY++FY-FY|FY+[A]+FY++FY
    Y=+GZ--GZ+C13FX++FX[++FX++FX++FX]-C11FX++FX++FX++FX++FX-GZ++GZ
    Z=+GW-GW-GW+
    W=+GZGZ-GZ-GZGZ+
    G=
    A=+GZ--GZ+C13FX++FX++FX++FX++FX
  }


Citric.Circles {

  ; best order 4
  ; time 0:02

    angle 10
    axiom FY++FY++FY++FY++FY++

    F=
    X=FX+FX+FX[+FX+FX+FX+FX]----FX+FX+FX
    Y=FY+FX+FX[+FX++FY]----FX+FX+FX
  }


Fractal.Rose {

  ; best order 13
  ; time 1:33

    angle 10
    axiom C17A

    A=[X]G++[X]G++[X]G++[X]G++[X]G++
    W=FV
    V=G
    F=
    X=@.276393[A]FW++FW[---Y]++FW++FW++FW++
    Y=@.618034[A]FW++FW++FW[<2---Z]++FW++FW++
    Z=@.618034[A]FW++FW++FW[---Y]++FW++FW++
  }


Gothic.Outline {

  ; best order 3
  ; time 0:02

    angle 10
    axiom FX++FX++FX++FX++FX++

    F=
    X=FX++FX[++GY]-FX[++GY[++GY]-FX++FX]-FX[++GY--GY]-FX[++GY]-FX++FX
    Y=GY++FX[++GY]-FX[++GY[++GY]-FX++FX]-FX[++GY--GY]-FX[++GY]-FX++GY
    G=
  }


Grown.Feather {

  ; best order 28 and 32
  ; time 0:17 and 1:29

    angle 5
    axiom C70\72[X]

    X=D/3[A]D/3[!A]@Q0.75>1X
    A=B
    B=E
    E=@0.381966X
  }


Grown.Fern {

  ; best order 28
  ; time 0:22

    angle 5
    axiom C79[\72X]

    X=/3D[/72!Y]/1@I3D@3[\72Y]@Q0.618034>1X
    Y=Z
    Z=A
    A=@0.381966X
  }


Grown.FernStar {

  ; best order 24
  ; time 0:21

    angle 5
    axiom C79\36D[X]\72D[X]\72D[X]\72D[X]\72D[X]

    X=/3D[/72!Y]/1@I3D@3[\72Y]@Q0.618034>1X@IQ0.618034
    Y=Z
    Z=A
    A=@0.381966X
  }


Grown.Grass {

  ; best order 28
  ; time 0:21

    angle 5
    axiom C70\72[X]

    X=D/2[A]D/2[!A]D/2@0.618034X
    A=B
    B=E
    E=@0.381966>1X
  }


Grown.Lawn {

  ; best order 24
  ; time 0:42

    angle 5
    axiom C70[\63@I2D@2X]M[\78@I2D@2!X]M[\72DX]M[\81DX]M[\69@I2D@2X]M[\90D!X]M[\90DX]M[\108@I2D@2!X]M[\99D!X]M[\102@I2D@2X]M[\117@I2D@2X]M[\135@I2D@2!X]

    X=D/2[A]D/2[!A]D/2@0.618034X
    A=B
    B=E
    E=@0.381966>1X
  }


Grown.Maple {

  ; best order 8
  ; time 1:41

    angle 36
    axiom C46[|@I7G@7|++++X][@I7G@7|----!X]+++++++++@I5G@5X

    G=GG
    F=F[+++FX][---FX]F
    X=>1[+++@IQ2.25FX][---@IQ2.25FX]FX
  }


Koch.Fireworks {

  ; best order 9
  ; time 0:08

    angle 12
    axiom C31Z+[A]--F[A]--F[A]--F[A]--F[A]--F[A]--F-

    A=>2+F[R]--F[U]--F[E]--F
    E=+F[H]--[|!H]F
    F=-!F!++!F!-
    H=>1+F[I]--[|!I]F
    I=>2+F[J]--[|!J]F
    J=>1+F[K]--[|!K]F
    K=>2+F[L]--[|!L]F
    L=>2+F--F
    R=>1+F[S]--F[U]--F[E]--F
    S=>2+F[T]--F[U]--F[E]--F
    T=>1+F[P]--F[S]--F[E]--F
    P=>2+F--[|!E]F--F[E]--F
    U=>2+F[R]--F[V]--F--F
    V=>1+F[R]--F[W]--F[E]--F
    W=>1+F[V]--F[X]--F--F
    X=>2+F[Y]--F[Y]--F--F
    Y=>2+F--F--F--F
    Z=Z@IQ3
  }


Koch.Levitation {

  ; best order 6
  ; time 0:10

    angle 6
    axiom C31FW+FW+FW+FW+FW+FW+

    F=
    W=-FXFY++FZFX-
    X=FX-FXFY++FZFX-FX
    Y=->3FX-FXFY++FZFXFY++FZFX-FX-
    Z=--FXFY++FZFXFY++FZFX-FX<3-
  }


Koch.StarRing {

  ; best order 6
  ; time 0:14

    angle 6
    axiom C31FX-FX-FX-FX-FX-FX-

    F=
    X=FX-FXFY++FZFX-FX
    Y=->2FX-FXFY++FZFXFY++FZFX-FX<2-
    Z=-->2FXFY++FZFXFY++FZFX-FX<2-
  }


Mandelbrot.Set {

  ; best order 7
  ; time 0:09

    angle 16
    axiom C25+++F[---@I6Y]++++F[----@I4X]++F[----@I6Y]++F[----@IQ2A]++F[----@I6Y]++F[----@I4X]++F[---@I6Y]++++F

    A=<1--E[----@I6Y]++E[----@I3X]++E[----@I6Y]++E[----@IQ3A]++E[----@I6Y]++E[----@I3X]++E[----@I6Y]++E>1
    B=<1[@I1.2Z]--E[++++@I1.2Z][----@I6Y]++E[----@IQ2Z][++++@IQ2Z]++E[----@I6Y]++E[----A]++E[----@I6Y]++E
    B=[----@IQ2Z][++++@IQ2Z]++E[++++@I1.2Z][----@I6Y]++E>1
    E=@2F@I2
    F=F[-----@I3.5B]F
    X=@2A@I2
    Y=@2X@I2
    Z=@2B@I2
  }


No.Touch.Basic {

  ; best order 14
  ; time 0:14

    angle 10
    axiom C38+[A]FX++[A]FX++[A]FX++[A]FX++[A]FX++

    A=<1+G[@.236068-I]++@.381966E
    B=[A]FX[@.618034-B]++[A]FX++[A]FX++[A]FX++[A]FX
    E=A
    I=B
    F=
    X=FY
    Y=FW
    W=G
  }


No.Touch.Double {

  ; best order 14
  ; time 0:37

    angle 10
    axiom C39+[A]FX++[A]FX++[A]FX++[A]FX++[A]FX++

    A=<1+G[@.236068-I]++@.381966E
    B=[A]FX[@.618034-H]++[A]FX++[A]FX[@.618034-H]++[A]FX++[A]FX
    H=[A]FX[@.618034-H]++[A]FX++[A]FX++[A]FX++[A]FX
    E=A
    I=B
    F=
    X=FY
    Y=FW
    W=G
  }


No.Touch.Full {

  ; best order 13
  ; time 0:26

    angle 10
    axiom C40+[J]FX++[J]FX++[J]FX++[J]FX++[J]FX++

    A=<1+G[@.236068-I]++@.381966E
    B=[A]FX[@.618034-H]++[A]FX[@.618034-G++G++H]++[A]FX[@.618034-H]++[A]FX++[A]FX
    L=[A]FX[@.618034-H]++[A]FX++[A]FX[@.618034-H]++[A]FX++[A]FX
    H=[A]FX[@.618034-H]++[A]FX++[A]FX++[A]FX++[A]FX
    J=+G[@.236068-K]++@.381966E
    E=A
    I=B
    K=L
    F=
    X=FY
    Y=FW
    W=G
  }


No.Touch.Inside {

  ; best order 13
  ; time 0:12

    angle 10
    axiom C39+[A]G++[A]G++[A]G++[A]G++[A]G++

    A=<1--@.4472316B
    B=[I]FX++[I]FX++[I]FX++[I]FX[@.618034-H]++[I]FX
    H=[I]FX[@.618034-H]++[I]FX++[I]FX++[I]FX++[I]FX
    I=<1+G[@.236068-J]++@.381966K
    J=H
    K=I
    F=
    X=FY
    Y=FW
    W=G
  }


No.Touch.Insight {

  ; best order 13
  ; time 0:12

    angle 10
    axiom C39+[A]G++[A]G++[A]G++[A]G++[A]G++

    A=<1--@.4472316B
    B=[I]FX[@.618034-H]++[I]FX++[I]FX++[I]FX[@.618034-E]++[I]FX[@.618034-E]
    E=[I]FX[@.618034-H]++[I]FX++[I]FX[@.618034-H]++[I]FX++[I]FX
    H=[I]FX[@.618034-H]++[I]FX++[I]FX++[I]FX++[I]FX
    I=<1+G[@.236068-J]++@.381966K
    J=E
    K=I
    F=
    X=FY
    Y=FW
    W=G
  }


Penta.Spread {

  ; best order 8
  ; time 0:02

    angle 10
    axiom C31++GA--G++GA--G++GA--G++GA--G++GA--G

    R=@0.618034>2G
    A=[+F[RZ]--F[RE]--F[RB]--F]--F
    B=+F[RB]--F--F--F--F
    Z=[+F[RY]--F[RE]--F[RB]--F]--F
    Y=[+F[RX]--F[RE]--F[RB]--F]--F
    X=[+F[RB]--F[RW]--F[RB]--F]--F
    W=[+F--F[RV]--F[RB]--F]--F
    V=[+F[RW]--F[RI]--F[RB]--F]--F
    E=[+F[RZ]--F[RH]--F[RB]--F]--F
    H=[+F[RZ]--F[RI]--F[RB]--F]--F
    I=[+F[RU]--F--F[RB]--F]--F
    U=[+F[RS]--F--F[RT]--F]--F
    S=[+F[RX]--F[RU]--F[RT]--F]--F
    T=[+F--F--F--F]--F
  }


Penta.Thesis {

  ; best order 13
  ; time 0:07

    angle 10
    axiom C16[A]G++[A]G++[A]G++[A]G++[A]G++

    A=+F[@.236068I]++[@.381966E]F
    B=[A]G[@.618034B]++[A]G++[A]G++[A]G++[A]G++
    E=<3A
    I=<3B
  }


R.I.P.Around {

  ; best order 6
  ; time 0:06

    angle 4
    axiom FY-FY-FY-FY-

    F=
    Y=FY-FY+FX+FY-FY
    X=FA[-Y-Y]+FFX-FX-FXFA[-Y-Y]+F
    A=FA+FFX-FXFA+F-
  }


Sea.Horse {

  ; best order 16 (floats on)
  ; time 0:07

    angle 8
    axiom C88FX

    F=
    X=+FY-<1-@2F@I2X+>1+FY-
    Y=@Q2F@I2X@Q2
  }


Shaded.Paper {

  ; best order 17
  ; time 0:32

    angle 8
    axiom c16FX--FX--FX--FX--

    F=
    X=-FY<1++FY>1-
    Y=+FX<1--FX>1+
  }


Sierp.Square {

  ; best order 5 and 7
  ; time 0:04 and 3:03

    angle 4
    axiom FX-FX-FX-FX-

    F=
    G=
    X=GX-GX+GY++FX-GX-GX-GX++GX-GX
    Y=GYGYGY
  }


Sierp.Trigon.1 {

  ; best order 6 and 9
  ; time 0:01 and 0:06

    angle 6
    axiom C32FX-FY-FX-FY-FX-FY-

    F=
    X=-FY+<2FX>2+FY-
    Y=+FX-<2FY>2-FX+
  }


Sierp.Trigon.2 {

  ; best order 6
  ; time 0:05

    angle 6
    axiom C19F++F++F++

    F=F[<2++F--F--F]FF
  }


Sierp.Trigon.3 {

  ; best order 6
  ; time 0:14

    angle 12
    axiom C19+F+++F+++F+++F++++++F---F---F---F

    F=F[<2++++F----F----F]FF
  }


Sign. {

  ; best order 8
  ; time 0:06

    angle 12
    axiom FX-FY-FX-FY-FX-FY-FX-FY-FX-FY-FX-FY-

    F=
    X=--FY++FX++FY--
    Y=++FX--FY--FX++
  }


Snow.Flake.1 {

  ; best order 5
  ; time 0:06

    angle 6
    axiom C21++[F]-[F]-[F]-[F]-[F]-[F]-

    F=FF<2[--F][-F][+F][++F]>2FF
  }


Snow.Flake.2 {

  ; best order 4
  ; time 0:11

    angle 6
    axiom C19++[F]-[F]-[F]-[F]-[F]-[F]---

    F=F[@I2[--F][-F][+F][++F]]<2F[--F][-F][+F][++F]F>2[@I2[--F][-F][+F][++F]]F
  }


Snow.Flake.3 {

  ; best order 5
  ; time 0:40

    angle 6
    axiom C21Y-Y-Y-Y-Y-Y-

    F=F[@I2[--F][-F][+F][++F]]<2F[--F][-F][+F][++F]F>2[@I2[--F][-F][+F][++F]]F
    Y=[-F][F]+F--F+
  }


Snow.Flake.4 {

  ; best order 12
  ; time 0:14

    angle 6
    axiom C17[FX]+[FX]+[FX]+[FX]+[FX]+[FX]+

    F=
    X=FY<2[+FY][-FY]>2@2FX@I2
    Y=@3FX@I3
  }


Twelve.Stones {

  ; best order 27
  ; time 0:01

    angle 5
    axiom C31A\30A\30A\30A\30A\30A\30A\30A\30A\30A\30A\30A\30

    A=[@I2X][Y]@I2D@2
    X=\5>1[D]W
    W=\5[D]X
    Y=/5>1[D]Z
    Z=/5[D]Y
  }


; © Charlie Chernohorsky, 1998-2002; <fractint@oblivion.cz>
; tested on 1024 x 768 @ 256 colors; some do need floats on
