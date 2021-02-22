Stars&Pentas2  {
     ;; by Philippe Hurbain
     ;; Penrose's stars and pentagons, generated from
     ;; decomposition rules
     ;; u is the star, v is the boat, w is the thin rhombus
     ;; x, y and z are the pentagons
 Angle 10
 Axiom u
 u=@.381966[v]F[|y][-u]++F|+[v]F[|y]++F|+[v]F[|y]++F|+
 u=[v]F[|y]++F|+[v]F[|y]++F
 v=@.381966[v]F[|y]++F|+[v]F[|y]-[u]F-F|+[v]F[|y]++F
 w=@.381966G++[u]F|+F-F|+[v]F[|y]
 y=@.381966[x][y][w]F[|!y]++F++[y][w]F[|!y]++F++[z]F
 x=@.381966G++G++[!x][!z]F--[!z]F--[!z]F--[!z]F--[!z]F
 z=@.381966[z][x]F++[z]F++[w][y]F[|!y]++F++[z]F
 F=G
}
