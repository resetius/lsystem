# lsystem
[L-System Fractal Generator](https://en.wikipedia.org/wiki/L-system)

This program was inspired by [FractInt](http://fractint.oblivion.cz) pictures and written by me in 2008. Current version (2021) was rewritten in C language and stripped of old/unused/broken code.

# build
```
$ cmake ${source-dir}
$ make
```   
# run
```
$ lsystem -f ${source-dir}/fractals/snoppy.ls
  ....
building Snow.Flake.2
  using order 4
  lsystem done
  turtle done
  normilize done
  saving done
building Snow.Flake.3
  using order 5
  lsystem done
  turtle done
  normilize done
  saving done
building Snow.Flake.4
  using order 12
  lsystem done
  turtle done
  normilize done
  saving done
building Twelve.Stones
  using order 27
  lsystem done
  turtle done
  normilize done
  saving done
```
# syntax

```
fractal_name { fractal_description }
```
Fractal with name 'fractal_name' will be saved to 'fractal_name.png'.

Fractal description parameters:

 | name     | description                                   |
 | ------------- | --------------------------------------------- |
 | alpha         | initial angle                                 |
 | theta         | angle increment in radians                    |
 | angle         | angle increment in degree                     |
 | axiom         | sets axiom                                    |
 | + or -        | increment or decrement angle on theta radians |
 | !             | swaps + and -                                 |
 | [ and ]       | branch                                        |
 | F or D        | draw forward                                  |
 | G or M.       | skip forward                                  |
 | Cnumber       | sets current color to number                  |
 | >number       | increases color by number                     |
 | <number       | decreases color by number                     |
 | |             | increases angle by 180 degree                 |
 | \number       | increases angle by number degree              |
 | /number       | decreases angle by number degree              |
 | @number       | multiplies step by number                     |
 | @qnumber      | multiplies step by square root of number      |
 | @lnumber      | divides step by number                        |
 | @lqnumber     | divides step by square root of number         |
 | @qlnumber     | divides step by square root of number         |
 | ;             | comment                                       |
 | ;order number | sets order of current fractal to number       |
 
# Fractal description examples
```
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
```

# Pictures examples
This examples were generated from rule-files taken from [FractInt](http://fractint.oblivion.cz).

![img/200x200/No.Touch.Double.png](https://github.com/resetius/lsystem/blob/master/img/200x200/No.Touch.Double.png?raw=true)
![img/200x200/Mandelbrot.Set.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Mandelbrot.Set.png?raw=true)
![img/200x200/Penta.Spread.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Penta.Spread.png?raw=true)
![img/200x200/No.Touch.Inside.png](https://github.com/resetius/lsystem/blob/master/img/200x200/No.Touch.Inside.png?raw=true)
![img/200x200/Sierp.Square.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sierp.Square.png?raw=true)
![img/200x200/Penta.Thesis.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Penta.Thesis.png?raw=true)
![img/200x200/Grown.Lawn.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.Lawn.png?raw=true)
![img/200x200/Koch.Fireworks.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Koch.Fireworks.png?raw=true)
![img/200x200/Koch.Levitation.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Koch.Levitation.png?raw=true)
![img/200x200/Sign..png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sign..png?raw=true)
![img/200x200/Grown.Feather.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.Feather.png?raw=true)
![img/200x200/Grown.Grass.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.Grass.png?raw=true)
![img/200x200/Grown.Maple.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.Maple.png?raw=true)
![img/200x200/Fractal.Rose.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Fractal.Rose.png?raw=true)
![img/200x200/R.I.P.Around.png](https://github.com/resetius/lsystem/blob/master/img/200x200/R.I.P.Around.png?raw=true)
![img/200x200/Twelve.Stones.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Twelve.Stones.png?raw=true)
![img/200x200/Shaded.Paper.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Shaded.Paper.png?raw=true)
![img/200x200/Gothic.Outline.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Gothic.Outline.png?raw=true)
![img/200x200/Sea.Horse.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sea.Horse.png?raw=true)
![img/200x200/Citric.Circles.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Citric.Circles.png?raw=true)
![img/200x200/No.Touch.Basic.png](https://github.com/resetius/lsystem/blob/master/img/200x200/No.Touch.Basic.png?raw=true)
![img/200x200/Sierp.Trigon.3.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sierp.Trigon.3.png?raw=true)
![img/200x200/Koch.StarRing.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Koch.StarRing.png?raw=true)
![img/200x200/Sierp.Trigon.2.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sierp.Trigon.2.png?raw=true)
![img/200x200/No.Touch.Insight.png](https://github.com/resetius/lsystem/blob/master/img/200x200/No.Touch.Insight.png?raw=true)
![img/200x200/Snow.Flake.1.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Snow.Flake.1.png?raw=true)
![img/200x200/Snow.Flake.3.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Snow.Flake.3.png?raw=true)
![img/200x200/No.Touch.Full.png](https://github.com/resetius/lsystem/blob/master/img/200x200/No.Touch.Full.png?raw=true)
![img/200x200/Grown.FernStar.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.FernStar.png?raw=true)
![img/200x200/Sierp.Trigon.1.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Sierp.Trigon.1.png?raw=true)
![img/200x200/Snow.Flake.2.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Snow.Flake.2.png?raw=true)
![img/200x200/Grown.Fern.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Grown.Fern.png?raw=true)
![img/200x200/Astral.2.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Astral.2.png?raw=true)
![img/200x200/Astral.1.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Astral.1.png?raw=true)
![img/200x200/Snow.Flake.4.png](https://github.com/resetius/lsystem/blob/master/img/200x200/Snow.Flake.4.png?raw=true)
