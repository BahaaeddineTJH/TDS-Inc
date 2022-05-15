# TDS-Inc
Télécharger les librairies: libsox, gtk et fftw3

Dans le fichier ‘local-serveur’: make serveur
→ ./serveur port_number path_to_bin_folder(sans ‘/’ a la fin du path)
exemple: ./serveur 2048 bin

Puis dans le fichier ‘interface’: make main
→ ./main adresse_ip port_number
exemple: ./main 127.0.0.1 2048

Ensuite il faut choisir une musique dans ‘file’ puis ‘open’ et appuyer sur le bouton 
‘Run Shazaam’.
