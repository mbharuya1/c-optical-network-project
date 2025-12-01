plot "sortie_vitesse_liste.txt" using 1:2 title 'liste' with lines
set term postscript portrait
set output "01_courbes_vitesse.ps"
set size 0.7, 0.7