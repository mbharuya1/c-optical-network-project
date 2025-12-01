plot "sortie_vitesse_hachage_arbre.txt" using 1:2 title 'table hachage taille 5000' with lines
replot "sortie_vitesse_hachage_arbre.txt" using 1:3 title 'table hachage taille 50000' with lines
replot "sortie_vitesse_hachage_arbre.txt" using 1:4 title 'table hachage taille 500000' with lines
replot "sortie_vitesse_hachage_arbre.txt" using 1:5 title 'arbre' with lines
set term postscript portrait
set output "02_courbes_vitesse.ps"
set size 0.7, 0.7